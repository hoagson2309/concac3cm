#include "hardware/i2c.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include <hardware/structs/io_bank0.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define PIN_MISO 16
#define PIN_CS 17
#define PIN_SCK 18
#define PIN_MOSI 19
#define IODIR 0x00
#define GPIO 0x09
#define SPI_OP_CODE 0x46

#define SDA 4
#define SCL 5
#define OS 6

#define TEMP_ADDR 0x49
#define TEMP_LOW 22
#define TEMP_HIGH 29

// --Temperature register list ---
#define TEMP 0x00
#define CONF 0x01
#define THYST 0x02
#define TOS 0x03

#define ALS_ADDR 0x52

#define BUTTON_PIN 15
static volatile bool temp_on = true;

static inline void cs_select()
{
    asm volatile("nop \n nop \n nop");
    gpio_put(PIN_CS, 0);
    asm volatile("nop \n nop \n nop");
}

static inline void cs_deselect()
{
    asm volatile("nop \n nop \n nop");
    gpio_put(PIN_CS, 1);
    asm volatile("nop \n nop \n nop");
}

void io_exp_write(uint8_t reg, uint8_t data)
{
    uint8_t buf[3];
    buf[0] = SPI_OP_CODE;
    buf[1] = reg;
    buf[2] = data;

    cs_select();
    spi_write_blocking(spi0, buf, 3);
    cs_deselect();

    sleep_ms(10);
}
void gpio_callback(uint gpio, uint32_t events)
{
    static uint64_t last_us = 0;
    uint64_t now = time_us_64();
    if (gpio == BUTTON_PIN && (events & GPIO_IRQ_EDGE_RISE))
    {
        if (now - last_us > 200000)
        { // 200 ms debounce
            temp_on = !temp_on;
            last_us = now;
        }
    }
    else if (gpio == OS && (events & GPIO_IRQ_EDGE_RISE))
    {
        // threshold reached
        printf("HOT HOT HOT HOT \n");
    }
}

float read_temperature(void)
{
    uint8_t buf[2];
    uint8_t reg = TEMP;
    i2c_write_blocking(i2c_default, TEMP_ADDR, &reg, 1, true);
    i2c_read_blocking(i2c_default, TEMP_ADDR, buf, sizeof(buf), false);

    int16_t raw = (buf[0] << 8) | buf[1];
    raw >>= 5; // 11 bits on the left side are useable
    return raw * 0.125f;
}

void temp_set_thresholds()
{
    // Convert to LM75B format: 0.5°C per LSB, left-shifted 7 bits
    uint16_t low_raw = (uint16_t)(TEMP_LOW * 2) << 7;
    uint16_t high_raw = (uint16_t)(TEMP_HIGH * 2) << 7;

    uint8_t thyst[2] = {(low_raw >> 8) & 0xFF, low_raw & 0xFF};
    uint8_t tos[2] = {(high_raw >> 8) & 0xFF, high_raw & 0xFF};
    uint8_t reg = THYST;
    uint8_t buffer[3] = {reg, thyst[0], thyst[1]};
    i2c_write_blocking(i2c_default, TEMP_ADDR, buffer, 3, false);

    reg = TOS;
    buffer[0] = reg;
    buffer [1] = tos[0];
    buffer [2] = tos [1];
    i2c_write_blocking(i2c_default, TEMP_ADDR, buffer, 3, false);
}

int32_t read_light()
{
    uint8_t buf[3];
    uint8_t reg = 0x0D;

    i2c_write_blocking(i2c_default, ALS_ADDR, &reg, 1, true);
    i2c_read_blocking(i2c_default, ALS_ADDR, buf, sizeof(buf), false);

    int32_t raw = ((uint32_t)(buf[2] & 0x0F) << 16) | ((uint32_t)buf[1] << 8) | (uint32_t)buf[0];

    return raw;
}
int main()
{
    stdio_init_all();
    sleep_ms(1000);

    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(SDA, GPIO_FUNC_I2C);
    gpio_set_function(SCL, GPIO_FUNC_I2C);

    gpio_init(OS);
    gpio_set_dir(OS, GPIO_IN);
    gpio_pull_up(OS);

    spi_init(spi0, 500 * 1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

    gpio_pull_up(SDA);
    gpio_pull_up(SCL);
    gpio_pull_up(OS);
    sleep_ms(20);

    io_exp_write(IODIR, 0x00);
 uint8_t init_buf[2] = {0x00, 0x02};
    i2c_write_blocking(i2c_default, ALS_ADDR, init_buf, sizeof(init_buf), false);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_RISE, true, &gpio_callback);

    gpio_set_irq_enabled(OS, GPIO_IRQ_EDGE_RISE, true);

    uint8_t trash = 0x02;
    uint8_t config_data = CONF; // store your config byte
    uint8_t buffer[2] = {config_data, trash};
    i2c_write_blocking(i2c_default, TEMP_ADDR, buffer, 2, false);

    temp_set_thresholds();

    while (true)
    {
        if (temp_on)
        {
            float temp_ = read_temperature();
            io_exp_write(GPIO, (uint8_t)temp_);
            printf("TEMP: %.2f °C\n", temp_);
        }
        else
        {
            int32_t light = read_light();
            io_exp_write(GPIO, (uint8_t)light);
            printf("LIGHT: %lu \n", light);
        }
        sleep_ms(500);
    }

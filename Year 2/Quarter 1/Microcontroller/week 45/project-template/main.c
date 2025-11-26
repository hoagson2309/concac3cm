#include "pico/stdlib.h" //timing
#include "hardware/spi.h" //SPI communication
#include "hardware/adc.h" //analog-digital conversion
#include "stdio.h"

#define PIN_SCK 18  //or pico default spi sck pin
#define PIN_MOSI 19 //or pico default spi tx pin
#define PIN_MISO 16 //or pico default spi rx pin
//chips select pins
#define PIN_CS 17 //or pico default spi csn pin (io expander)
#define PIN_CS_DAC 20 //DAC

// CS functions for MCP23S17 (io expander)
static inline void cs_select()
{
    asm volatile("nop \n nop \n nop");
    gpio_put(PIN_CS, 0);  //pulling low - active low (enable the devices)
    asm volatile("nop \n nop \n nop");
}

static inline void cs_deselect()
{
    asm volatile("nop \n nop \n nop");
    gpio_put(PIN_CS, 1); //pulling CS HIGH (disables the device )
    asm volatile("nop \n nop \n nop");
}
// CS functions for DAC (digital analog converter)
static inline void cs_select_dac()
{
    asm volatile("nop \n nop \n nop");
    gpio_put(PIN_CS_DAC, 0); //pulling low - active low (enable the devices)
    asm volatile("nop \n nop \n nop");
}

static inline void cs_deselect_dac()
{
    asm volatile("nop \n nop \n nop");
    gpio_put(PIN_CS_DAC, 1); //pulling CS HIGH (disables the device again)
    asm volatile("nop \n nop \n nop");
}

// Write a byte to MCP23S17 register
void io_exp_write(uint8_t reg, uint8_t data)
{
// Set SPI for rising edge clock (Mode 0) => data is read when the clock goes from L to H
//=> LEDs update correctly
    spi_set_format(spi0, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

   // spi_set_format(spi0, 8, SPI_CPOL_1, SPI_CPHA_0, SPI_MSB_FIRST);

    uint8_t buf[3] = {0x40, reg, data}; // SPI write opcode
    cs_select(); 
    spi_write_blocking(spi0, buf, 3);
    cs_deselect();
    sleep_us(10);
}

// Write a value to DAC 
void dac_write_spi(uint16_t value)
{
    
    //spi_set_format(spi0, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);

    // Set SPI for falling edge (Mode 1) => data is read when the clock goes from H to L
    //"The contents of the serial input register are transferred to the DAC register on the sixteenth falling edge of SCLK"
    //=> stable voltage output
    spi_set_format(spi0, 8, SPI_CPOL_0, SPI_CPHA_1, SPI_MSB_FIRST); 

    value = value << 2; //moves the 10-bit DAC data into bits 11–2 of the 16-bit register
    uint8_t buf[2];

    buf[0] = (value >> 8) & 0xFF;   //High byte(control + top DAC bits)
                                    // (shift upper 8 bits of 16-bit register (bits 15-8) down into bits 7–0 of the byte)
                                    //& 0xFF ensures only 8 bits are sent via SPI

    buf[1] = value & 0xFF;  //Low byte (bottom DAC bits + padding)
                            //(Keeps lower 8 bits of value (bits 7–0))

    cs_select_dac(); //SYNC (CS) low => start of write
                                        //16 falling edges of SCLK clock all bits into the DAC’s serial input register.
    spi_write_blocking(spi0, buf, 2);   // DIN (Serial data input) + SCLK (Serial clock) (Sends 16 bits (control + 10-bit data) over DIN/SCLK)
    cs_deselect_dac();  //SYNC high => DAC latches value
    sleep_us(10);

    //"Once SYNC is low, the data on DIN is clocked into the 16-bit serial input register on the falling edges of SCLK"
    //"Normally, the SYNC line is kept low for at least 16 falling edges of SCLK and the DAC is updated on the 16th SCLK falling edge"
}
int main()
{
    stdio_init_all();
    sleep_ms(2000); // Wait for USB serial

    // SPI init
    spi_init(spi0, 1000 * 1000); // 1 MHz
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

    // CS pins
    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

    gpio_init(PIN_CS_DAC);
    gpio_set_dir(PIN_CS_DAC, GPIO_OUT);
    gpio_put(PIN_CS_DAC, 1);

    // ADC init if you want to read back voltage
    adc_init();
    adc_gpio_init(26); // ADC0 on GPIO26
    adc_select_input(0);

    // Set MCP23S17 port A as output -> drives LEDs
    io_exp_write(0x00, 0x00); // IODIRA = 0 (all outputs)

    // //initialize port B as output
    // io_exp_write(0x01, 0x00); // IODIRB = 0 → Port B all outputs

 while (true)
    {
        for (uint16_t value = 0; value <= 1023; value++)
        {
            dac_write_spi(value);          // Update DAC
            io_exp_write(0x0A, value >> 2); // Update LEDs 
            //0x0A (register address we writing to) => GPIOB — Port B output register 
            //shift 10 bits of DAC value to 8-bit number cuz io only handle 8 bits => control 8 LEDS (bits 7-0)
            //so the LEDs show a binary representation of the DAC voltage

            // Read back DAC voltage if connected to ADC
            uint16_t adc_raw = adc_read();
            float voltage = adc_raw * 3.3f / 4095.0f;
            printf("Value: %3d | ADC: %4d | Voltage: %.2f V\n", value, adc_raw, voltage);

            sleep_ms(200);
        }
    }
}























//void io_exp_write(uint8_t reg, uint8_t data)
    //This function sends three bytes to the I/O expander:
        //Byte 1: Control byte      (0x40 = write) (selects MCP23S17)
        //Byte 2: Register address  (0x00 for IODIRA)
        //Byte 3: Data byte         (bit pattern for LEDs)

// Why we need to write a byte to MCP23S17 registers?
    // The MCP23S17 is an SPI I/O expander — it lets your Pico control 16 extra GPIO pins (organized into two 8-bit ports: Port A and Port B) using only a few SPI lines.
    // However — unlike the Pico’s own GPIO pins — you can’t directly set a pin high or low by toggling a hardware register in the Pico.
    // You have to tell the MCP23S17 what to do — and that means writing data into its internal registers via SPI.
    //You write bytes to the MCP23S17 registers because that’s how you tell it what to do — each register controls a specific behavior (direction, output level, pull-ups, interrupts, etc.).

//spi_set_format(spi0, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    //Data size: 8 bits per transfer
    //Bit order: most significant bit first (MSB_FIRST)
    //this sets the communication timing format that matches the device (IO-expander or DAC)

//CPOL (Clock Polarity
    //Whether the clock idles LOW (0) or HIGH (1)
//CPHA (Clock Phase)
    //Whether data is read on the first edge or the second edge of the clock pulse
//So depending on these, there are 4 SPI modes:
// Mode	 CPOL	CPHA	Clock idle	Data captured on	Also called
//  0	  0    	 0	       LOW	      Rising edge	      “Mode 0”
//  1	  0	     1	       LOW   	  Falling edge	      “Mode 1”
//  2	  1	     0	       HIGH	      Falling edge	      “Mode 2”
//  3	  1  	 1	       HIGH	      Rising edge	      “Mode 3”
//cuz u using 2 chips and each chip has its own SPI mode requirements specified in its datasheet.

// Rising or falling edge = when the chip safely reads data.
// It ensures the right LED pattern or voltage is displayed correctly.

//Pull IO-expander CS LOW → send data → release CS HIGH
//Only after releasing IO-expander CS do you pull DAC CS LOW → send data → release
//At no point are both CS pins LOW simultaneously.

//We use uint16_t (16 bits) to hold the value,
// but only the lower 10 bits actually contain useful DAC data (0–1023).
// The DAC itself only cares about 10 bits of precision,
// but SPI transmits in 8-bit chunks, so we use a 16-bit variable to make it easier to handle.

//10-bit DAC input: value = 0b1111111111 (1023 decimal)
//value = value << 2; // 0b111111111100 (12 bits)
//Stored in 16-bit variable uint16_t value:
//value = 0b0000111111111100  // 16 bits total
    //buf[0]: [0 0 0 0 1 1 1 1], buf[1]: [1 1 1 1 1 1 0 0]



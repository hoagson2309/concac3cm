#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

const uint8_t segment_patterns[] = {
    0b00111111, 
    0b00000110, 
    0b01011011, 
    0b01001111, 
    0b01100110, 
    0b01101101, 
    0b01111101, 
    0b00000111, 
    0b01111111,
    0b01101111
};

void display_on_7segment(uint number, uint segments[]) {
    uint8_t pattern = segment_patterns[number];

    for (int i = 0; i < 7; i++) {
        gpio_put(segments[i], (pattern >> i) & 1);
    }
}

int main() {
    stdio_init_all();
    uart_init(uart0, 115200);

    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);

    char buffer[16];
    int index = 0;

    uint segments_humid_tens[7] = {21, 20, 12, 11, 10, 26, 22};
    uint segments_humid_units[7] = {17, 16, 15, 14, 13, 19, 18};
    for (size_t i = 0; i < 7; i++)
    {
        gpio_init(segments_humid_tens[i]);
        gpio_set_dir(segments_humid_tens[i], GPIO_OUT);
        gpio_init(segments_humid_units[i]);
        gpio_set_dir(segments_humid_units[i], GPIO_OUT);
    }
    
    for (uint i = 0; i < 10; i++) {
        display_on_7segment(i, segments_humid_units);
        display_on_7segment((i + 1) % 10, segments_humid_tens); // Different digit for tens
        sleep_ms(3000);
    }

    while (true) {
        while (uart_is_readable(uart0)) { 
            char c = uart_getc(uart0);
            if (c == '\n') {
                buffer[index] = '\0';
                int received_number = atoi(buffer);
                printf("Received: %d\n", received_number);
                display_on_7segment((uint) received_number % 10, segments_humid_units);
                sleep_ms(50);
                display_on_7segment(((uint) received_number /10) % 10, segments_humid_tens);
                sleep_ms(50);
                index = 0;
            } else {
                buffer[index++] = c;
                if (index >= sizeof(buffer) - 1) {
                    index = 0;
                }
            }
        }
    }
}

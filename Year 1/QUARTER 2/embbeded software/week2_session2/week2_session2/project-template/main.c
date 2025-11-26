// TODO: include your code here
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include <stdbool.h>
void setup_led_pin(uint led_pin){
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
}
void display_number(uint number, uint leds[]) {
    if (number > 9) return; // Only display numbers from 0 to 9

    // Define the pattern for each number
    uint pattern[] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};
    // Turn on the right LEDs
    for (int i = 0; i < 7; i++) {
        gpio_put(leds[i], pattern[number] & (1 << i));
    }
}

int main() {
    // Initialize ADC for the potentiometer
    adc_init();
    adc_gpio_init(28); // Initialize the GPIO pin for the ADC
    adc_select_input(4); // Select the ADC input, channel 4 = pin 28
    adc_set_temp_sensor_enabled(true);

    // Set the GPIO pin for the button as input
    const uint PIN_LED1[8] = {13, 12, 18, 17, 16, 14, 15, 19};    // TODO: Set the GPIO pin for the LED1
    const uint PIN_LED2[8] = {}; // TODO: Set the GPIO pin for the LED2
    // Set the GPIO pin for the LED as output   
    for(int i = 0; i < 8; i++){
        setup_led_pin(PIN_LED1[i]); //displaying the tens
        setup_led_pin(PIN_LED2[i]); //displaying the ones
    }

    while (true) {
        float voltage = adc_read() * 3.3f / 4095.0f;
        uint temperature = 27 - (voltage - 0.706) / 0.001721;
        display_number(temperature / 10, PIN_LED1);
        display_number(temperature % 10, PIN_LED2);
        sleep_ms(100);    
    }
}
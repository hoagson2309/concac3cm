#include "pico/stdlib.h" // Standard library for Pico

// Constants for LED blink delay in milliseconds and GPIO pins
const uint TIME_DELAY_MS = 1000;
const uint LED_PIN_1 = 12; 
const uint LED_PIN_2 = 13; 
const uint LED_PIN_3 = 14; 
const uint LED_PIN_4 = 15; 
// The difference is due to the order for better visualization on the breadboard 

int main() {
    // Initialize both LED pins as output
    gpio_init(LED_PIN_1);
    gpio_set_dir(LED_PIN_1, GPIO_OUT);
    gpio_init(LED_PIN_2);
    gpio_set_dir(LED_PIN_2, GPIO_OUT);
    gpio_init(LED_PIN_3);
    gpio_set_dir(LED_PIN_3, GPIO_OUT);
    gpio_init(LED_PIN_4);
    gpio_set_dir(LED_PIN_4, GPIO_OUT);

    // Never-ending superloop
    while (true) {
        for(int i=0; i<16; i++){
            gpio_put(LED_PIN_1, false);
            gpio_put(LED_PIN_2, false);
            gpio_put(LED_PIN_3, false);
            gpio_put(LED_PIN_4, false);
            if(i & 1){
                gpio_put(LED_PIN_1, true);
            }
            if(i & 2){
                gpio_put(LED_PIN_2, true);
            }
            if(i & 4){
                gpio_put(LED_PIN_3, true);
            }
            if(i & 8){
                gpio_put(LED_PIN_4, true);
            }
            sleep_ms(TIME_DELAY_MS);
        }
    }
}
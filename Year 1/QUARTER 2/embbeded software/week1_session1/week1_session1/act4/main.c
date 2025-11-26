#include "pico/stdlib.h" // Standard library for Pico

void setup_led_pin(uint LED_PIN) {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

int main() {
    const int delay = 100;
    const uint LED_PINS [6] = {0,1,2,3,4,5};
    for(int i = 0; i< 6; i++){
        setup_led_pin(LED_PINS[i]);
    }
    while(true){
        for(int i = 0; i < 6; i++){
            if(i != 0){
                gpio_put(LED_PINS[i], true);
                gpio_put(LED_PINS[i-1], true);
                if(i >= 1){
                    gpio_put(LED_PINS[i-2], false);
                }
                sleep_ms(delay);
            } else{
                gpio_put(LED_PINS[0], true);
                gpio_put(LED_PINS[1], false);
                sleep_ms(delay);
            }
        }
        for(int i = 5; i >= 0; i--){
            if(i != 5){
                gpio_put(LED_PINS[i], true);
                gpio_put(LED_PINS[i + 1], true);
                if(i <= 5){
                    gpio_put(LED_PINS[i + 2], false); 
                }
                sleep_ms(delay);
            } else{
                gpio_put(LED_PINS[5], true);
                gpio_put(LED_PINS[4], false);
                sleep_ms(delay);
            }
        }
    }
}
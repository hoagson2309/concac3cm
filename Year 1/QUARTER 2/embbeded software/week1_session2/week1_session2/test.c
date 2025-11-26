#include "pico/stdlib.h" // Standard library for Pico

int main() {
    // Set up the LED pin 15 / physical pin 20
    const uint LED_PIN = 15;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Never-ending superloop
    while (true) {
        gpio_put(LED_PIN, true);
        sleep_ms(1000);
        gpio_put(LED_PIN, false);
        sleep_ms(1000);
    }
}
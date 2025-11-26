#include "pico/stdlib.h" // Standard library for Pico

void setup_led_pin(uint LED_PIN) {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

int main() {
    // Set up the LED pin 15 / physical pin 20
    const uint BLINK_TIME = 1000;
    const uint LED_PIN = 15;
    setup_led_pin(LED_PIN);

    // Never-ending superloop
    while (true) {
        gpio_put(LED_PIN, true);
        sleep_ms(BLINK_TIME);
        gpio_put(LED_PIN, false);
        sleep_ms(BLINK_TIME);
    }
}
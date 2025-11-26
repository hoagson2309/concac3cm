#include "pico/stdlib.h"  // Standard library for Pico
#include "hardware/pwm.h" // Hardware PWM library
#include "hardware_random.h"    // Random number generator

void set_up_led(const uint LED_PIN){
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

int main(){
    const uint RED = 13;
    set_up_led(RED);
    const uint GREEN = 14;
    set_up_led(GREEN);
    const uint BLUE = 15;
    set_up_led(BLUE);

    const uint SLEEP = 500;

    gpio_set_function(RED, GPIO_FUNC_PWM);
    gpio_set_function(GREEN, GPIO_FUNC_PWM);
    gpio_set_function(BLUE, GPIO_FUNC_PWM);

    uint R_slice_num = pwm_gpio_to_slice_num(RED);
    uint G_slice_num = pwm_gpio_to_slice_num(GREEN);
    uint B_slice_num = pwm_gpio_to_slice_num(BLUE);

    pwm_set_wrap(R_slice_num, 254);
    pwm_set_wrap(G_slice_num, 254);
    pwm_set_wrap(B_slice_num, 254);

    pwm_set_enabled(R_slice_num, true);
    pwm_set_enabled(G_slice_num, true);
    pwm_set_enabled(B_slice_num, true);

    while (true){
        pwm_set_gpio_level(RED, pico_rand() % 255);
        pwm_set_gpio_level(GREEN, pico_rand() % 255);
        pwm_set_gpio_level(BLUE, pico_rand() % 255);

        sleep_ms(SLEEP);
    }
}
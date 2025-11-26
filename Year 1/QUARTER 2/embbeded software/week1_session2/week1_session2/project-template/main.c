// TODO: include your code here
#include "pico/stdlib.h"

void display_binary_4_LEDs(int number, const uint PIN_LED[4]){
    for(int i = 3; i >= 0; i--){
        gpio_put(PIN_LED[i], number % 2);
        number /= 2;
    }
}

int main()
{
    const uint PIN_BUTTON = 14; // TODO: Set the GPIO pin for the button
    const uint PIN_LED[] = {0, 1, 2, 3};    // TODO: Set the GPIO pin for the LED
    const uint delay = 200;
    // Set the GPIO pin for the button as input
    gpio_init(PIN_BUTTON);
    gpio_set_dir(PIN_BUTTON, GPIO_IN);
    gpio_pull_down(PIN_BUTTON);

    // Set the GPIO pin for the LED as output   
    for(int i = 0; i < 4; i++){
        gpio_init(PIN_LED[i]);
        gpio_set_dir(PIN_LED[i], GPIO_OUT);
    }
    
    bool previous_state = false;
    int counter = 0;
    while (true)
    {
        // Read the button state and light the LED
        bool button_state = gpio_get(PIN_BUTTON);
        if (button_state && !previous_state)
        {
            display_binary_4_LEDs(counter % 16, PIN_LED);
            counter++;
        }
        previous_state = button_state; //This ensures the toggle happens only once per press (and release)
        sleep_ms(delay); //debouncing
    }
    return 0;
}  
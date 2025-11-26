#include "pico/stdlib.h"
#include "hardware/timer.h"
#include <stdio.h>
#include <stdlib.h>

#define LED 2

bool toggle_led_callback(struct repeating_timer* t){
    static bool led_state = false;
    led_state = !led_state;
    gpio_put(LED, led_state);

    printf("%lld\n", time_us_64());  //Returns the current time in microseconds since the board started running.
    return true;
}

int main(){
    stdio_init_all();
    gpio_init(LED);
    gpio_set_dir(LED, true);

    struct repeating_timer timer;
    add_repeating_timer_ms(500, toggle_led_callback, NULL, &timer);  
    //instead of starting 500 ms from now, 
    //it will align the timer so the callbacks happen on exact half-second boundaries (relative to system time).

    while(1){
        tight_loop_contents();
    }
}
#include "pico/stdlib.h" // Standard library for Pico
#include <dht.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include <string.h>

// CAR LIGHT (CONTROLLER) !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void set_car_light(int green, int yellow, int red, uint led_pin1, uint led_pin2, uint led_pin3){
    gpio_put(led_pin1, green);
    gpio_put(led_pin2, yellow);
    gpio_put(led_pin3, red);
}

void setup_led_pin(uint led_pin){
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
}

int main(){
    stdio_init_all();

    const uint LED_PIN_GREEN = 2;
    setup_led_pin(LED_PIN_GREEN);

    const uint LED_PIN_YELLOW = 3;
    setup_led_pin(LED_PIN_YELLOW);

    const uint LED_PIN_RED = 4;
    setup_led_pin(LED_PIN_RED);

    // set GPIO pin to UART
    gpio_set_function(0, GPIO_FUNC_UART); //TX
    gpio_set_function(1, GPIO_FUNC_UART); //RX

    // initialize UART 0 with a baud rate of 115200
    uart_init(uart0, 115200);

    set_car_light(1, 0, 0, LED_PIN_GREEN, LED_PIN_YELLOW, LED_PIN_RED);
    
    while (true){
        if(uart_is_readable(uart0)){
            char command = uart_getc(uart0);

            if(command == 'B'){ // button pressed 
            set_car_light(0, 1, 0, LED_PIN_GREEN, LED_PIN_YELLOW, LED_PIN_RED); // switch car light to yellow
            sleep_ms(2000); //2sec

            set_car_light(0, 0, 1, LED_PIN_GREEN, LED_PIN_YELLOW, LED_PIN_RED); //switch car light to red

            uart_putc(uart0, 'G'); //send signal to pedestrian light to make it turn green
            sleep_ms(10000); //10sec

            uart_putc(uart0, 'B');//send signal to pedestrian light to make it turn to blinking stage
            sleep_ms(3000); //3sec

            uart_putc(uart0, 'R');//send signal to pedestrian light to make it turn red

            set_car_light(1, 0,  0, LED_PIN_GREEN, LED_PIN_YELLOW, LED_PIN_RED);//switch car light to green again after pedestrian light turned red
            }
        }
    }
    return 0;
}

//PEDESTRIAN LIGHT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void set_pedestrian_light(int green, int red, const uint led_pin1, const uint led_pin2){
    gpio_put(led_pin1, green);
    gpio_put(led_pin2, red);
}

void setup_led_pin(uint led_pin){
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
}

int main(){
    const uint LED_PIN_GREEN = 6;
    setup_led_pin(LED_PIN_GREEN);

    const uint LED_PIN_RED = 7;
    setup_led_pin(LED_PIN_RED);

    const uint PIN_BUTTON = 8;
    // Set the GPIO pin for the button as input
    gpio_init(PIN_BUTTON);
    gpio_set_dir(PIN_BUTTON, GPIO_IN);
    gpio_pull_down(PIN_BUTTON);

    // set GPIO pin to UART
    gpio_set_function(1, GPIO_FUNC_UART); //TX
    gpio_set_function(0, GPIO_FUNC_UART); //RX

    // initialize UART 0 with a baud rate of 115200
    uart_init(uart0, 115200);

    //start with red light for pedestrians
    set_pedestrian_light(0, 1, LED_PIN_GREEN, LED_PIN_RED);

    while(true){
        if(gpio_get(PIN_BUTTON)){ //check button (pressed or not)
            uart_putc(uart0, 'B'); //press the button
            sleep_ms(500);
        }

        if(uart_is_readable(uart0)){
            char command = uart_getc(uart0);

            if(command == 'G'){ 
                set_pedestrian_light(1, 0, LED_PIN_GREEN, LED_PIN_RED); //switch pedestrian light to green
            } else if(command == 'B'){
                for(int i = 0; i < 3; i++){
                    set_pedestrian_light(1, 0, LED_PIN_GREEN, LED_PIN_RED);
                    sleep_ms(500);
                    set_pedestrian_light(0, 0, LED_PIN_GREEN, LED_PIN_RED);
                    sleep_ms(500);
                }
            } else if (command == 'R'){
                set_pedestrian_light(0 , 1, LED_PIN_GREEN, LED_PIN_RED); // switch pedestrians light to red
            }
        }
    }
    return 0;
}

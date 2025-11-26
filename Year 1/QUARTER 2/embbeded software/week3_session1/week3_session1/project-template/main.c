#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include <stdio.h> // Needed for printf and scanf
#include <string.h>

bool scanf_non_blocking(char* destination){
    static int index = 0;
    int value = getchar_timeout_us(0);
    if(!isspace(value)){
        destination[index] = value;
        index++;
        destination[index] = '\0';
        return false;
    } else{
        destination[index] = '\0';
        index = 0;
        return true;
    }
}
int main() {
    stdio_init_all(); // Initialize the serial communication

    adc_init();
    adc_gpio_init(26); // Initialize the GPIO for ADC input
    adc_select_input(0); 

    const uint LED_PIN = 0;

     // Tell GPIO_PIN it is allocated to the PWM
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    // Get the slice number for the GPIO_PIN
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN);

    pwm_set_wrap(slice_num, 999);
    // Set the PWM running     
    pwm_set_enabled(slice_num, true);

    char input_buffer[10];  // Buffer to hold the input string
    int brightness = 0;
    
    while (true) { // Infinite loop to keep the program running
        if(scanf_non_blocking(input_buffer)){ //if input is completed
            brightness = atoi(input_buffer); //The input string is converted to an integer
        }
        if(brightness >= 0 && brightness <= 999){   
            pwm_set_gpio_level(LED_PIN, brightness);
            printf("Brightness: %d\n", brightness);  // print output brightness value to the console
        }
        uint16_t value = adc_read();
        float voltage = value * 3.3f / 4095.0f;
        printf("Potentiometer Voltage: %.2f V\n", voltage);
    
    sleep_ms(500); // small delay to prevent excessive cpu usage
    }
}

///In your activity, scanf_non_blocking() is necessary because:
///It allows the LED brightness to remain adjustable without the program freezing while waiting for input.
///It lets the program monitor for input changes continuously and respond when the input is complete (i.e., when a space is detected).
///It demonstrates the concept of processing input in a responsive, non-blocking manner—a fundamental skill in embedded programming.
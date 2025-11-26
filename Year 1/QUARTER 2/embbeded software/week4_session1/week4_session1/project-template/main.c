#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "dht.h"

typedef enum{
    LOW_TEMPERATURE,
    MEDIUM_TEMPERATURE,
    HIGH_TEMPERATURE
}temperature_state_t;

temperature_state_t state = LOW_TEMPERATURE;
uint32_t state_start_time = 0;

void setup_led_pin(uint led_pin){
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
}

void set_RGB_led_color(bool green, bool blue, bool red, uint green_pin, uint blue_pin, uint red_pin){
    gpio_put(green_pin, green);
    gpio_put(blue_pin, blue);
    gpio_put(red_pin, red);
}

void setup_buzzer(uint buzzer_pin){
    gpio_init(buzzer_pin);
    gpio_set_dir(buzzer_pin, GPIO_OUT);
}

void buzz(uint buzzer_pin, uint duration_ms){
    gpio_put(buzzer_pin, 1);
    sleep_ms(duration_ms);
    gpio_put(buzzer_pin, 0);
}

float read_temperature(){
    uint16_t raw = adc_read();
    float voltage = raw * 3.3 / 4095.0f;
    return (voltage - 0.5f) * 100.0f; //return celcius degree
}

float read_humidity(){

    return humidity;    

}

void display_on_7_segment_display(uint number, uint leds[]) {
    if (number > 9) return; // Only display numbers from 0 to 9

    // Define the pattern for each number
    uint pattern[] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};
    // Turn on the right LEDs
    for (int i = 0; i < 7; i++) {
        gpio_put(leds[i], pattern[number] & (1 << i));
    }
}

void next_state(float temperature, uint green_pin, uint blue_pin, uint red_pin, uint buzzer_pin){
    switch (state){

        case LOW_TEMPERATURE:
            if(temperature > 20.0){
            state = MEDIUM_TEMPERATURE;
            set_RGB_led_color(green_pin, blue_pin, red_pin, 0, 1, 0); // blue (medium)
            }
            break;

        case MEDIUM_TEMPERATURE:
            if(temperature > 30.0){
                state = HIGH_TEMPERATURE;
                set_RGB_led_color(green_pin, blue_pin, red_pin, 0, 0, 1); //red (high)
                buzz(buzzer_pin, 500);//alert for high tempurature
            } else if (temperature <= 20){
                state = LOW_TEMPERATURE;
                set_RGB_led_color(green_pin, blue_pin, red_pin, 1, 0 ,0); //green(low)
            }
            break;

        case HIGH_TEMPERATURE:
            if(temperature <= 30.0){
                state = MEDIUM_TEMPERATURE;
                set_RGB_led_color(green_pin, blue_pin, red_pin, 0, 1, 0);
            }
            break;
    }
}

int main(){
    stdio_init_all();

    const uint GREEN_PIN = 0;
    setup_led_pin(GREEN_PIN);

    const uint BLUE_PIN = 1;
    setup_led_pin(BLUE_PIN);

    const uint RED_PIN = 2;
    setup_led_pin(RED_PIN);

    const uint BUZZER_PIN = 3;
    setup_buzzer(BUZZER_PIN);

    uint segments_pins_tens[7] = {4, 5, 6, 7, 8, 9, 10}; //pins for tens digits display
    for(int i = 0; i < 7; i++){
        gpio_init(segments_pins_tens[i]);
        gpio_set_dir(segments_pins_tens[i], GPIO_OUT);
    }

    uint segments_pins_units[7] = {11, 12, 13, 14, 15, 16, 17}; //pins for units digits display
    for (int i = 0; i < 7; i++) {
        gpio_init(segments_pins_units[i]);
        gpio_set_dir(segments_pins_units[i], GPIO_OUT);
    }

    adc_init();
    adc_set_temperature_sensor_enable(true);
    adc_select_input(4);

    set_RGB_led_color(GREEN_PIN, BLUE_PIN, RED_PIN, 1, 0, 0); //initialize to green

    while(true){
        float temperature = read_temperature();
        float humidity = read_humidity();

        //display on 7-segment display
        uint8_t units_digit = (uint8_t)(temperature) % 10; //converts the floating-point value to an 8-bit unsigned integer by truncating any decimal part. ex:29.1 = 29
        display_on_7_segment_display(units_digit, segments_pins_units);

        sleep_ms(5);

        uint8_t tens_digit = ((uint8_t)(temperature) / 10) % 10; //converts the floating-point value to an 8-bit unsigned integer by truncating any decimal part. 
        display_on_7_segment_display(tens_digit, segments_pins_tens);

        next_state(temperature, GREEN_PIN, BLUE_PIN, RED_PIN, BUZZER_PIN);
        sleep_ms(500);     
    }
    return 0;
}



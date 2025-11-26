
# Week 2 - Tutorial 2: Analog to Digital Conversion (ADC)

> **Name:** SON CAO
> 
> **Group:** ETI1V.IA
> 
> **Date:** 22/11/2024

## Introduction

This session now will focus on reading analog signals. While you learn about the working principle of analog-to-digital conversion, in Electronic Instrumentation, here we will focus on actually using the ADC peripheral of the Raspberry Pi Pico. We will also learn how to map the read values to a physical quantity and to another range to represent the data on digital outputs (LEDs)

This is the list of needed equipment for this tutorial (everything is included in your kit):
- Raspberry Pi Pico board (with USB cable, headers soldered)
- Breadboard
- Jumper wires
- Resistors
- 1 LED
- 1 Potentiometer
- 2 7-segment displays
- (1 Photoresistor)

## Extra information: Missing code completion in VSCode

VSCode might not find the headers for code completion even with the C/C++ extension installed. To fix this, right click on the not found header (underlined in squiggly red) and click on `Edit includePath setting`. Add the following path to the `includePath` array:

```bash
#{env: PICO_SDK_ PATH}/**
```

## Activity 1: Potentiometer to LED
**Description: Read the value of a potentiometer and display it on in binary**


The analog to digital converter (ADC) is a peripheral that allows us to read analog, continuous, signals and convert them to digital, discrete, values. On a 10-bit ADC the range of output values goes from 0 to 1023, where 0 represents the minimum voltage and 1023 the maximum voltage (reference voltage).

First we will connect a potentiometer to the Pico and read its value. The potentiometer is a variable resistor, that resistance can be changed by turning a knob. The resistor of the potentiometer acts as a voltage divider, so the voltage at the middle pin is proportional to the position of the knob, it goes from 0V to 3.3V (if connect right). Display the value of the potentiometer on an LED with PWM. The LED should be off when the potentiometer is at the minimum value and fully on when the potentiometer is at the maximum value.

Here is sample code to read the value of the potentiometer:

```c
#include "pico/stdlib.h"
#include "hardware/adc.h"

int main() {
    adc_init(); // Initialize the ADC
    adc_gpio_init(26); // Initialize the GPIO pin for the ADC
    adc_select_input(0); // Select the ADC input, channel 0 = pin 26

    while (true) {
        
        uint16_t value = adc_read(); // Read the value of the ADC
        
        // Do something with the value
        sleep_ms(100);
    }
}
```

*Hint: Use the aground pin (pin 33) for the potentiometer for a more stable reading.*

> Question: What is the range of values that you can read from your Pico?
- When the potentiometer is turned to its minimum, the scaled ADC value is 0, and the LED is off.
- When the potentiometer is turned to its maximum, the scaled ADC value is 1023, and the LED is fully bright.

```c
// TODO: include your code here
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

int main() {
    // Initialize ADC for the potentiometer
    adc_init();
    adc_gpio_init(26); // Initialize the GPIO pin for the ADC
    adc_select_input(0); // Select the ADC input, channel 0 = pin 26

    const uint LED_PIN = 15;
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN);
    pwm_set_wrap(slice_num, 1023); // Match the 10-bit ADC range
    pwm_set_gpio_level(LED_PIN, 0); // Start with the LED off
    pwm_set_enabled(slice_num, true);

    while (true) {
        uint16_t value = adc_read(); // Read ADC value (range: 0-1023)

        // Scale ADC value to PWM duty cycle and update LED brightness
        pwm_set_gpio_level(LED_PIN, value);

        sleep_ms(100); 
    }
    return 0;
}
```

## Activity 2: Speed controlled counter
**Description: Control the speed of a counter with a potentiometer**

Now let's control the speed of a binary counter with the potentiometer. Modify/combine your counter code from last week with the potentiometer reading. Your program should control the speed of the counter have two options (choose one of them):

1. The counter should count up depending on the potentiometer value. On the minimum value the counter should stop, at the maximum value the counter should count 100 times a second. In-between the counter should be controlled linearly. (This is the easier option)
2. On the minimum value the counter should count backwards 10 times a second, on the maximum value the counter should count forwards 10 times a second. In-between the counter should be controlled linearly. (This is the harder option)

> Question: How can you derive the delay time from the potentiometer value? Give a formula.

```c
// TODO: include your code here
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
void display_binary_6_LEDs(int number, const uint PIN_LED[6]){
    for(int i = 5; i >= 0; i--){
        gpio_put(PIN_LED[i], number % 2);
        number /= 2;
    }
}

int main() {
    int counter = 640;
    // Initialize ADC for the potentiometer
    adc_init();
    adc_gpio_init(26); // Initialize the GPIO pin for the ADC
    adc_select_input(0); // Select the ADC input, channel 0 = pin 26

    // Set the GPIO pin for the button as input
    const uint PIN_LED[6] = {0, 1, 2, 3, 4, 5};    // TODO: Set the GPIO pin for the LED
    const uint delay = 200;
    // Set the GPIO pin for the LED as output   
    for(int i = 0; i < 6; i++){
        gpio_init(PIN_LED[i]);
        gpio_set_dir(PIN_LED[i], GPIO_OUT);
    }

    while (true) {
        uint16_t value = adc_read(); // Read ADC value (range: 0-4095)

        if(value >= 2049){
            counter++ ;
            display_binary_6_LEDs(counter % 64, PIN_LED);
            sleep_ms(1000 - ((value - 2048) * 900 / 2047));
        } else if (value <= 2048){
            counter--;
            display_binary_6_LEDs(counter % 64, PIN_LED);
            sleep_ms(100 + (value * 900 / 2047));
        }
    }
}
```

## Activity 3: Potentiometer to 7-segment display (sign-off)
**Description: Display the value of a potentiometer on a 7-segment display**

Reading the actual value of the potentiometer is not very useful, as it is just a number between 0 and 4095. Therefore we need to map this value to a physical quantity. The potentiometer is connected to the ADC, which has a resolution of 12 bits, meaning it can read values from 0 to 4095. The voltage range of the ADC is 0 to 3.3V, so the value of the ADC is proportional to the voltage at the input pin. (volt = value * 3.3 / 4095)

To show the measured value in a more human-readable way, we will use 7-segment displays. As you know, a 7-segment display is a common way to display numbers, it consists of 7 LEDs arranged in a specific pattern. By turning on and off the LEDs in the right pattern we can display numbers from 0 to 9. As with all LEDs, we need to use a current limiting resistor to avoid burning them.

To make this activity easier for you we will start by only displaying the value of the potentiometer on one 7-segment display. The potentiometer value goes from 0 to 4095, but we only can to display numbers from 0 to 9. Therefore we need to map the value of the potentiometer to the range 0 to 9. You will need to find the right formula to do this.

> Question: What is the formula to map the value of the potentiometer to the range 0 to 9?
- Since we want an integer result for the 7-segment display, we can use integer division: 
- Mapped value = (Input value * 9) / 4095

> Sign-off: Show your code to your lab teacher or teaching assistant.

*Note: Here is a function to display a number on a common cathode 7-segment display. Test beforehand if your display is of this kind (segment is off when input is 0)*

```c
void display_number(uint number, uint leds[]) {
    if (number > 9) return; // Only display numbers from 0 to 9

    // Define the pattern for each number
    uint pattern[] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};
    // Turn on the right LEDs
    for (int i = 0; i < 7; i++) {
        gpio_put(leds[i], pattern[number] & (1 << i));
    }
}
```

If you are using the 7-segment display with a BCD decoder (remember the Digital module) you can use your 4-bit binary output function from earlier sessions and need less pins.

```c
// TODO: include your code here
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include <stdbool.h>
void setup_led_pin(uint led_pin){
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
}
void display_number(uint number, uint leds[]) {
    if (number > 9) return; // Only display numbers from 0 to 9

    // Define the pattern for each number
    uint pattern[] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};
    // Turn on the right LEDs
    for (int i = 0; i < 7; i++) {
        gpio_put(leds[i], pattern[number] & (1 << i));
    }
}

int main() {
    // Initialize ADC for the potentiometer
    adc_init();
    adc_gpio_init(26); // Initialize the GPIO pin for the ADC
    adc_select_input(0); // Select the ADC input, channel 0 = pin 26

    // Set the GPIO pin for the button as input
    const uint PIN_LED[8] = {13, 12, 18, 17, 16, 14, 15, 19};   // TODO: Set the GPIO pin for the LED of 7-segmentation (0 to 6 = LED on 7 segmentation, 7 = DP)
    // Set the GPIO pin for the LED as output   
    for(int i = 0; i < 8; i++){
        setup_led_pin(PIN_LED[i]);
    }

    while (true) {
        uint16_t value = adc_read() * 9 / 4095; //Scale the raw ADC reading (range: 0–4095) to a smaller range (0–9). This makes the potentiometer control a single-digit display, such as a 7-segment LED.
        display_number(value, PIN_LED);
        sleep_ms(100);    
    }
}
```
> Extra challenge: Display the voltage measured on two 7-segment displays. The first display should show the integer part of the value and the second display should show the decimal part of the value.

## Activity 4: Internal temperature sensor (optional)
**Description: Read the internal temperature sensor of the Pico**

The Pico has an interesting feature, it has an internal temperature sensor. This sensor is not very accurate, but it can be useful for some applications, mainly to detect if the Pico is overheating. The temperature sensor is directly connected to the ADC and can be read like any other analog signal. Just select the ADC input 4, furthermore the temperature sensor needs to be enabled with `adc_set_temp_sensor_enabled(true);`. The value of the temperature sensor is not in degrees Celsius, but in a value that needs to be converted to degrees Celsius. The formula to convert the value to degrees Celsius is:

```
temperature = 27 - (voltage - 0.706) / 0.001721
```

Read the value of the internal temperature sensor and display it on two 7-segment display. The value should be updated every second.

```c
// TODO: include your code here
// TODO: include your code here
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include <stdbool.h>
void setup_led_pin(uint led_pin){
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
}
void display_number(uint number, uint leds[]) {
    if (number > 9) return; // Only display numbers from 0 to 9

    // Define the pattern for each number
    uint pattern[] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};
    // Turn on the right LEDs
    for (int i = 0; i < 7; i++) {
        gpio_put(leds[i], pattern[number] & (1 << i));
    }
}

int main() {
    // Initialize ADC for the potentiometer
    adc_init();
    adc_gpio_init(28); // Initialize the GPIO pin for the ADC
    adc_select_input(4); // Select the ADC input, channel 4 = pin 28
    adc_set_temp_sensor_enabled(true);

    // Set the GPIO pin for the button as input
    const uint PIN_LED1[8] = {13, 12, 18, 17, 16, 14, 15, 19};    // TODO: Set the GPIO pin for the LED1
    const uint PIN_LED2[8] = {}; // TODO: Set the GPIO pin for the LED2
    // Set the GPIO pin for the LED as output   
    for(int i = 0; i < 8; i++){
        setup_led_pin(PIN_LED1[i]); //displaying the tens
        setup_led_pin(PIN_LED2[i]); //displaying the ones
    }

    while (true) {
        float voltage = adc_read() * 3.3f / 4095.0f; //Scale the raw ADC reading (range: 0–4095) to a voltage range (0–3.3V). This makes the    potentiometer control a single-digit display, such as a 7-segment LED.
        uint temperature = 27 - (voltage - 0.706) / 0.001721; //The formula to convert the value to degrees Celsius
        display_number(temperature / 10, PIN_LED1);
        display_number(temperature % 10, PIN_LED2);
        sleep_ms(100);    
    }
}
```

## Questions to answer:

Please answer this reflection questions:

1. How long did this tutorial take you?
- 3 days
3. Did you face difficulties?
- yes, a lot
4. What would you like to see improved?
- maybe giving some more examples before starting the actual programs

## Sign-off

Please show your code of activity 3 to your lab teacher or teaching assistant.
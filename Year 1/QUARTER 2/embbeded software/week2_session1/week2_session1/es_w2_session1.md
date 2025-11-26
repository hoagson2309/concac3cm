# Week 2 - Session 1: Time and Pulse Width Modulation (PWM)

> **Name:** SON CAO
> 
> **Group:** ETI1V.IA
> 
> **Date:** 20/11/2024

## Introduction

In this tutorial, we will see how time influences the behavior of a system. We will also learn about Pulse Width Modulation (PWM) and how to use it to control the brightness of an LED.

This is the list of needed equipment for this tutorial (everything is included in your kit):
- Raspberry Pi Pico board (with USB cable, headers soldered)
- Breadboard
- Jumper wires
- Resistors
- 1 LED

While your computer has a clock that keeps track of absolute time, often embedded systems do not. This means that the Pico does not know what time it is. However, we can use the Pico to keep track of relative time, for this the microcontroller has built-in timers that count the number of clock cycles that have passed. We can use these timers to keep track of time passing, or to generate signals with specific properties.

## Activity 1: Blink without sleep
**Description: Blink an LED without using the sleep function**

You might have already noticed that the `sleep_ms()` function is not the best way to control time in an embedded system. It is blocking, which means that the program stops until the time is up. This is usually not a problem for small delays, but it can be a problem for longer delays, as you are not able to do anything else during that time. We will now rewrite the blinking LED program without using the `sleep_ms()` function. Take the blinking LED program (template project) and try to reimplement it using the elapsed time since the startup. 

> Question: Why is the blinking rate of our LED not exactly 1 Hz, when using the `sleep_ms(1000)` function?

You will need to function:  `time_us_32 (void)` - This function returns the time in microseconds since the Pico started. (*Note: This wraps around every 71 minutes, so be careful when using it for long periods of time.*)

*Hint: Calculate when the LED should change state and check if this point in time has passed.*

```c
// TODO: include your code here
// TODO: include your code here
#include "pico/stdlib.h" // Standard library for Pico

int main() {
    // Set up the LED pin 15 / physical pin 20
    const uint LED_PIN = 15;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Never-ending superloop
    uint previous_time = 0;
    uint current_time;
    const uint delay = 1000;

    while (true) {
        //check if the time is elapsed
        current_time = to_ms_since_boot(time_us_32());
        if(current_time - previous_time >= delay){
            gpio_put(LED_PIN, !gpio_get(LED_PIN));
            previous_time = current_time;
        }
    }
    return 0;
}
```

## Activity 2: Blink and direct light
**Description: Combinate the blinking LED with direct light activity**

Now connect a button and a second LED to the Pico. Change your code so that the first LED blinks as before, but when the button is pressed the second LED should light up. When the button is released the second LED should turn off (see activity 0 of last session).

> Question: Would this be possible with the `sleep_ms` function? Why?

```c
// TODO: include your code here
#include "pico/stdlib.h" // Standard library for Pico
void set_up_led(uint LED_PIN){
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

int main() {
    // Set up the LED pin 15 / physical pin 20
    // Set the GPIO pin for the LED as output
    const uint LED_PIN1= 15;
    set_up_led(LED_PIN1);
    const uint LED_PIN2= 13;
    set_up_led(LED_PIN2);
    const uint PIN_BUTTON = 14;
    
    // Set the GPIO pin for the button as input
    gpio_init(PIN_BUTTON);
    gpio_set_dir(PIN_BUTTON, GPIO_IN);
    gpio_pull_down(PIN_BUTTON);

    // Never-ending superloop
    uint previous_time = 0;
    uint current_time;
    const uint delay = 1000;
    while (true) {
        //check if the time is elapsed
        current_time = to_ms_since_boot(time_us_32());
        if(current_time - previous_time >= delay){
            gpio_put(LED_PIN2, !gpio_get(LED_PIN2));
            previous_time = current_time;
        }

        bool button_state = gpio_get(PIN_BUTTON);
        if (button_state == 1)
        {
            gpio_put(LED_PIN1, true);
        } else{
            gpio_put(LED_PIN1, false);
        }
        current_time = to_ms_since_boot(time_us_32());
        if(current_time - previous_time >= delay){
            gpio_put(LED_PIN1, !gpio_get(LED_PIN1));
            previous_time = current_time;
        }
    }
    return 0;
}
```

## Activity 3: Manual PWM control --> PWM peripheral
**Description: Control the brightness of an LED with a loop**

In this sessions introduction you heard an explaination of PWM. Now we will try to control the brightness of an LED by changing the duty cycle of a square wave. First we, will do this manually by changing the state of the LED in a loop. Later we will use the PWM peripheral of the Pico to do this automatically.

### Part 1: Manual PWM

To better understand PWM we will first implement a manual PWM control for a 50% duty cycle. Start with the template project again. Now experiment with the sleep time of the LED. Start out with a sleep time of 1000 microseconds and keep decreasing the sleep time until you can't see the LED blinking anymore. 

> Question: What is the shortest sleep time you can use and still see the LED blinking?
> 20ms

Afterwards add a second LED that is always on. Include your final code below.

```c
// TODO: include your code here
// TODO: include your code here
// TODO: include your code here
#include "pico/stdlib.h" // Standard library for Pico

int main() {
    // Set up the LED pin 15 / physical pin 20
    const uint LED_PIN = 13;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Never-ending superloop
    uint previous_time = 0;
    uint current_time;
    const uint delay = 5;

    while (true) {
        //check if the time is elapsed
        current_time = to_ms_since_boot(time_us_32());
        if(current_time - previous_time >= delay){
            gpio_put(LED_PIN, !gpio_get(LED_PIN));
            previous_time = current_time;
        }
    }
    return 0;
}
```

> Can you see the difference in brightness between the two LEDs?
- yes, the LED_PIN = 15 is likely to be brighter than the LED_PIN = 13

### Part 2: PWM peripheral

Now we will use the PWM peripheral of the Pico to control the brightness of the LED. The PWM peripheral generates a square wave with a specific duty cycle. The duty cycle is the percentage of time the signal is high. To use the PWM peripheral we need to configure it first. We will use the `pwm_set_gpio_level` function to set the duty cycle of the PWM signal. Here is the code to get you started, copy it to your project and check if it is working.

```c
#include "pico/stdlib.h" // Standard library for Pico
#include "hardware/pwm.h" // Hardware PWM library

int main() {
    // Set up the LED pin 15 / physical pin 20
    const uint LED_PIN = 15;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    const uint SLEEP = 100;

    // Tell GPIO_PIN it is allocated to the PWM
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    // Get the slice number for the GPIO_PIN
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN);
    
    // Set period of 4 cycles (0 to 3 inclusive)
    pwm_set_wrap(slice_num, 3);
    // Set level to high for 1 slice (2/4 = 50% duty cycle)
    pwm_set_gpio_level(LED_PIN, 2);
    // Set the PWM running     
    pwm_set_enabled(slice_num, true);

    // Never-ending superloop
    while (true) {
        sleep_ms(SLEEP);
    }
}
```

> Question: Do you see a difference in brightness compared to the manual PWM control?
- Yes, it seems much dimmer
### Part 3: PWM peripheral (cont.)

Finally take the code and experiment with the duty cycle. Try to set the duty cycle to 0%, 25%, 50%, 75% and 100%.

> Question: What happens if you set the duty cycle to 0% or 100%?
- at 0% it didn't bright up, at 100% it light almost the same as normally light
> Question: Can you think of another device that might use PWM to control its behavior?
- LED Brightness Control
## Activity 4: PWM - Slowly changing brightness (sign-off)
**Description: Slowly change the brightness of an LED**

The concept of PWM is even more powerful when we can change the duty cycle of the square wave during a running program. We will now implement a program that slowly changes the brightness of an LED. The LED should start at 0% brightness and slowly increase to 100% brightness over 2 seconds. After reaching 100% brightness the LED should slowly decrease to 0% brightness over 5 seconds. The LED should then start increasing in brightness again.

```c
// TODO: include your code here
#include "pico/stdlib.h" // Standard library for Pico
#include "hardware/pwm.h" // Hardware PWM library

int main() {
    // Set up the LED pin 15 / physical pin 20
    const uint LED_PIN = 15;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    const uint SLEEP = 100;

    // Tell GPIO_PIN it is allocated to the PWM
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    // Get the slice number for the GPIO_PIN
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN);
    
    // Set period of 100 cycles (0 to 99 inclusive)
    pwm_set_wrap(slice_num, 99);
    // Set level to high for 1 slice (0% duty cycle)
    pwm_set_gpio_level(LED_PIN, 0);
    // Set the PWM running     
    pwm_set_enabled(slice_num, true);

    // Never-ending superloop
    while (true) {
       for (int i = 0; i <= 100; i++)
       {
        pwm_set_gpio_level(LED_PIN, i);
        sleep_ms(2000/100);
       }
       for(int i = 100; i >= 0; i--){
        pwm_set_gpio_level(LED_PIN, i);
        sleep_ms(5000/100);
       }
        
        sleep_ms(SLEEP);
    }
}
```

> Sign-off: Show your code to your lab teacher or teaching assistant.

## Activity 5: PWM RGB Control. (optional)
**Description: Control the Color of an RGB LED**

If you are done with the previous activities, you can try to control the color of an RGB LED. You can get one by asking your lab teacher. The RGB LED has four pins, one for each color (Red, Green, Blue) and one for the common cathode, look online to know which is which. You can control the color of the LED by changing the brightness of each color hue. 

*Note: Don't forget to add a resistor to each color pin to limit the current (470 Ohm should be fine).*

We will implement a mood light, that slowly changes the color of the RGB LED. The LED should change it's color to a random color every 10 seconds, but the transition should be smooth over 2 seconds. 

*Hint: You can use the `pico_rand()` function to get a random number.*

> Question: Why would the "normal" `rand()` workflow we used in Programming 1 not work well on the Pico? Hint: We call `srand(current time)` to seed the random number generator.

```c
// TODO: include your code here
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
```

## Questions to answer:
Please answer this reflection questions:

1. How long did this tutorial take you?
- 8 hours
2. Did you face difficulties?
- Yes, at the beginning i didn't know what to do but then I finally figured it out
3. What would you like to see improved?
- The last activity

## Sign-off

Please show your code of activity 4 to your lab teacher or teaching assistant.

# Week 1 - Tutorial 2: Digital Inputs (buttons)

> Name: SON CAO
>
> Group: ETI1V.IA
>
> Date: 14/11/2024

## Introduction

Welcome to the second tutorial of the Embedded Software course. In this tutorial, we will learn how to read digital inputs using buttons. We will deal with a common issue of button presses: bouncing. Also, we will practice keeping track of the state in a function with static variables.

This is the list of the equipment needed for this tutorial:
- RaspberryPi Pico board (with USB cable, headers soldered)
- Breadboard
- Jumper wires
- 4 LEDs
- 2 Buttons
- Resistors

## Activity 0 - Direct Light
**Description: Light an LED with a button press**

We start easy: Connect a button to the Raspberry Pi Pico to one of your GPIO pins (not GP0 or GP1). Connect an LED to another GPIO pin. When the button is pressed the LED should light up. When the button is released the LED should turn off.

> **TODO:** *Question: Why are we not using GP0 or GP1?*
> - We avoid using GP0 and GP1 on the Raspberry Pi Pico because they are typically reserved for serial communication (UART0, TX and RX). Using them for other functions, like a button or LED, can interfere with serial debugging and USB communication, which are essential for programming and monitoring the Pico.

*Note: We will use internal pull-down resistors during this session, you learn more about pull-up and pull-down registers in Electronic Instrumentation*

In the following code snippet, you can see the basic code to read the button and light the LED. Fill in the missing GPIO pin numbers and test your program. When you are done you can continue with the next activity.

```c
#include "pico/stdlib.h"

int main() {
    const uint PIN_BUTTON = ; // TODO: Set the GPIO pin for the button
    const uint PIN_LED = ; // TODO: Set the GPIO pin for the LED

    // Set the GPIO pin for the button as input
    gpio_init(PIN_BUTTON);
    gpio_set_dir(PIN_BUTTON, GPIO_IN);
    gpio_pull_down(PIN_BUTTON);

    // Set the GPIO pin for the LED as output
    gpio_init(PIN_LED);
    gpio_set_dir(PIN_LED, GPIO_OUT);

    while (true) {
        // Read the button state and light the LED
        bool button_state = gpio_get(PIN_BUTTON);
        gpio_put(PIN_LED, button_state);
    }

    return 0;
}
```

## Activity 1 - Fast blink slow blink
**Description: Blink an LED fast or slow with a button press**

Now we will combine the button press with the blinking LED from the last session. When the button is pressed the LED should blink fast (4 times per second). When the button is released the LED should blink slowly (1 time per second). You do not need to implement extra functions for this activity.

*Note: Try to use only use two calls to `gpio_put`.*

```c
// TODO: include your code here
#include "pico/stdlib.h"
int main()
{
    const uint PIN_BUTTON = 14; // TODO: Set the GPIO pin for the button
    const uint PIN_LED = 15;    // TODO: Set the GPIO pin for the LED
    const uint delay = 250;
    const uint delay2 = 1000;
    // Set the GPIO pin for the button as input
    gpio_init(PIN_BUTTON);
    gpio_set_dir(PIN_BUTTON, GPIO_IN);
    gpio_pull_down(PIN_BUTTON);

    // Set the GPIO pin for the LED as output
    gpio_init(PIN_LED);
    gpio_set_dir(PIN_LED, GPIO_OUT);

    while (true)
    {
        // Read the button state and light the LED
        bool button_state = gpio_get(PIN_BUTTON);
        if (button_state == 1)
        {
            gpio_put(PIN_LED, true);
            sleep_ms(delay);
            gpio_put(PIN_LED, false);
            sleep_ms(delay);
        }
        else
        {
            gpio_put(PIN_LED, true);
            sleep_ms(delay2);
            gpio_put(PIN_LED, false);
            sleep_ms(delay2);
        }
    }

    return 0;
}
```

## Activity 2 - Light Switch
**Description: Toggle an LED on button press**

Until now the button was stateless, it only triggered a direct action. Now we will implement a light switch. When the button is pressed the LED should toggle its state. This means if the LED is on it should turn off and if the LED is off it should turn on. We only want to change the state of the LED when the button is pressed, not when it is released. Furthermore it should not keep changing the state while the button is pressed. For this refer to the lecture part. Again, you can do this directly in the main superloop.

```c
// TODO: include your code here
#include "pico/stdlib.h"
int main()
{
    const uint PIN_BUTTON = 14; // TODO: Set the GPIO pin for the button
    const uint PIN_LED = 15;    // TODO: Set the GPIO pin for the LED
    const uint delay = 50;
    // Set the GPIO pin for the button as input
    gpio_init(PIN_BUTTON);
    gpio_set_dir(PIN_BUTTON, GPIO_IN);
    gpio_pull_down(PIN_BUTTON);

    // Set the GPIO pin for the LED as output
    gpio_init(PIN_LED);
    gpio_set_dir(PIN_LED, GPIO_OUT);

    bool led_state = false;
    bool previous_state = false;
    while (true)
    {
        // Read the button state and light the LED
        bool button_state = gpio_get(PIN_BUTTON);
        if (button_state && !previous_state)
        {
            led_state = !led_state;
            gpio_put(PIN_LED, led_state);
        }
        previous_state = button_state; //This ensures the toggle happens only once per press (and release)
       sleep_ms(delay);
    }
    return 0;
}
```

## Activity 3 - Counter (sign-off)
**Description: Binary count up with a (debounced) button**

Last session you learned how to implement a binary time counter. This week we will instead count buutton presses. We will also implement a debounce mechanism to make sure that the button presses are registered correctly.

### Part 1 - Counting presses

Your goal is to implement a counter that counts up by one every time the button is pressed. The counter should be displayed on 4 LEDs in binary. The counter should be able to count from 0 to 15 and then wrap around to 0 again. 

*Note: Reuse the binary output function from activity 3 in session 1.*

```c
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
    }
    return 0;
}   

```

### Part 2 - Debouncing

If you have not implemented a debounce mechanism yet you might notice that button presses are not always registered correctly, some presses might be registered multiple times. To deal with that issues implement a software debounce mechanism, you can use `sleep_ms` to wait for the button to stabilize. The actual wait time depends on the button you are using, you might need to experiment a bit to find the right value (you can start with 50ms).

```c
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
```

> TODO: As debouncing is an important topic in embedded systems you should show your implementation to a teacher or TA to get a sign-off!

## Activity 4 - Light Switch (continued)
**Description: Toggle an LED on button press**

The final topic of today is keeping track of state within functions. We will modify the light switch activity, so copy your code to a new project directory and continue from there.

### Part 1 - Passing state

Implement the function `toggle_led` that toggles the state of the LED. The function should be called with the current state of the LED and return the new state of the LED. Call it from your main superloop. For this one time you are allowed to use a magic number for the LED pin.

```c
/// Toggle the state of the LED (ON-OFF)
/// @param led_state Current state of the LED
/// @return New state of the LED
bool toggle_led(bool led_state);
```

```c
// TODO: include your code here
#include "pico/stdlib.h"
/// Toggle the state of the LED (ON-OFF)
/// @param led_state Current state of the LED
/// @return New state of the LED
bool toggle_led(bool led_state);
bool toggle_led(bool led_state){
    return !led_state;
}
int main()
{
    const uint PIN_BUTTON = 14; // TODO: Set the GPIO pin for the button
    const uint PIN_LED = 15;    // TODO: Set the GPIO pin for the LED
    const uint delay = 50;
    // Set the GPIO pin for the button as input
    gpio_init(PIN_BUTTON);
    gpio_set_dir(PIN_BUTTON, GPIO_IN);
    gpio_pull_down(PIN_BUTTON);

    // Set the GPIO pin for the LED as output
    gpio_init(PIN_LED);
    gpio_set_dir(PIN_LED, GPIO_OUT);

    bool led_state = false;
    bool previous_state = false;
    while (true)
    {
        // Read the button state and light the LED
        bool button_state = gpio_get(PIN_BUTTON);
        if (button_state && !previous_state)
        {
            led_state = toggle_led(led_state);
            gpio_put(PIN_LED, led_state);
        }
        previous_state = button_state; //This ensures the toggle happens only once per press (and release)
       sleep_ms(delay);
    }
    return 0;
}
```

### Part 2 - Static state

Now change your code to keep the state of the LED in a static variable. This means you should not pass the state of the LED to or from the function `toggle_led` anymore.

> Question: What is the advantage of keeping the state of the LED in a static variable instead of passing a global variable?

```c
/// Toggle the state of the LED (ON-OFF)
void toggle_led(void);
```

```c
// TODO: include your code here
#include "pico/stdlib.h"
/// Toggle the state of the LED (ON-OFF)
void toggle_led(void);
void toggle_led(void){
    static bool led_state = false;
    led_state = !led_state;
    gpio_put(15, led_state);
}
int main()
{
    const uint PIN_BUTTON = 14; // TODO: Set the GPIO pin for the button
    const uint PIN_LED = 15;    // TODO: Set the GPIO pin for the LED
    const uint delay = 50;
    // Set the GPIO pin for the button as input
    gpio_init(PIN_BUTTON);
    gpio_set_dir(PIN_BUTTON, GPIO_IN);
    gpio_pull_down(PIN_BUTTON);

    // Set the GPIO pin for the LED as output
    gpio_init(PIN_LED);
    gpio_set_dir(PIN_LED, GPIO_OUT);

    bool led_state = false;
    bool previous_state = false;
    while (true)
    {
        // Read the button state and light the LED
        bool button_state = gpio_get(PIN_BUTTON);
        if (button_state && !previous_state)
        {
            toggle_led;
        }
        previous_state = button_state; //This ensures the toggle happens only once per press (and release)
       sleep_ms(delay);
    }
    return 0;
}
```

> Extra challenge: Can you move the button functionality into a separate function as well? (+debouncing)
> -yes, why not?

## Extra Information: Easier upload (optional)

If you are tired of dragging and dropping the `.uf2` file to your Raspberry Pi Pico you can use the following command to upload your program to the board you can use picotool in the terminal. This sets the board into bootloader mode and uploads the program to the board and resets it.

```bash
picotool load -f program_binary.uf2
```

There is a little catch to this method. The program currently running needs to be stopped via USB and this can only be done if the program currently running called `stdio_init_all();` in the `main()` function. So make sure to add this line at the beginning of your `main()` function in all your programs.

## Activity 5 - Timed Light Switch (optional)
**Description: Staircase lightswitch with long on function when long-pressed**

Every week we try to give you at least one activity with a relation to the real world. This week we will implement a timed light switch.

In apartment buildings, you often find light switches in staircases that turn on the light for a certain amount of time. This is useful when you are going up the stairs and do not want to turn off the light manually. When doing work in the staircases you might want to turn on the light for a longer period of time. This is often done by long-pressing the light switch. You should now implement this behavior with a button and an LED.

When the button is pressed the LED should turn on for one second and then turn off. When the button is long-pressed (let's say 500ms) the LED should turn on for 15 seconds and then turn off.

```c
// TODO: include your code here
#include "pico/stdlib.h"

int main()
{
    const uint PIN_BUTTON = 14; // TODO: Set the GPIO pin for the button
    const uint PIN_LED = 15;    // TODO: Set the GPIO pin for the LED
    const uint delay = 50;
    const uint delay0 = 1000;
    const uint delay1 = 500;
    const uint delay2 = 15000;


    // Set the GPIO pin for the button as input
    gpio_init(PIN_BUTTON);
    gpio_set_dir(PIN_BUTTON, GPIO_IN);
    gpio_pull_down(PIN_BUTTON);

    // Set the GPIO pin for the LED as output
    gpio_init(PIN_LED);
    gpio_set_dir(PIN_LED, GPIO_OUT);

    bool led_state = false;
    bool previous_state = false;
    while (true)
    {
        // Read the button state and light the LED
        bool button_state = gpio_get(PIN_BUTTON);
        if (button_state && !previous_state)
        {
            if(button_state){ //if 1
                sleep_ms(delay1); // delay 500ms
                if(button_state){ // if still 1
                    gpio_put(PIN_LED, true);
                    sleep_ms(delay2); //15s
                    gpio_put(PIN_LED, false);
                } else{ //otherwise
                    gpio_put(PIN_LED, true);
                    sleep_ms(delay0); //1s
                    gpio_put(PIN_LED, false);
                }
            }
        }
        previous_state = button_state; //This ensures the toggle happens only once per press (and release)
       sleep_ms(delay); //debouncing
    }
    return 0;
}
```

## Questions to answer:
 
> Please answer the following reflection questions:
> 
> 1. How long did this tutorial take you?
> 8 hours
> 2. Did you face difficulties?
> Yes, i used to face some challenges with light switch and toggle button at first
> 3. What would you like to see improved?
# Week 3 - Session 1: Serial Communication

> **Name:** SON CAO
> 
> **Group:** ETI1V.IA
> 
> **Date:** 27/11/2024

## Introduction

During this session, you will learn how to communicate from the Raspberry Pi Pico to your computer using the serial communication protocol. This is a simple way to send data from the Pico to your computer, and vice versa.

This is the list of needed equipment for this tutorial (everything is included in your kit):
- Raspberry Pi Pico board (with USB cable, headers soldered)
- Breadboard
- Jumper wires
- Potentiometer
- 1 LED

Until now we were only able to see the output of our programs on LEDs or other peripherals. With serial communication, we can send data to our computer and see it on the terminal. This is useful for debugging, logging data, or even controlling the Pico from your computer. We will use the already familiar `printf()` function to send data to the computer and the `getchar()` function to read data character by character.

## Activity 0: Hello World*
**Description: Print a "Hello World!"0 message to the computer terminal**

First, we will set up the serial communication. We will use the USB port of the Pico to communicate with the computer. The USB port is connected to the UART peripheral of the Pico. We will use the functions `stdio_init_all()` to initialize the serial communication and `printf()` to send data to the computer. On the computer side we will use PuTTY to see the data sent by the Pico (if you are using Windows).

```c
#include "pico/stdlib.h"
#include <stdio.h> // Remember this: it is also needed for embedded printf and scanf

int main() {
    stdio_init_all(); // Initialize the serial communication

    while (true) {
        printf("Hello World!\n"); // Print a message to the computer terminal
        sleep_ms(1000); // Sleep for 1 second
    }
}
```

Compile and run the code on the Pico.

Now let us install and configure PuTTY to see the data sent by the Pico:
1. Download and install PuTTY from [here](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html)
2. Look for the COM port of the Pico in the Windows device manager, under `Ports`, it will show up as USB Serial Device. (*Note: Try to always use the same USB port when to avoid changing the COM port*).
3. Open PuTTY and select the Serial connection type, fill the following fields:
    - Serial line: COMX (where X is the number of the COM port)
    - Speed: 115200
4. Click on `Open` to open the connection.

You should now see the message "Hello World!" on the PuTTY terminal.

### Notes for Mac and Linux users
**Not officially supported: Teachers might not be able to help you with this.**

If you are using Mac or Linux, you can use the terminal to see the data sent by the Pico. The Pico will show up as a serial device in `/dev/` with the name `ttyACM0` or `/dev/tty.usbmodemxxxxx` (if needed check by running the command `ls /dev/tty*` to see all devices). You can use the `screen` command to see the data sent by the Pico. Open a terminal and type the following command:

```bash
screen /dev/ttyACM0 115200
```

## Activity 1: Voltage reading to Serial
**Description: Read the value of a potentiometer and send it to the computer**

Now we will read the value of a potentiometer and send it to the computer. We will use the `printf()` function to send the value to the computer. Reuse the code from the previous session to read the value of the potentiometer, afterwards calculate the voltage (0-3.3V, remember last session) and send it to the computer with an accuracy of 2 digits after the comma. Update the value every 500ms.

Example output:
``` 
...
Current reading is: 1.53 Volt
Current reading is: 1.58 Volt
...
```

```c
// TODO: include your code here
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <stdio.h> // Remember this: it is also needed for embedded printf and scanf

int main() {
    stdio_init_all(); // Initialize the serial communication
    adc_init(); // Initialize ADC for the potentiometer
    adc_gpio_init(26); // Initialize the GPIO pin for the ADC
    adc_select_input(0); // Select the ADC input, channel 0 = pin 26
    while (true) {
        uint16_t adc_value = adc_read();
        float voltage = adc_value * 3.3f / 4095.0f;
        printf("Current reading is: %.2f\n", voltage); // Print a message to the computer terminal
        sleep_ms(500); 
    }
}   
```

> Question: Why does the potentiometer not read 0V when it is at the minimum value (and 3.3V at it's maximum)?
- The potentiometer may not read 0V or 3.3V due to wiring, ADC resolution, internal resistance, or circuit noise.

## Activity 2: Mirror mirror on the wall..
**Description: Read a string from the computer and send it back**

Next, we will start receiving data from the computer. We will use the `scanf()` function to read the data sent by the computer. You will learn more about input functions in programming 2. For now it is enough to know that `scanf()` reads data from the standard input and stores it in a variable. The function has the following syntax for reading a string (a sequence of characters until a whitespace is found):

```c
char buffer[100]; // Create a buffer to store the string
scanf("%s", buffer); // Read a string from the computer
```

*Note: For now we will not handle errors, so be careful with the input you send to the Pico.*

Implement a program that reads a string from the computer and sends it back. The program should read the string and print it back to the computer with the length in parenthesis added to it. The program should run indefinitely. To solve this problem, remember the string functions you used in Programming 1.

```c
// TODO: include your code here
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <stdio.h> // Needed for printf and scanf
#include <string.h>

int main() {
    stdio_init_all(); // Initialize the serial communication
    char buffer[100]; // Create a buffer to store the string
    
    while (true) { // Infinite loop to keep the program running
        scanf("%s", buffer); // Read a string from the computer
        int length = strlen(buffer); // Calculate the length of the string
        printf("%s (%d)\n", buffer, length); // Print the string and its length
        sleep_ms(500); // Sleep for 500 ms
    }
    return 0;
}

```

Example input:
```
Hello
thisisalongstring
...
```

Example output:
```
Hello (5)
thisisalongstring (17)
...
```

## Activity 3: Serial commands to control an LED
**Description: Control the brightness of an LED using serial commands**

In this activity, we will control the brightness of a LED using serial commands. We will read the serial input from the computer and change the brightness of the LED accordingly. The input will be a number between 0 and 9.

You can again use the `scanf()` function to read the input from the computer. Alternatively, you can use the `getchar()` function to read the input character by character. The function `getchar()` reads a single character from the computer. You can use it to read the input character by character and convert it to a number (or something else for more complex inputs). Watch out, special characters like the newline character (`\n`) are also read by `getchar()`. Also remember that the input is interpreted as a character, so you need to convert it to a number.

```c
// TODO: include your code here
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include <stdio.h> // Needed for printf and scanf
#include <string.h>
int main() {
    stdio_init_all(); // Initialize the serial communication

    const uint LED_PIN = 0;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

     // Tell GPIO_PIN it is allocated to the PWM
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    // Get the slice number for the GPIO_PIN
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN);
    
    // Set PWM wrap value for 8-bit resolution (0-255)
    pwm_set_wrap(slice_num, 8);
    // Set the PWM running     
    pwm_set_enabled(slice_num, true);
    
    while (true) { // Infinite loop to keep the program running
        int number;
        printf("Enter a number from 0 - 9: ");
        scanf("%d", &number);
        if(number >=0 && number <=9){   
            pwm_set_gpio_level(LED_PIN, number);
        }
    sleep_ms(500); // Sleep for 500 ms
    }
}

```

## Activity 4: Two-way communication (sign-off)
**Description: Send and receive data from the computer (simultaneously)**

Finally combine the previous activities to send and receive data from the computer. You should still be able to change the brightness of the LED (activity 4) while sending the voltage reading from the potentiometer every 500ms (activity 1) to the computer.

To reach this goal you will need to use the non-blocking version of `getchar()` defined in the SDK: `getchar_timeout_us(uint32_t timeout_us)`. This function waits for a character for a certain amount of time and returns `PICO_ERROR_TIMEOUT` if no character is received. If this is the case, just keep the brightness of the LED the same.

For a non-blocking reading of the adc you can take a look at the non-blocking blink of last week, that might help you.

```c
// TODO: include your code here
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include <stdio.h> // Needed for printf and scanf
#include <string.h>
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

    pwm_set_wrap(slice_num, 9);
    // Set the PWM running     
    pwm_set_enabled(slice_num, true);
    
    while (true) { // Infinite loop to keep the program running
        int number = getchar_timeout_us(0);
        printf("Enter a number from 0 - 9: \n");
        scanf("%d", &number);
        if(number >=0 && number <=9){   
            pwm_set_gpio_level(LED_PIN, number);
        }
        uint16_t value = adc_read();
        float voltage = value * 3.3f / 4095.0f;
        printf("Potentiometer Voltage: %.2f V\n", voltage);
    
    sleep_ms(500); // Sleep for 500 ms
    }
}

```

## Activity 5: Non-Blocking scanf (optional, mandatory for 10 points)
**Description: Implement a non-blocking scanf with stdio_getchar_timeout_us**

A note ahead: This activity tests your understanding of arrays and strings. If you are not comfortable with these topics, you might have a hard time solving this activity. You will also need to use static variables.

In the previous activities, we used the blocking function `scanf()` to read the input from the computer. This function waits for the input to be received before continuing. This is not always the best solution, especially if you want to do other things in the meantime. You used the non-blocking function `getchar_timeout_us()` to read the input character by character. Now we will implement a non-blocking function similar to `scanf()` using this `getchar_timeout_us()`. Your new function `bool scanf_non_blocking(char* destination)` should keep reading characters int the destination until a space is found (you do not have to deal with buffer overflow, assume that it is big enough). If a space is found, the function should return TRUE, otherwise FALSE. Don't forget terminating the string at the end.

To prove that it works, change activity 4 in a way that the LED brightness can be changed in the range of 0-999. Also output the received number to the computer.

```c
// TODO: include your code here
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)
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
        if(scanf_non_blocking(input_buffer)){ //if input is complete
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
```

## Questions to answer:
Please answer these reflection questions:

1. How long did this tutorial take you?
2. Did you face difficulties?
3. What would you like to see improved?

## Sign-off

Please show your code of activity 4 to your lab teacher or teaching assistant.
# Week 3 - Session 2: Advanced Communication

> **Name:** SON CAO
> 
> **Group:** ETI1V.IA
> 
> **Date:** 2/12/2024

## Introduction

In today's session we will see how the Raspberry Pi Pico can communicate with other devices. We will not focus on the actual communication protocol, but rather see that we can use libraries available on the internet. Later we will also connect two Picos and let them communicate with each other.

This is the list of needed equipment for this tutorial (everything is included in your kit):
- Raspberry Pi Pico board (with USB cable, headers soldered)
- Breadboard
- Jumper wires
- DHT22 or similar temperature sensor
- 1 LED

## Activity 1: Example library usage
**Description: Use a library example to read data from a sensor**

When building a system you will often not only connect passive sensors like potentiometers or buttons, but also active sensors like temperature sensors, accelerometers, or gyroscopes. These sensors have a digital interface to communicate with the microcontroller and send data. In the datasheet of the sensor you can find which protocol the sensor uses and how to communicate with it. Often this is quite complex, but luckily there are libraries that can help us with this. Manufacturers often provide libraries to communicate with their sensors, but there are also open-source libraries. Especially for hobbyist components like the temperature sensor we will use today, other users have written libraries or driver code that can be used freely. Remember that you should always check the license of the code you use and give credit to the original author, if required. Also never trust the code you find to fully work, other engineers might have used the code in a different way or simply made a mistake.

To show you how to use a library, we will use the DHT22 temperature sensor. This sensor is a digital sensor that uses a single wire to communicate with the microcontroller. The sensor sends a signal to the microcontroller that contains the temperature and humidity. The sensor is quite easy to use, but the protocol is a bit complex. We will therefore use the library `pico_dht` by Valentin Milea that is available on GitHub. You can find it [here](https://github.com/vmilea/pico_dht). Note: It is available under the MIT license, so you can use it freely, but you should give credit to the author and include the license in your project. Companies often buy libraries or have them developed by their engineers, but the overall idea is the same.

The first step after finding a library is to check the documentation, usually starting with the README file. This file should contain information on how to install the library, how to use it, and what functions are available. In the case of the `pico_dht` library, the README file focuses on running the included example code. This is a good starting point to see if the library works and how to use it. So let's start by running the example code:
- Clone the repository to your computer: `git clone https://github.com/vmilea/pico_dht.git`
- Enter the directory: cd `pico_dht`
- Change `DHT_MODEL` in `dht_example.c` if needed (default is DHT22, the one we have in the kit)
- Build the example code: `mkdir build, cd build, cmake .., make`
- Connect the sensor to the Pico:
    - Pin 1: Connect the VCC pin of the sensor to 3.3V
    - Pin 2: Connect the data pin of the sensor to GPIO 15
    - Pin 3: Leave the pin unconnected
    - Pin 4: Connect the GND pin of the sensor to GND
- Copy dht_example.uf2 to Raspberry Pico
- Open a serial connection and check output

## Activity 2: Using a library in your own code
**Description: Use a library to read data from a sensor**

Now that we know that the library is working as expected, we can use it in our own projects. Please start with the project-template or one of your old activities. We will write a simple program that shows the measured temperature on the serial connection (`prinf()`) and the humidity on an LED (using PWM scaled to humidity percentage).

Try to figure things out yourself, but if you are stuck, the lab teacher or teaching assistant can help you!

Here are a few hints: 

1. Make sure to check the example to understand how the library works, as there is no official documentation. That is often the case with hobbyist libraries, so you will need to read the code to understand how to use it. But even in professional projects, documentation is often missing or outdated, so it is a good skill to have.

2. In Programming 2 you already learned that CMake can help you with including libraries. You will need to tell the linker to include the library and the compiler where to find the header files. You can do this by adding the following lines to your `CMakeLists.txt`:
- `target_link_libraries(your_project_name pico_dht)`, this line is already included in our project template, so just add it to the list of libraries, like this: `target_link_libraries(${PROJECT} pico_stdlib hardware_pwm hardware_adc pico_rand dht)`
- `add_subdirectory(pico_dht/dht)` or `add_subdirectory(pico_dht)` to the `CMakeLists.txt` so that the compiler knows where to find the header files. Make sure that this line is after `pico_sdk_init()`, as the library uses the SDK as well.

```c
// TODO: include your code here
#include "pico/stdlib.h" // Standard library for Pico
#include <dht.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include <string.h>

static const dht_model_t DHT_MODEL = DHT22;
static const uint DATA_PIN = 15; 
static const uint LED_PIN = 16; //gpio pin for led

void setup_pwm(uint gpio_pin){
    gpio_set_function(gpio_pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(gpio_pin);
    pwm_set_enabled(slice_num, true);
    pwm_set_wrap(slice_num, 100);
}

static float celsius_to_fahrenheit(float temperature) {
    return temperature * (9.0f / 5) + 32;
}


int main() {
    stdio_init_all();
    puts("Temperature and humidity monitor");

    //initialize DHT sensor
    dht_t dht;
    dht_init(&dht, DHT_MODEL, pio0, DATA_PIN, true /* pull-up */);

    //initialize PWM for LED
    setup_pwm(LED_PIN);

    while(true){
        dht_start_measurement(&dht);

        float humidity;
        float temperature_c;
        dht_result_t result = dht_finish_measurement_blocking(&dht, &humidity, &temperature_c);

        if(result == DHT_RESULT_OK){
            //print temperature to serial console
            printf("Temperature: %.1f C (%.1f F)\n", temperature_c, celsius_to_fahrenheit(temperature_c));

            //scale LED brightness based on humidity percentage
            printf("Humidity: %.1f%%\n", humidity);
            pwm_set_gpio_level(LED_PIN, humidity); //adjust led brightness
        } else if ( result == DHT_RESULT_TIMEOUT){
            puts("DHT sensor not responding. Please check your wiring.");
        } else {
            assert(result == DHT_RESULT_BAD_CHECKSUM); //Verifies the result indicates a bad checksum and prints an error message.
            puts("Bad checksum");  
        }
        sleep_ms(2000);
    } 
    return 0;
}
```

## Activity 3: Communicating with another Pico through UART
**Description: Send data from one Pico to another**

Of course sometimes you want to communicate between two embedded systems. the easiest way to do this is to use the UART protocol, as it only requires two wires. One wire is used to transmit data (TX) and one is used to receive data (RX). You should also connect the GND of both systems together to have a common reference. In the activities in session 1 you already used the UART protocol to communicate with your computer, through USB. But now we will use the UART pins of the Pico to communicate with another Pico. Therefore team up with another student and connect the two Picos as follows:
- Connect the TX pin of Pico 1 to the RX pin of Pico 2 (e.g. TX on GPIO 0 to RX on GPIO 1)
- Connect the RX pin of Pico 1 to the TX pin of Pico 2 (e.g. RX on GPIO 1 to TX on GPIO 0)
- Connect the GND of both Picos together

*Note: This is a great moment to search a partner for your final project, as you will need to work in pairs, as well.*

Now let's write two simple program's:
1. Pico 1 will send a message every second (e.g. "Hello Pico 2!") to Pico 2
2. Pico 2 will receive the message and print it to standard output (preferably in one string, not character by character)

Here's a code snippet explaining the necessary function calls, you will need to change the code to repeatedly send a full string. Furthermore you will need to implement the receiving and relaying part on the second Pico.

```c
#include "pico/stdlib.h" // Standard library for Pico
#include "hardware/uart.h" // UART hardware library for Pico

int main() {

    // Set the GPIO pin to UART
    gpio_set_function(12, GPIO_FUNC_UART);
    gpio_set_function(13, GPIO_FUNC_UART);

    // Initialise UART 0 with a baud rate of 115200
    uart_init(uart0, 115200);

    // Send a character to the UART
    uart_putc(uart0, 'H');

    // Check if a character is available to read
    if (uart_is_readable(uart0)) {
        // Read a character from the UART
        char received = uart_getc(uart0);
    }
}
```

1. Implement the sending part on Pico 1:

```c
// TODO: include your code here
#include "pico/stdlib.h" // Standard library for Pico
#include <dht.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include <string.h>

//IMPLEMENT PICO 1 (SENDER)

int main(){
    //set GPIO pin to UART
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);

    //initialize UART 0 with a baud rate of 115200
    uart_init(uart0, 115200);

    const char *message = "Hello Pico 2!\n";
    while(true){
    
    //send a string to the UART
    uart_puts(uart0, message);  //uart_putc if it's a character
    printf("Sent: %s", message);
    sleep_ms(1000);
    }
    return 0;
}
```

2. Implement the receiving part on Pico 2:

```c
// TODO: include your code here
#include "pico/stdlib.h" // Standard library for Pico
#include <dht.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include <string.h>

// IMPLEMENT PICO 2 (RECEIVER)
int main(){
  stdio_init_all();
    // set GPIO pin to UART
    gpio_set_function(1, GPIO_FUNC_UART);
    gpio_set_function(0, GPIO_FUNC_UART);

    // initialize UART 0 with a baud rate of 115200
    uart_init(uart0, 115200);

    char buffer[200];
    size_t index = 0;
    while (true){
        if (uart_is_readable(uart0)){
            // read character from UART
            char received = uart_getc(uart0);

            // store character in the buffer
            buffer[index++] = received;

            if (received == '\n'){
                buffer[index] = '\0';
                printf("Received: %s", buffer);
                index = 0;
            }
        }
    }
    return 0;
}
```

*Note: If you want to try a different protocol, you can use I2C or SPI. These are more complex, but also more powerful. They both operate with a master-slave architecture. Here you can find a great tutorial using on SPI (chapters 1-4 are relevant for your level): [Circuitstate SPI](https://www.circuitstate.com/tutorials/making-two-raspberry-pi-pico-boards-communicate-through-spi-using-c-cpp-sdk/)*

## Activity 4 Traffic Light: (Optional for 6 points, mandatory for 10 points)
**Description: Implement pedestrian traffic light**

Now that you have learned how to communicate between two Picos, let's implement a traffic light system. One Pico will control the car light (3 LED) and the other will control the pedestrian light (2 LEDs). The pedestrian light will be controlled by a button. Take the traffic light in front of Saxion as a model:
1. The cars will have green light until a pedestrian button is pressed
2. Switch to yellow light for cars, after a short time to a red light
3. The pedestrian light will turn green for around 10 seconds
4. After that the pedestrian light will blink for 3 seconds and then turn red again
5. Now the car light will turn green again

*Note: The description is quite high-level, so you will need to figure out the details yourself. This should prepare you for the final project, where you will need to design the system yourself.*

```c
// TODO: include your code here
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

```

## Questions to answer:
Please answer this reflection questions:

1. How long did this tutorial take you?
- 3 days
2. Did you face difficulties?
- yes, for the last activity at first but now i understande
3. What would you like to see improved?

## Sign-off

Please show your code of activity 3 to your lab teacher or teaching assistant.
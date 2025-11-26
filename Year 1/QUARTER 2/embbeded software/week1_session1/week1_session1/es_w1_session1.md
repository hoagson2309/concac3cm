# Week 1 - Tutorial 1: Introduction and Setup

> Name: SON CAO
>
> Group: ETI1V.IA
>
> Date: 13/11/2024

## Introduction

Welcome to the Embedded Software course.

In this tutorial, we will set up the RaspberryPi Pico toolchain and write our first program. We will learn how to interact with the on-board LED and how to connect an external LED. We will practice the [*superloop*](https://en.wikibooks.org/wiki/Embedded_Systems/Super_Loop_Architecture) concept by implementing a few simple programs.

This is the list of the equipment needed for this tutorial:
- Laptop with Windows and WSL2 installed (or with MacOS, however this is not officially supported)
- Raspberry Pi Pico board (with USB cable, headers soldered)
- Breadboard
- Jumper wires
- 6 LEDs
- Resistors

Let's start by testing your Raspberry Pi Pico board. Plug in the USB cable to your computer and the board while holding down the button on the board. The board should appear as a USB drive on your computer. If it does not, please ask for help! Next drag and drop the file `test_pico_w.uf2` that you can find in the tutorial directory to the RPi USB drive. The board should restart and you should see the on-board LED blinking. If you see this, you are ready to start the tutorial.

## Setting up the toolchain

## Windows

Programs for Raspberry Pi Pico can be compiled using the WSL Ubuntu virtual machine on Windows. You already have it, it's only a matter of installing the right compiler, tools and the [*Software Developer Kit*](https://www.raspberrypi.com/documentation/pico-sdk/index_doxygen.html). You can do it manually or automatically.

To install the tools **manually**, enter the following commands in the WSL terminal:

```bash
sudo apt update && sudo apt upgrade --yes

sudo apt install build-essential make python3 python3-pip cmake git gdb-multiarch ninja-build gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib automake autoconf build-essential texinfo libtool libftdi-dev libusb-1.0-0-dev pkg-config

cd ~
mkdir -p pico
cd pico
git clone https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
cd ..
git clone https://github.com/raspberrypi/pico-examples.git
cd pico-examples
git submodule update --init


echo "export PICO_SDK_PATH=~/pico/pico-sdk" >> ~/.bashrc
source ~/.bashrc
```

To install the tools **automatically**, you can use the script [`install_all.sh`](https://raw.githubusercontent.com/SaxionACS/public/main/bash/install_all.sh). 

When run, the script will present a menu with options. You can leave the default option *all* to install everything and just press `OK`.

You can download and run it by entering the following commands in the WSL terminal:

```bash
cd ~
wget https://raw.githubusercontent.com/SaxionACS/public/main/bash/install_all.sh
sudo bash install_all.sh
``` 

## For MacOS users
*Note: MacOS is not officially supported in this course, but we'll try to help you!*

You can install the toolchain using [*Homebrew*](https://brew.sh). If you don't have it installed on your Mac, open the terminal window and run the following command:

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

This will guide you through the installation process of Homebrew. After you have installed Homebrew, you can install the toolchain by running the following commands in the terminal:

```bash
brew install cmake
brew install --cask gcc-arm-embedded
```

Then download the RaspberryPi Pico SDK to your home directory:

```bash
cd ~
mkdir Pico
cd ./Pico/
git clone -b master https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
```



```bash
echo "export PICO_SDK_PATH=~/pico/pico-sdk" >> ~/.bashrc
source ~/.bashrc
```

When you have done that install the recommended extensions in VSCode, including the CMake Tools extension. Open the `project-template` folder in VSCode and you should be able to build the project later.

## Activity 1: Hello World (sign-off)
*Description: Hello world with external LED*

Now that we have the toolchain installed, let's write our first program. As with desktop programming, the first program we usually write is the "Hello World" program. In embedded programming, the equivalent of "Hello World" is to blink an LED. Unfortunately, the wireless version of the RaspberryPi Pico has a quite complex setup of the onbord LED, so we will directly go to use one of the GPIO pins.

This requires some explanation. The term *GPIO* stands for General Purpose Input/Output. Those are pins (electric connectors of the microcontroller) that can be used to read inputs or write outputs (Or to send or receive electric signals if you prefer). The RaspberryPi Pico has 26 GPIO pins that can be configured for any purpose, that is either for reading or writing.

You can select any of the GPIO pins to connect the LED. For this tutorial, we will use pin 15. The code snippet below shows how to blink the on-board LED. To figure out the number of the pin you want to use take a look at the pinout document [here](https://datasheets.raspberrypi.com/picow/PicoW-A4-Pinout.pdf).

*Note: Do not forget to use a resistor to limit the current to the LED! You can assume that 330 Ohm is a good value for the LEDs in your kit. In Electronic Instrumentation you learn more about the correct value.*

```c
#include "pico/stdlib.h" // Standard library for Pico

int main() {
    // Set up the LED pin 15 / physical pin 20
    const uint LED_PIN = 15;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Never-ending superloop
    while (true) {
        gpio_put(LED_PIN, true);
        sleep_ms(1000);
        gpio_put(LED_PIN, false);
        sleep_ms(1000);
    }
}
```

Now it is time to compile and run the program. You can use the following commands to compile and run the program. Execute them in the terminal in the `project-template` directory:

```bash
mkdir build
cd build
cmake ..
make
```

After running these commands, you will have a file called `project-template.uf2` in the `build` directory. This file is the compiled program -- the binary executable that can be run by RPi Pico. Now plug in your board while holding down the `BOOTSEL` button to the computer. This will make the board appear as a USB drive. Drag and drop the `project-template.uf2` file onto the RPi USB drive. In contrast to desktop programming, you don't need to run the program, it will start automatically when you plug in the board!

*Can you see the on-board LED blinking? (slower than before)*

Although you probably can guess the meaning of those functions, let's go through them:

- `gpio_init(LED_PIN)`: This function initializes the pin that we want to use. In this case, we are initializing the on-board LED pin.

- `gpio_set_dir(LED_PIN, GPIO_OUT)`: This function sets the direction of the pin. In this case, we are setting the on-board LED pin as an output pin.

- `gpio_put(LED_PIN, 1)`: This function sets the value of the pin. In this case, we are setting the on-board LED pin to high (1).

- `sleep_ms(1000)`: This function makes the program sleep for a certain amount of time. In this case, we are making the program sleep for 1000 milliseconds (1 second).

As always in C, the `main()` function is the entry point of the program. This is where the program starts running. The `while (true)` loop is a so-called *superloop*. This is a loop that runs forever. This is the main loop of the program. The program will keep running unless the device is disconnected from power. It is also the only instance where `while(true)` is good practice.

> **TODO:** *Question: What do you think happens if you return from the `main()` function?*

You might wonder how the compiler knows what `GPIO_OUT` is. The `#include "pico/stdlib.h"` line includes the standard library for the Pico. This library contains the definitions of the constants and functions that we use in the program. In the library, the `GPIO_OUT` constant is defined as `1`. The `gpio_set_dir` function uses this constant to set the direction of the pin. If you have the C/C++ extension installed in VSCode, you can hover over the constant to see its definition.

**TODO:** With the knowledge you have from Programming 1, please improve the code:

1. Replace the magic number `1000` with a constant.
2. Move the setup of the LED pin to a separate function. with the prototype `void setup_led_pin(uint led_pin)`.

Note: To rebuild your project after making changes you just need to run `make` in the `build` directory.

```c
// TODO: include your code here
#include "pico/stdlib.h" // Standard library for Pico

void setup_led_pin(uint LED_PIN) {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

int main() {
    // Set up the LED pin 15 / physical pin 20
    const uint BLINK_TIME = 1000;
    const uint LED_PIN = 15;
    setup_led_pin(LED_PIN);

    // Never-ending superloop
    while (true) {
        gpio_put(LED_PIN, true);
        sleep_ms(BLINK_TIME);
        gpio_put(LED_PIN, false);
        sleep_ms(BLINK_TIME);
    }
}
```

>  **TODO:** When you are done, show the circuit to a teacher or TA to get a sign-off so we can make sure that everyone has a working setup for the coming weeks!

## Activity 2: Alternating LEDs
*Description: 2 LEDs blinking alternately*

To practice let's write a program that blinks two LEDs alternately. The LEDs should blink at a speed of 1 Hz (1 second on, 1 second off). You can use any two GPIO pins for the LEDs. 

This can be done as a simple modification of the previous main function. You do not need to add any new functions for this activity.

Note: Make a new project folder by copying the `project-template` folder and renaming it to your preferred name, for example, `activity2`. Also, change the project name in the `CMakeLists.txt` file, and rerun the Cmake commands as above in the new folder.

```c
// TODO: include your code here
#include "pico/stdlib.h" // Standard library for Pico

void setup_led_pin(uint LED_PIN) {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

int main() {
    // Set up the LED pin 15 / physical pin 20
    const uint BLINK_TIME = 1000;
    const uint LED_PIN1 = 15;
    setup_led_pin(LED_PIN1);
    const uint LED_PIN2 = 14;
    setup_led_pin(LED_PIN2);

    // Never-ending superloop
    while (true) {
        gpio_put(LED_PIN1, true);
        gpio_put(LED_PIN2, false);
        sleep_ms(BLINK_TIME);
        gpio_put(LED_PIN1, false);
        gpio_put(LED_PIN2, true);
        sleep_ms(BLINK_TIME);
    }
}
```

## Activity 3: Binary Counter
*Description: Show a binary counter with 4 LEDs*

Now write a program that lets 4 LEDs show a binary counter. The counter should increment every second and should reset to 0 after reaching 15.

Your program should only do as little as possible in the `main()` function. You should create a function that takes an integer as an argument and sets the LEDs according to the binary representation of the number. The prototype of the function should be `void display_binary_4_LEDs(uint number, const uint led_pins[4]);`. As you can see we pass an array of 4 integers to the function, these are the pin numbers of the LEDs, that is a good way to keep the your pin numbers organized and you can even iterate over them in the function! An example of the array could look like this: `const uint led_pins[4] = {12, 13, 14, 15};`.

Use the modulo operator `%` you learned in Programming 1 to show the binary representation of the number. Hint: This is similar to the number reverse assignment in Programming 1, but now with base 2 instead of base 10.

This snippet of the expected output shows the binary representation of the numbers 14, 15, 0, 1 (where 1 indicates a lit LED, and 0 indicates a dimmed LED):

```
...
1110
1111
0000
0001
...
```

```c
// TODO: include your code here
#include "pico/stdlib.h" // Standard library for Pico

// Constants for LED blink delay in milliseconds and GPIO pins
const uint TIME_DELAY_MS = 1000;
const uint LED_PIN_1 = 12; 
const uint LED_PIN_2 = 13; 
const uint LED_PIN_3 = 14; 
const uint LED_PIN_4 = 15; 
// The difference is due to the order for better visualization on the breadboard 

int main() {
    // Initialize both LED pins as output
    gpio_init(LED_PIN_1);
    gpio_set_dir(LED_PIN_1, GPIO_OUT);
    gpio_init(LED_PIN_2);
    gpio_set_dir(LED_PIN_2, GPIO_OUT);
    gpio_init(LED_PIN_3);
    gpio_set_dir(LED_PIN_3, GPIO_OUT);
    gpio_init(LED_PIN_4);
    gpio_set_dir(LED_PIN_4, GPIO_OUT);

    // Never-ending superloop
    while (true) {
        for(int i=0; i<16; i++){
            gpio_put(LED_PIN_1, false);
            gpio_put(LED_PIN_2, false);
            gpio_put(LED_PIN_3, false);
            gpio_put(LED_PIN_4, false);
            if(i & 1){
                gpio_put(LED_PIN_1, true);
            }
            if(i & 2){
                gpio_put(LED_PIN_2, true);
            }
            if(i & 4){
                gpio_put(LED_PIN_3, true);
            }
            if(i & 8){
                gpio_put(LED_PIN_4, true);
            }
            sleep_ms(TIME_DELAY_MS);
        }
    }
}6
```

> Extra challenge: Can you make the functions generic for bigger counters (so no hardcoded limit of 4 LEDs)?

## Activity 4: Scanner Light (optional)
*Description: Moving pattern of two LEDs*

Write a program that lets 6 LEDs show a moving pattern of two LEDs wide. The pattern should move from left to right and right to left: when it reaches the rightmost LED, it should move back to the left again. When the pattern reaches one of the two sides, only one LED should be lit before the pattern moves to the other side again. The pattern should restart and continue indefinitely.

The LEDs should light up according to the following pattern (where * indicates a lit LED, and . indicates a dimmed LED), and the pattern should move at a speed of 10 steps per second:

```
*.....
**....
.**...
..**..
...**.
....**
.....*
....**
...**.
..**..
.**...
**....
```

*Hint: Use an array to store the pin numbers of the LEDs.*

```c
// TODO: include your code here
#include "pico/stdlib.h" // Standard library for Pico

void setup_led_pin(uint LED_PIN) {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

int main() {
    const int delay = 100;
    const uint LED_PINS [6] = {0,1,2,3,4,5};
    for(int i = 0; i< 6; i++){
        setup_led_pin(LED_PINS[i]);
    }
    while(true){
        for(int i = 0; i < 6; i++){
            if(i != 0){
                gpio_put(LED_PINS[i], true);
                gpio_put(LED_PINS[i-1], true);
                if(i >= 1){
                    gpio_put(LED_PINS[i-2], false);
                }
                sleep_ms(delay);
            } else{
                gpio_put(LED_PINS[0], true);
                gpio_put(LED_PINS[1], false);
                sleep_ms(delay);
            }
        }
        for(int i = 5; i >= 0; i--){
            if(i != 5){
                gpio_put(LED_PINS[i], true);
                gpio_put(LED_PINS[i + 1], true);
                if(i <= 5){
                    gpio_put(LED_PINS[i + 2], false); 
                }
                sleep_ms(delay);
            } else{
                gpio_put(LED_PINS[5], true);
                gpio_put(LED_PINS[4], false);
                sleep_ms(delay);
            }
        }
    }
}
```

## Questions to answer:

> Finally, Please answer the following questions:
> 
> 1. Give three examples of embedded systems.
> Smartwatch, automatic light sensor, digital camera.
> 2. Choose one of the examples, how does the device interact with the outside world?
> A Smartwatch is a basic embedded system that displays time and date and may include features like alarms or timers. It uses a microcontroller to keep accurate time and manage simple user interactions through buttons.
> 3. For the same example, what constraints does the device have?
> Battery Life, Limited Processing Power and Memory, User Interface Constraints, Connectivity Limitations.
> Other questions:
> 
> 1. How long did this tutorial take you?
> 8 hours
> 2. Did you face difficulties?
> I actually face some difficulties at first because of the logic but then I already figured it out (this session only).
> 3. What would you like to see improved?
> 

## Sign-off

After you completed all activities and answered the questions, convert this markdown file to a html file and upload it to Brightspace. Make sure you signed off the circuit in Activity 1 with a teacher or TA.
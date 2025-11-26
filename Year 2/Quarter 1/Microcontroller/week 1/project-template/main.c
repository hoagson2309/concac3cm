// // #include "pico/stdlib.h" // Standard library for Pico
// // #include "stdio.h"

// // //test
// // int main() {
// //     stdio_init_all();

// //     uint32_t mask = 0x03fc;   // LEDs on GPIO 2–9
// //     uint32_t leds = 0x0004;   // start with LED 2 on
// //     int direction = 1;        // 1 = left (towards higher pin numbers), 0 = right

// //     // initialize pins as output
// //     for (int i = 2; i <= 9; i++) {
// //         gpio_init(i);
// //         gpio_set_dir(i, true);
// //     }

// //     while (1) {
// //         //update LEDs
// //         gpio_put_masked(mask, leds);

// //         sleep_ms(1000); // delay to see the effect

// //         // shift pattern
// //         if (direction == 1) {
// //             leds <<= 1; // move left
// //         } else {
// //             leds >>= 1; //move right
// //         }
// //         //boundary checking and reverse direction
// //         if (leds == (1 << 9)) {     // reached LED 9
// //             direction = 0;
// //         } else if (leds == (1 << 2)) { // reached LED 2
// //             direction = 1;
// //         }
// //     }
// // }


// // // example programme interrupt & gpio mask - saxion (c) 2025

// // #include "pico/stdlib.h"
// // #include "stdio.h"

// // #define LED 10
// // #define BUTTON 2

// // volatile bool led_on = false;

// // // one general gpio callback function
// // void gpio_callback(uint gpio, uint32_t events) {
// // 	if (gpio == BUTTON && (events & GPIO_IRQ_EDGE_FALL)) {
// // 		gpio_xor_mask( (1<<LED) );
// // 	} 
// // 	// else if (GPIO == OTHERBUTTON) && (events & GPIO_IRQ_EDGE_FALL)) {
// // 	// do_something_else();
// // 	// } 
// // }

// // int main() {
// //     stdio_init_all(); // needed for picotool to auto load

// // 	// init IO
// // 	gpio_init_mask( (1 << LED) | (1 << BUTTON) );
// //  	gpio_set_dir_all_bits( (1 << LED) | (0 << BUTTON) );
// // 	gpio_pull_up( BUTTON );
// // 	gpio_xor_mask( (1<<LED) );
		
// // 	// register interrupt callback
// // 	gpio_set_irq_enabled_with_callback(
// // 		BUTTON,
// // 		GPIO_IRQ_EDGE_FALL,
// // 		true,
// // 		&gpio_callback
// // 	);
	
// // 	while (true) {
// // 		tight_loop_contents(); // Idle loop
// // 	}
// // }

#include "pico/stdlib.h"
#include "stdio.h"

#define LED_START 2
#define LED_END 9
#define BUTTON_START 10
#define BUTTON_STOP 11

volatile bool scanning = false; //flag
uint32_t mask = 0;

void gpio_callback(uint gpio, uint32_t events){
	if(gpio == BUTTON_START ){
		scanning = true;//start scanning
	} else if(gpio == BUTTON_STOP){
		scanning = false; //stop scanning
	}
}

int main(){
	
	stdio_init_all();

	for(int i = LED_START; i <= LED_END; i++){
		gpio_init(i);
		gpio_set_dir(i, true);
		mask |= (1u << i);   //The |= operator adds the bit to the mask without removing previous bits.
	}						//1u << i shift binary 1, i position to the left
	gpio_init(BUTTON_START);
	gpio_set_dir(BUTTON_START, false);
	gpio_pull_up(BUTTON_START);

	gpio_init(BUTTON_STOP);
	gpio_set_dir(BUTTON_STOP, false);
	gpio_pull_up(BUTTON_STOP);

	//set interrupt callback
	//The interrupt allows the program to respond immediately to button events, without constantly checking them in the main loop
	gpio_set_irq_enabled_with_callback(BUTTON_START, GPIO_IRQ_EDGE_RISE, true, &gpio_callback); //release -> trigger interrupt (cuz pull up)
	gpio_set_irq_enabled_with_callback(BUTTON_STOP, GPIO_IRQ_EDGE_FALL, true, &gpio_callback); //press -> trigger interrupt (cuz pull-up)
//start with 2 leds in the middle 	`
	uint32_t leds = (1u << (LED_START + 3)) | (1u << (LED_START + 4)); //( | combine 2 bits into 1 variable)
	int direction = 1; //1 = left, 0 = right

	while(true) {
		if(scanning){
			gpio_put_masked(mask, leds);
			sleep_ms(50);

			if(direction == 1){ 
				leds <<= 1;
				if((leds & mask) == ((1u << LED_END))) direction = 0;
			}
			if(direction == 0){
				leds >>= 1;
				if((leds & mask) == ((1u << LED_START))) direction = 1;
			}
		} else {
			tight_loop_contents(); //idle
		}
	}
}



//volatile tells the compiler that :
	//This variable can change at any time, outside the normal flow of the program, like through interrupts, hardware, or DMA

//without volatile: The compiler might “cache” the value of scanning in a register, so it never sees changes made by the interrupt. 
//With volatile, the compiler always reads the real memory value, so interrupt updates are seen immediately.

//1u: 
	//Bitwise operations (like <<) on signed integers can cause undefined behavior if the result overflows the signed range. 
	//Using 1u ensures the shift is safe and predictable because unsigned integers wrap around cleanly
//1u << i:
	//Example: If i = 3:
	//1 in binary: 0000 0001
	//1 << 3    : 0000 1000
	//This sets only bit 3 to 1 while keeping all other bits 0

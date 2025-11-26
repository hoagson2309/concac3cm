#include "pico/stdlib.h" // Standard library for Pico
#include "stdio.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/adc.h"

#define UART_ID uart0
#define BAUD_RATE 9600 //communication speed
#define UART_TX_PIN 0
#define UART_RX_PIN 1

const uint LED_PINS[4] = {2, 3, 4, 5};

void set_leds(uint8_t value){
    for(int i = 0; i < 4; i++){                     // (value >> i) & 1: Shift the bits of value right by i positions and check whether the lowest bit is 1       
        gpio_put(LED_PINS[i], (value >> i) & 1);   //shift 1 bit to the right and only keep the least significant bit so 1 0 1 0 (on off on off)
                                                      //The bits that fall off the right side are discarded, and zeros are added on the left.
    }
}

//UART RX interrupt handler
void on_uart_rx(){
    while(uart_is_readable(UART_ID)){    //checks if there is any data waiting in the UART receive buffer
        uint8_t ch = uart_getc(UART_ID);
        set_leds(ch & 0x0F);  //Takes the lower 4 bits of the received byte. 0x0F = 00001111 (binary mask). ch & 0x0F strips away everything except the bottom 4 bits.
    }              
}
 //ch = 0xAF  = 1010 1111 (in binary)
 //0x0F       = 0000 1111 (bit mask)
 // => ch & 0x0F  = 0000 1111 = 0x0F  => removes the upper 4 bits, keeping only the last 4 bits => so keep only 1111
 //Each bit is compared one by one — only bits where both are 1 remain 1.

int main(){
    stdio_init_all();

    for(int i = 0; i < 4; i++){
        gpio_init(LED_PINS[i]);
        gpio_set_dir(LED_PINS[i], true);
    }

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART); //Configures GPIO0 as the TX (transmit) pin for UART0.
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART); //Configures GPIO1 as the RX (receive) pin for UART0.

    uart_set_hw_flow(UART_ID, false, false); //Controls hardware flow control (CTS/RTS) for UART. 
                                            // CTS (Clear to Send) => input signal from another device telling your Pico it’s allowed to send data. (disable)
                                            //RTS (Request to Send) => output signal from Pico telling the other device it’s ready to receive. (disable)
    
    uart_set_fifo_enabled(UART_ID, false); //Disables FIFO. Each byte triggers the RX interrupt immediately for real-time processing.

    //An IRQ stands for Interrupt Request
    //Without interrupts, your program would have to constantly check (poll) for events like incoming UART data — wasting CPU time
    //With an IRQ, the CPU can do other work, and when data arrives, the UART automatically triggers an interrupt, which runs your function (on_uart_rx()) right away
    irq_set_exclusive_handler(UART0_IRQ, on_uart_rx);   //=> defines the function to run
    irq_set_enabled(UART0_IRQ, true);                   //=> allows hardware to generate interrupts
    uart_set_irq_enables(UART_ID, true, false);         //=> only RX triggers the interrupt.

    //init ADC
    adc_init();
    adc_gpio_init(26);  //GPIO26 -> ADC0
    adc_select_input(0);

    while(1){
        uint16_t result = adc_read();   //Reads the analog voltage from the ADC pin, adc_read() returns a 12-bit value (0–4095):0 -> 0V, 4095 -> 3v3
        uint8_t msb = result >> 8;  //Shifts the 12-bit ADC value 8 bits to the right, keeping only the upper 4 bits.
        //result = 0b1010 1100 1111 (12 bits)
        //result >> 8 → 0b0000 1010 (8 bits)       lower is always zeros so keep upper 4 bits cuz there are 4 leds
        uart_putc(UART_ID, msb);    //send over UART
        sleep_ms(500);  
    }
}


//The interrupt in your code detects when new UART data arrives. When that happens, it automatically runs on_uart_rx() to update the LEDs without waiting for the main loop.
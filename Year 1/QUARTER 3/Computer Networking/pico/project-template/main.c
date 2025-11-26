// TCP test programme
// examples+code from the book: 
// master the raspberry pi pico in C:Wifi with IwIP & mbedtls
// (c) IOpress
//


/*********** add/change to cmakelist ********************

target_include_directories(${PROJECT} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts
        )

target_link_libraries(${PROJECT} 
	pico_stdlib
	pico_cyw43_arch_lwip_threadsafe_background
)

********************************************************/

#include <stdio.h>
#include "pico/stdlib.h" 
#include "pico/cyw43_arch.h"
#include "setupWifi.h" // code for connecting to WiFi 
#include "lwip/altcp.h"

#define BUF_SIZE 2048
char myBuff[BUF_SIZE];

// http://128.119.245.12/wireshark-labs/INTRO-wireshark-file1.html

char header[] = "GET /wireshark-labs/INTRO-wireshark-file1.html HTTP/1.1\r\nHOST:gaia.cs.umass.edu\r\n\r\n";

err_t recv(void *arg, struct altcp_pcb *pcb, struct pbuf *p, err_t err)
{
    if (p != NULL)
    {
        printf("\nrecv total %d  this buffer %d next %d err %d\n\n", p->tot_len, p->len, p->next, err);
        pbuf_copy_partial(p, myBuff, p->tot_len, 0);
        myBuff[p->tot_len] = 0;
        printf("Buffer= %s\n", myBuff);
        altcp_recved(pcb, p->tot_len);
        pbuf_free(p);
    }
    return ERR_OK;
}

static err_t altcp_client_connected(void *arg, struct altcp_pcb *pcb, err_t err)
{
    err = altcp_write(pcb, header, strlen(header), 0);
    err = altcp_output(pcb);
    return ERR_OK;
}

int main() {
	ip_addr_t ip;
	
    stdio_init_all(); // needed for picotool for easy upload

	// country, ssid, pass, auth, hostname, ipaddr, ipmask, gateway
	setup(country, ssid, pass, auth, "PicoW2", NULL, NULL, NULL);
	
    struct altcp_pcb *pcb = altcp_new(NULL);
    altcp_recv(pcb, recv);

    IP4_ADDR(&ip, 128, 119, 245, 12); // server address gaia.cs.umass.edu (kurose ross)

    cyw43_arch_lwip_begin();
    err_t err = altcp_connect(pcb, &ip, 80, altcp_client_connected);
    cyw43_arch_lwip_end();
	
    // Never-ending superloop
    while (true) {
        sleep_ms(500);
    }
}
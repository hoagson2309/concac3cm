// setupWifi
// examples+code from the book: 
// master the raspberry pi pico in C:Wifi with IwIP & mbedtls
// (c) IOpress
//

#include "credentials.h" // ssid + passphrase

/* connection status while trying to connect
#define CYW43_LINK_DOWN         (0)     ///< link is down
#define CYW43_LINK_JOIN         (1)     ///< Connected to wifi
#define CYW43_LINK_NOIP         (2)     ///< Connected to wifi, but no IP address
#define CYW43_LINK_UP           (3)     ///< Connected to wifi with an IP address
#define CYW43_LINK_FAIL         (-1)    ///< Connection failed
#define CYW43_LINK_NONET        (-2)    ///< No matching SSID found (could be out of range, or down)
#define CYW43_LINK_BADAUTH      (-3)    ///< Authenticatation failure
*/

int setup(uint32_t country, const char *ssid, const char *pass,
          uint32_t auth, const char *hostname, ip_addr_t *ip,
          ip_addr_t *mask, ip_addr_t *gw)
{

    if (cyw43_arch_init_with_country(country))
    {
        return 1;
    }

    cyw43_arch_enable_sta_mode();
    if (hostname != NULL)
    {
        netif_set_hostname(netif_default, hostname);
    }
    if (cyw43_arch_wifi_connect_async(ssid, pass, auth))
    {
        return 2;
    }
    int flashrate = 1000;
    int status = CYW43_LINK_UP + 1;
    while (status >= 0 && status != CYW43_LINK_UP)
    {
        int new_status = cyw43_tcpip_link_status(&cyw43_state,
                                                 CYW43_ITF_STA);
        if (new_status != status)
        {
            status = new_status;
            flashrate = flashrate / (status + 1);
            printf("Wifi status: %d %d\n", status, flashrate);
        }
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(flashrate);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(flashrate);
    }
    if (status < 0)
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    }
    else
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
		
       	int32_t rssi;	 
		cyw43_wifi_get_rssi(&cyw43_state, &rssi);
		printf("RSSI: %d\n",rssi);
		
		if (ip != NULL)
        {
            netif_set_ipaddr(netif_default, ip);
        }
        if (mask != NULL)
        {
            netif_set_netmask(netif_default, mask);
        }
        if (gw != NULL)
        {
            netif_set_gw(netif_default, gw);
        }

        printf("IP: %s\n",
               ip4addr_ntoa(netif_ip_addr4(netif_default)));
        printf("Mask: %s\n",
               ip4addr_ntoa(netif_ip_netmask4(netif_default)));
        printf("Gateway: %s\n",
               ip4addr_ntoa(netif_ip_gw4(netif_default)));
        printf("Host Name: %s\n",
               netif_get_hostname(netif_default));
    }
    return status;
}

int connect()
{
	// uses "credentials.h"
    return  setup(country, ssid, pass, auth, "MyPicoW", NULL, NULL, NULL);
}

#include "bsp_eth.h"

#include "Ifx_Lwip.h"
#include "ip_addr.h"

void eth_init(void)
{
    IfxGeth_enableModule(&MODULE_GETH);                     /* Enable Gigabit Ethernet Media Access Controller (GETH) module*/

    /* Define a MAC Address */
    eth_addr_t ethAddr;
    ethAddr.addr[0] = 0xDE;
    ethAddr.addr[1] = 0xAD;
    ethAddr.addr[2] = 0xBE;
    ethAddr.addr[3] = 0xEF;
    ethAddr.addr[4] = 0xFE;
    ethAddr.addr[5] = 0xED;

    ip_addr_t default_ipaddr, default_netmask, default_gw;
    IP4_ADDR(&default_ipaddr, 192,168,6,57);
    IP4_ADDR(&default_netmask, 255,255,255,0);
    IP4_ADDR(&default_gw, 192,168,6,1);

    Ifx_Lwip_Reinit(ethAddr, &default_ipaddr, &default_netmask, &default_gw);   /* Initialize LwIP with the MAC address*/
}

void eth_process(void)
{
    Ifx_Lwip_pollTimerFlags();                          /* Poll LwIP timers and trigger protocols execution if required */
    Ifx_Lwip_pollReceiveFlags();                        /* Receive data package through ETH                             */
}

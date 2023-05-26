/*
 * eth_app.c
 *
 *  Created on: May 11, 2023
 *      Author: mkdigitals
 */


#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>

#include <lwip/api.h>
#include <lwip/opt.h>
#include <lwip/arch.h>
#include <lwip/api.h>
#include <lwip/inet.h>
#include <lwip/sockets.h>
#include <lwip/tcpip.h>

#include "app/include/eth_app.h"
#include "port/v_adapter.h"
/* Static IP ADDRESS */
#define IP_ADDR0   192
#define IP_ADDR1   168
#define IP_ADDR2   1
#define IP_ADDR3   10

/* NETMASK */
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   255
#define NETMASK_ADDR3   0

/* Gateway Address */
#define GW_ADDR0   192
#define GW_ADDR1   168
#define GW_ADDR2   1
#define GW_ADDR3   1

static struct netif g_netif;
static struct ip4_addr ipaddr;
static struct ip4_addr netmask;
static struct ip4_addr gw;

#define 	TASK_NAME		"eth5 task"
static void eth5_task(void *p);
static void lwip_dhcp_task(void *p);

int eth_create_task(void)
{
    TaskHandle_t task = NULL;

    /* Static address used */
    IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
    IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2, NETMASK_ADDR3);
    IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
    netif_set_addr(&g_netif, &ipaddr, &netmask, &gw);
    //log_printf("ETH5 static IP address:  %d.%d.%d.%d\n", IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);

    /* Add your network interface to the netif_list. */
    netif_add(&g_netif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, /*&ethernet_input */ &tcpip_input);
    netif_set_up(&g_netif);
    xTaskCreate(eth5_task, TASK_NAME, configMINIMAL_STACK_SIZE, NULL, ETH_TASK_PRIORITY, &task);
    if (task == NULL) {
	//log_printf("ERROR: Create %s\r\n", TASK_NAME);
	vTaskDelete(task);
	configASSERT(task);
    }
    //log_printf("SUCCESS: Create %s\r\n", TASK_NAME);
    return 0;
}

void udp_echo_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct
					ip_addr *addr, u16_t port)
{
    if (p != NULL) {
        /* send received packet back to sender */
        udp_sendto(pcb, p, addr, port);
        /* free the pbuf */
        pbuf_free(p);
    }
}

void eth5_task(void *p)
{
#define ECHO_PORT   7
    static char buf[1024];
    int sockfd, n;
    struct sockaddr_in local;
    u32_t addr_len = sizeof(struct sockaddr);

    local.sin_port = htons(ECHO_PORT);
    local.sin_family = PF_INET;
    local.sin_addr.s_addr = ipaddr.addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
	CLI_printf("create socket failed\r\n");
	return;
    }
    CLI_printf("create socket OK\r\n");

    /* bind to port at any interface */
    if (bind(sockfd, (struct sockaddr *) &local, addr_len) < 0) {
    	CLI_printf("error bind\r\n");
    }
    CLI_printf("bind OK\r\n");

    /* received data to buffer */
    while (1) {
	n = recvfrom(sockfd, buf, 1024, 0, (struct sockaddr *) &local, (u32_t *) & addr_len);
	if (n > 0) {
	    buf[n] = 0;

	    CLI_printf("%d bytes recv from (%s) : %s\r\n", n, inet_ntoa(local.sin_addr), buf);
	    if (sendto(sockfd, buf, n, 0, (struct sockaddr *) &local, addr_len) < 0) {
	    	CLI_printf("Error sendto\r\n");
	    }
	}
	vTaskDelay(5);
    }
}

//portTASK_FUNCTION( EchoServer, pvParameters ){
//		struct udp_pcb *pcb;
//		unsigned port = 7;
//		int err;
//		/* create new UDP PCB structure */
//		pcb = udp_new();
//		if (!pcb) {
//			CLI_printf("Error creating PCB. Out of Memory\n\r");
//		}
//
//		/* bind to specified @port */
//		err = udp_bind(pcb, IP_ADDR_ANY, port);
//		if (err != 0) {
//			CLI_printf("Unable to bind to port %d: err = %d\n\r", port, err);
//		}
//
//		/* Receive data */
//		udp_recv(pcb, udp_echo_recv, NULL);
//
//        for( ;; ){
//        	ethernetif_input(&s_EMAC_if);
//        }
//}



//void EchoRequest( struct netconn *pxNetCon ) {
//        struct netbuf *pxRxBuffer;
//        u8_t *pcRxString;
//        u16_t usLength;
//        netconn_recv( pxNetCon, &pxRxBuffer);
//        if ( pxRxBuffer != NULL ){
//                netbuf_data( pxRxBuffer, ( void * ) &pcRxString, &usLength );
//                if (  pcRxString != NULL){
//                        netconn_write( pxNetCon, pcRxString, (uint16_t) usLength, NETCONN_COPY );
//                        netconn_write( pxNetCon, "Hello Internet!\n", (uint16_t) 16, NETCONN_COPY);
//                        printf("REC: %s",pcRxString);
//                }
//                netbuf_delete( pxRxBuffer );
//        }
//}

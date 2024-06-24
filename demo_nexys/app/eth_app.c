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


#include "lwip/dhcp.h"



#include <lwip/api.h>
#include <lwip/opt.h>
#include <lwip/mem.h>
#include <lwip/memp.h>
#include <lwip/netif.h>
#include <netif/etharp.h>
#include <lwip/timeouts.h>
#include <lwip/arch.h>
#include <lwip/api.h>
#include <lwip/inet.h>
#include <lwip/tcpip.h>

#include "app/include/eth_app.h"
#include "port/v_adapter.h"
#include "port/ethernetif.h"
#include "ping.h"
/* Static IP ADDRESS */
#define IP_ADDR0   192
#define IP_ADDR1   168
#define IP_ADDR2   1
#define IP_ADDR3   86

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

/* MAC Address */
#define HW_ADDR0   0x80
#define HW_ADDR1   0xFA
#define HW_ADDR2   0x5B
#define HW_ADDR3   0x15
#define HW_ADDR4   0x46
#define HW_ADDR5   0x3D

static struct netif g_netif;
static struct ethernetif g_ethernetif;
static struct ip4_addr ipaddr;
static struct ip4_addr netmask;
static struct ip4_addr gw;
static struct ip4_addr target_ipaddr;


#define 	TASK_NAME		"eth5 task"
static void eth5_task(void *p);
static void lwip_dhcp_task(void *p);
void start_ping_action();
void check_ping_result();

uint32_t ETH_time_now(void)
{
  return xTaskGetTickCount();
}

intptr_t ETH_timeout_start(void)
{
  return (intptr_t)ETH_time_now();
}

int ETH_timeout_expired( intptr_t token, int timeout )
{
  int32_t delta;
  if( timeout == 0 ){
    return 1;
  }
  if( timeout < 0 ){
    /* forever */
    return 0;
  }
  uint32_t now;

  now = ETH_time_now();

  delta = ((int32_t)(now))- (int32_t)(token);
  if( delta > timeout ){
    return 1;
  } else {
    return 0;
  }
}



int eth_create_task(void)
{
    TaskHandle_t task = NULL;

    /* Static address used */

    xTaskCreate(eth5_task, TASK_NAME, 8*configMINIMAL_STACK_SIZE, NULL, ETH_TASK_PRIORITY, &task);

    if (task == NULL) {
	//log_printf("ERROR: Create %s\r\n", TASK_NAME);
	vTaskDelete(task);
	configASSERT(task);
    }
    //log_printf("SUCCESS: Create %s\r\n", TASK_NAME);
    return 0;
}



void eth5_task(void *pParameter )
{
    (void)(pParameter);
    IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
	IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1, NETMASK_ADDR2, NETMASK_ADDR3);
	IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);

	netif_set_addr(&g_netif, &ipaddr, &netmask, &gw);
	//log_printf("ETH5 static IP address:  %d.%d.%d.%d\n", IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);

	/* Add your network interface to the netif_list. */
	  netif_add(&g_netif, &ipaddr, &netmask, &gw, &g_ethernetif, &ethernetif_init, &ethernet_input);
	  g_netif.hwaddr_len = 6;
	  g_netif.hwaddr[0] = HW_ADDR0;
	  g_netif.hwaddr[1] = HW_ADDR1;
	  g_netif.hwaddr[2] = HW_ADDR2;
	  g_netif.hwaddr[3] = HW_ADDR3;
	  g_netif.hwaddr[4] = HW_ADDR4;
	  g_netif.hwaddr[5] = HW_ADDR5;

	  /* Registers the default network interface */
	  netif_set_default(&g_netif);

	  if (netif_is_link_up(&g_netif))
	  {
	    /* When the netif is fully configured this function must be called */
	    netif_set_up(&g_netif);
	  }
//	lwip_init();
	sys_timeout(4000, start_ping_action, NULL);
	sys_timeout(100, check_ping_result, NULL);
//	ping_init(target_ipaddr);
	for(;;){
		ethernetif_input(&g_netif);
		sys_check_timeouts();
		vTaskDelay(5);
	}
}

void start_ping_action() {
	//get gateway IP from global net interface
	ip_addr_t gw_addr = g_netif.gw;
	uint8_t gw_ip_part_1 = ip4_addr1(&gw_addr);
	//check if DHCP already succeeded by checking against non 0 ip part
	int ret = 0;
	if(gw_ip_part_1 != 0) {
		ip_addr_t target_ping_ip;
		//select target:
		//gateway
		//target_ping_ip = gw_addr;
		//static IPs
		//IP_ADDR4(&target_ping_ip, 192,168,1,180);
		IP_ADDR4(&target_ping_ip, 192,168,1,12); //google.com

		CLI_printf("Starting to ping IP: %d.%d.%d.%d.\n", (int)ip4_addr1(&target_ping_ip),
				(int)ip4_addr2(&target_ping_ip), (int)ip4_addr3(&target_ping_ip),
				(int)ip4_addr4(&target_ping_ip));
		if((ret = ping_ip(target_ping_ip)) != PING_ERR_OK) {
			CLI_printf("Error while sending ping: %d\n", ret);
		}
	}
	//every 4 seconds, start a new ping attempt
	sys_timeout(4000, start_ping_action, NULL);
}

void check_ping_result() {
	ping_result_t res;
	memset(&res, 0, sizeof(res));
	int retcode = 0;
	if((retcode = ping_ip_result(&res)) == PING_ERR_OK) {
        if (res.result_code == PING_RES_ECHO_REPLY) {
        	CLI_printf("Good ping from %s %u ms\n", ipaddr_ntoa(&res.response_ip),
                    (unsigned) res.response_time_ms);
        } else {
        	CLI_printf("Bad ping err %d\n", res.result_code);
        }
	} else {
		//printf("No ping result available yet: %d\n", retcode);
	}
	sys_timeout(100, check_ping_result, NULL);
}

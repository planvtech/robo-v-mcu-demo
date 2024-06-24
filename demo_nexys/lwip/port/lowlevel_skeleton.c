/**
 * @file
 * low level Ethernet Interface Skeleton
 *
 */

/* portions 
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * See ethernetif.c for copyright details
 */
#include <stdint.h>
#include "port/ethernetif.h"
#include "drivers/include/udma_ethernet_driver.h"
#include "drivers/include/udma_smi_driver.h"
#include "phy/phy_ctrl.h"
#include "phy/driver_lan8720.h"
#include "lwip/etharp.h"
#define LINK_STATUS_WAIT_CYCLES		1000
/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
void
low_level_init(void *i, uint8_t *addr, void *mcast)
{
	  /* device capabilities */
	  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */

	CLI_printf("low_level_init is called\n\r");
	if(1 == lan8720_basic_init(1))
	{
		CLI_printf("failed phy initialization\n\r");
	}
//
	lan8720_speed_indication_t speed;
	if(1 == lan8720_basic_auto_negotiation(&speed))
	{
		CLI_printf("failed phy auto_negotiation");
		return;
	}
	switch(speed){
		case LAN8720_SPEED_INDICATION_10BASE_T_HALF_DUPLEX:
			CLI_printf("Speed: LAN8720_SPEED_INDICATION_10BASE_T_HALF_DUPLEX\n\r");
			break;
		case LAN8720_SPEED_INDICATION_10BASE_T_FULL_DUPLEX:
			CLI_printf("Speed: LAN8720_SPEED_INDICATION_10BASE_T_FULL_DUPLEX\n\r");
			break;
		case LAN8720_SPEED_INDICATION_100BASE_TX_HALF_DUPLEX:
			CLI_printf("Speed: LAN8720_SPEED_INDICATION_100BASE_TX_HALF_DUPLEX\n\r");
			break;
		case LAN8720_SPEED_INDICATION_100BASE_TX_FULL_DUPLEX:
			CLI_printf("Speed: LAN8720_SPEED_INDICATION_100BASE_TX_FULL_DUPLEX\n\r");
			break;
	}


	for (uint16_t k = 0; k < LINK_STATUS_WAIT_CYCLES; k++)
	{
		lan8720_link_t status;
		if(1 == lan8720_basic_link_status(&status))
		{
			CLI_printf("failed phy link status acquirement");
			return;
		}
		if(status == LAN8720_LINK_UP)
		{
			CLI_printf("LINK_UP\n\r");
			if(udma_eth_start(0) != 0)
				CLI_printf("ETH_OPEN_FAILURE\n\r");
			return;
		}
	}
	CLI_printf("LINK_DOWN\n\r");
}

/**
 * This function starts the transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param ethernetif the lwip network interface structure for this netif
 * @return 1 if the packet could be sent
 *         0 if the packet couldn't be sent	(no space on chip)
 */

int
low_level_startoutput(void *i)
{
	return 1;
}

/**
 * This function should do the actual transmission of the packet.
 The packet is contained in chained pbufs, so this function will be called
 for each chunk
 *
 * @param ethernetif the lwip network interface structure for this netif
 * @param data where the data is
 * @param len the block size
 */

void
low_level_output(void *i, void *data, uint16_t len)
{
	CLI_printf("llout ");
	CLI_printf("len = ");
	CLI_printf("%d\n\r", len);
	udma_eth_write(len, data);

}
/**
 * This function begins the actual transmission of the packet, ending the process
 *
 * @param ethernetif the lwip network interface structure for this netif
 */

void
low_level_endoutput(void *i, uint16_t total_len)
{
	//CLI_printf("low_level_endoutput is called\n\r");
}
/**
 * This function checks for a packet on the chip, and returns its length
 * @param ethernetif the lwip network interface structure for this netif
 * @return 0 if no packet, packet length otherwise
 */
int
low_level_startinput(void *i)
{
	return udma_eth_get_read_len();
}

/**
 * This function takes the data from the chip and copies it to a chained pbuf
 * @param ethernetif the lwip network interface structure for this netif
 * @param data where the data is
 * @param len the block size
 */
void
low_level_input(void *i, void *data, uint16_t len)
{
	udma_eth_read(len, data);
}

/**
 * This function ends the receive process
 * @param ethernetif the lwip network interface structure for this netif
 */
void
low_level_endinput(void *i)
{
}

/**
 * This function is called in case there is not enough memory to hold a frame
 * after its length has been got from the chip. The driver decides whether to 
 * drop it or let it waiting in the chip's memory, based on the developer's
 * knowledge of the hardware (the chip can have more or less memory than the system)
 * @param ethernetif the lwip network interface structure for this netif
 * @param len the frame length
 */
void
low_level_inputnomem(void *i, uint16_t len)
{
	CLI_printf("low_level_inputnomem is called\n\r");
}


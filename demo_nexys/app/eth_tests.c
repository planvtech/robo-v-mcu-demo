/*
 * sdio_tests.c
 *
 *  Created on: 20-Oct-2021
 *      Author: somesh
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "semphr.h"	// Required for configASSERT

#include "target/core-v-mcu/include/core-v-mcu-config.h"
#include "libs/cli/include/cli.h"
#include "libs/utils/include/dbg_uart.h"
#include "hal/include/hal_apb_soc_ctrl_regs.h"

#include "drivers/include/udma_ethernet_driver.h"
#include "drivers/include/udma_smi_driver.h"
#include "phy/phy_ctrl.h"
#include "../lwip/include/phy/driver_lan8720.h"

static void eth_init_test(const struct cli_cmd_entry *pEntry);
static void phy_dump_test(const struct cli_cmd_entry *pEntry);
static void eth_send_test(const struct cli_cmd_entry *pEntry);
static void eth_recv_test(const struct cli_cmd_entry *pEntry);
static void eth_reset_test(const struct cli_cmd_entry *pEntry);
static void eth_set_test(const struct cli_cmd_entry *pEntry);
static void link_status_test(const struct cli_cmd_entry *pEntry);
static void autonegotiation_test(const struct cli_cmd_entry *pEntry);
static void enable_loopback_mode(const struct cli_cmd_entry *pEntry);
static void disable_loopback_mode(const struct cli_cmd_entry *pEntry);


uint8_t eth_send_buf_0[16] = {0};
uint8_t eth_send_buf_1[17] = {0};
uint8_t eth_send_buf_2[18] = {0};
uint8_t eth_send_buf_3[19] = {0};
int test_num = 0;
uint8_t eth_recv_buf[4096] = {0};
// EFPGA menu
const struct cli_cmd_entry eth_cli_tests[] =
{
  CLI_CMD_SIMPLE( "init", eth_init_test, "eth init" ),
  CLI_CMD_SIMPLE( "phy_dump", phy_dump_test, "phy_dump" ),
  CLI_CMD_WITH_ARG( "send", eth_send_test, 0, "eth send" ),
  CLI_CMD_WITH_ARG( "receive", eth_recv_test, 0, "eth receive" ),
  CLI_CMD_WITH_ARG( "eth_set", eth_set_test, 0, "eth set" ),
  CLI_CMD_WITH_ARG( "eth_reset", eth_reset_test, 0, "eth reset" ),
  CLI_CMD_WITH_ARG( "phy_status", link_status_test, 0, "phy_status" ),
  CLI_CMD_WITH_ARG( "autoneg", autonegotiation_test, 0, "autoneg" ),
  CLI_CMD_WITH_ARG( "loopback_en", enable_loopback_mode, 0, "loopback_en" ),
  CLI_CMD_WITH_ARG( "loopback_dis", disable_loopback_mode, 0, "loopback_dis" ),
  CLI_CMD_TERMINATE()
};

static void eth_init_test(const struct cli_cmd_entry *pEntry)
{
	(void)pEntry;
	CLI_printf("eth init test is called\n\r");
	for (uint8_t i = 0; i < 16; i++)
	{
		eth_send_buf_0[i] = i;
	}
	for (uint8_t i = 0; i < 17; i++)
	{
		eth_send_buf_1[i] = 2*i;
	}
	for (uint8_t i = 0; i < 18; i++)
	{
		eth_send_buf_2[i] = 3*i;
	}
	for (uint8_t i = 0; i < 19; i++)
	{
		eth_send_buf_3[i] = 4*i;
	}
	if(1 == lan8720_basic_init(1))
	{
		CLI_printf("failed phy initialization\n\r");
	}

	udma_eth_open(0);
}

static void autonegotiation_test(const struct cli_cmd_entry *pEntry)
{
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
}
static void link_status_test(const struct cli_cmd_entry *pEntry)
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
	}
	else
	{
		CLI_printf("LINK_DOWN\n\r");
	}
}

static void enable_loopback_mode(const struct cli_cmd_entry *pEntry)
{
	enable_loopback();
}

static void disable_loopback_mode(const struct cli_cmd_entry *pEntry)
{
	disable_loopback();
}

static void phy_dump_test(const struct cli_cmd_entry *pEntry)
{
	(void)pEntry;
	CLI_printf("phy dump test is called\n\r");
	udma_smi_dump(1);
}


static void eth_send_test(const struct cli_cmd_entry *pEntry)
{
	(void)pEntry;
	CLI_printf("eth send test is called\n\r");
	switch(test_num)
	{
	case 0:
		udma_eth_write(16, eth_send_buf_0);
		test_num = 1;
		break;
	case 1:
		udma_eth_write(17, eth_send_buf_1);
		test_num = 2;
		break;
	case 2:
		udma_eth_write(18, eth_send_buf_2);
		test_num = 3;
		break;
	case 3:
		udma_eth_write(19, eth_send_buf_3);
		test_num = 0;
		break;
	}

	return;
}

static void eth_recv_test(const struct cli_cmd_entry *pEntry)
{
	(void)pEntry;
	uint16_t recv_length = 0;
	uint16_t i = 0;
	CLI_printf("eth recv test is called\n\r");
	recv_length = udma_eth_read(0, eth_recv_buf);
	if(0 == recv_length)
	{
		CLI_printf("no data to receive\n\r");
	}
	else
	{
		CLI_printf("received %d bytes \n\r", (int)recv_length);
	}

	while (i < recv_length)
	{
		CLI_printf("%x \n\r", (uint32_t)(eth_recv_buf[i]));
		i += 1;
	}

	return;
}
static void eth_set_test(const struct cli_cmd_entry *pEntry)
{
	(void)pEntry;
	CLI_printf("eth set test is called\n\r");
	udma_smi_rst(1);
}

static void eth_reset_test(const struct cli_cmd_entry *pEntry)
{
	(void)pEntry;
	CLI_printf("eth set test is called\n\r");
	udma_smi_rst(0);
}

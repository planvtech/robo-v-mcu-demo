/*
* Copyright 2021 QuickLogic
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* SPDX-License-Identifier: Apache-2.0
*/

#include "target/core-v-mcu/include/core-v-mcu-config.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "hal/include/hal_udma_ctrl_reg_defs.h"
#include "hal/include/hal_udma_ethernet_reg_defs.h"
#include "drivers/include/udma_ethernet_driver.h"

uint8_t read_queue = 0;

uint8_t eth_rd_buf_0[1024];
uint8_t eth_rd_buf_1[1024];
uint8_t eth_rd_buf_2[1024];
uint8_t eth_rd_buf_3[1024];
uint8_t* recv_addr;

uint16_t udma_eth_open(uint8_t eth_id) {
	UdmaEthernet_t *peth = (UdmaEthernet_t*)(UDMA_CH_ADDR_ETH + eth_id * UDMA_CH_SIZE);
	volatile UdmaCtrl_t* pudma_ctrl = (UdmaCtrl_t*)UDMA_CH_ADDR_CTRL;
	pudma_ctrl->reg_rst |= (UDMA_CTRL_ETH0_CLKEN << eth_id);
	pudma_ctrl->reg_rst &= ~(UDMA_CTRL_ETH0_CLKEN << eth_id);
	pudma_ctrl->reg_cg |= (UDMA_CTRL_ETH0_CLKEN << eth_id);


	return 0;
}

uint16_t udma_eth_start(uint8_t eth_id)
{
	UdmaEthernet_t *peth = (UdmaEthernet_t*)(UDMA_CH_ADDR_ETH + eth_id * UDMA_CH_SIZE);
	/* configure */
	uint32_t rx_addr_0 = (uint32_t)(eth_rd_buf_0);
	CLI_printf("Assigning rx_saddr_0 to %x\n\r", rx_addr_0);
	peth->rx_saddr_0 = rx_addr_0;

	uint32_t rx_addr_1 = (uint32_t)(eth_rd_buf_1);
	CLI_printf("Assigning rx_saddr_1 to %x\n\r", rx_addr_1);
	peth->rx_saddr_1 = rx_addr_1;

	uint32_t rx_addr_2 = (uint32_t)(eth_rd_buf_2);
	CLI_printf("Assigning rx_saddr_2 to %x\n\r", rx_addr_2);
	peth->rx_saddr_2 = rx_addr_2;

	uint32_t rx_addr_3 = (uint32_t)(eth_rd_buf_3);
	CLI_printf("Assigning rx_saddr_3 to %x\n\r", rx_addr_3);
	peth->rx_saddr_3 = rx_addr_3;

	peth->eth_setup_b.tx_enable = 1;

	CLI_printf("rx_saddr_0 is assigned to to %x\n\r", peth->rx_saddr_0);
	CLI_printf("rx_saddr_1 is assigned to to %x\n\r", peth->rx_saddr_1);
	CLI_printf("rx_saddr_2 is assigned to to %x\n\r", peth->rx_saddr_2);
	CLI_printf("rx_saddr_3 is assigned to to %x\n\r", peth->rx_saddr_3);

	recv_addr = eth_rd_buf_0;
	// Don't forget to check if the memory was successfully allocated
	if (!eth_rd_buf_0 || !eth_rd_buf_1 || !eth_rd_buf_2 || !eth_rd_buf_3) {
	    return 1;
	}


	peth->eth_setup_b.rx_enable = 1;

	return 0;
}

uint16_t udma_eth_write(uint16_t write_len, uint8_t* write_buffer) {
	UdmaEthernet_t*	peth = (UdmaEthernet_t*)(UDMA_CH_ADDR_ETH0);

	while (peth->status_b.busy) {  // ToDo: Why is this necessary?  Thought the semaphore should have protected
		CLI_printf(".");
	}

	peth->tx_saddr = (uint32_t)write_buffer;
	peth->tx_size = write_len;
	peth->tx_cfg_b.en = 1; //enable the transfer

	return 0;
}
uint16_t udma_eth_get_read_len() {
	UdmaEthernet_t*	peth = (UdmaEthernet_t*)(UDMA_CH_ADDR_ETH0);
	uint32_t descriptor_0;
	uint32_t descriptor_1;
	uint16_t recv_len = 0;
	//read_queue


	if(read_queue == 0)
	{
		descriptor_0 = peth->rx_desc_0;
		//if(((descriptor_0 & 0x80000000) != 0) && ((descriptor_1 & 0x80000000) != 0))
		if((descriptor_0 & 0x80000000) != 0)
		{
			recv_len = descriptor_0 & 0x00000FFF;
			peth->rx_desc_0 = 0;
		}
		else
			read_queue ++;
	}
	else if(read_queue == 1)
	{
		descriptor_0 = peth->rx_desc_1;
		if((descriptor_0 & 0x80000000) != 0)
		{
			recv_len = descriptor_0 & 0x00000FFF;
			peth->rx_desc_1 = 0;
		}
		else
			read_queue ++;
	}
	else if(read_queue == 2)
	{
		descriptor_0 = peth->rx_desc_2;
		if((descriptor_0 & 0x80000000) != 0)
		{
			recv_len = descriptor_0 & 0x00000FFF;
			peth->rx_desc_2 = 0;
		}
		else
			read_queue ++;
	}
	else if(read_queue == 3)
	{
		descriptor_0 = peth->rx_desc_3;
		if((descriptor_0 & 0x80000000) != 0)
		{
			recv_len = descriptor_0 & 0x00000FFF;
			peth->rx_desc_3 = 0;
		}
		else
			read_queue = 0;
	}

	if(recv_len != 0)
		CLI_printf("len : %d\n\r", recv_len);
	return recv_len;
}
 uint16_t udma_eth_read(uint16_t read_len, uint8_t* read_buffer) {
	UdmaEthernet_t*	peth = (UdmaEthernet_t*)(UDMA_CH_ADDR_ETH0);
	uint32_t descriptor;
	int test_loop = 0;
	CLI_printf("rq : %d\n\r", read_queue);
	switch(read_queue)
	{
		case 0:
			recv_addr = eth_rd_buf_0;
			break;
		case 1:
			recv_addr = eth_rd_buf_1;
			break;
		case 2:
			recv_addr = eth_rd_buf_2;
			break;
		case 3:
			recv_addr = eth_rd_buf_3;
			break;
	}
	if(read_queue == 3)
		read_queue = 0;
	else
		read_queue ++;
	memcpy(read_buffer, recv_addr, read_len);
//	CLI_printf("d : \n\r");
//	while(test_loop < read_len)
//	{
//		CLI_printf("%x ", (uint32_t)(read_buffer[test_loop]));
//		test_loop += 1;
//	}
//	CLI_printf("\n\r");
	return read_len;
}

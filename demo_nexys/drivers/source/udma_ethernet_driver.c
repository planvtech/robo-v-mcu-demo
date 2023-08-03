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
#include <stdio.h>
#include <stdint.h>
#include "hal/include/hal_udma_ctrl_reg_defs.h"
#include "hal/include/hal_udma_ethernet_reg_defs.h"
#include "drivers/include/udma_ethernet_driver.h"

static UdmaEthernet_t *peth = (UdmaEthernet_t*)(UDMA_CH_ADDR_ETH);
uint8_t read_queue = 0;
uint8_t* recv_addr;
uint8_t eth_rd_buf_0[4096];
uint8_t eth_rd_buf_1[4096];
uint8_t eth_rd_buf_2[4096];
uint8_t eth_rd_buf_3[4096];
uint16_t udma_eth_open (uint8_t eth_id) {
	UdmaEthernet_t*				peth;
	volatile UdmaCtrl_t*		pudma_ctrl = (UdmaCtrl_t*)UDMA_CH_ADDR_CTRL;

	/* Enable reset and enable eth clock */
	pudma_ctrl->reg_rst |= (UDMA_CTRL_ETH0_CLKEN << eth_id);
	pudma_ctrl->reg_rst &= ~(UDMA_CTRL_ETH0_CLKEN << eth_id);
	pudma_ctrl->reg_cg |= (UDMA_CTRL_ETH0_CLKEN << eth_id);


	/* configure */
	peth = (UdmaEthernet_t*)(UDMA_CH_ADDR_ETH + eth_id * UDMA_CH_SIZE);
	peth->eth_setup_b.tx_enable = 1;
	peth->rx_saddr_0 = (uint32_t)(eth_rd_buf_0);
	peth->rx_saddr_1 = (uint32_t)(eth_rd_buf_1);
	peth->rx_saddr_2 = (uint32_t)(eth_rd_buf_2);
	peth->rx_saddr_3 = (uint32_t)(eth_rd_buf_3);
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

 uint16_t udma_eth_read(uint16_t read_len, uint8_t* read_buffer) {
	 UdmaEthernet_t*	peth = (UdmaEthernet_t*)(UDMA_CH_ADDR_ETH0);
	 uint32_t descriptor;
	 uint8_t recv_len = 0;
	 int test_loop = 0;
	 for(uint8_t i = 0; i < 4; i ++)
	 {
		 switch(read_queue)
		 {
		 	 case 0:
		 		descriptor = peth->rx_desc_0;
		 		if(descriptor == 0)
		 		{
		 			CLI_printf("buffer 0 desc = 0\n\r");
		 		}
		 		else
		 		{
		 			CLI_printf("descriptor0 = %x\n\r", descriptor);
		 		}

		 		if((descriptor & 0x80000000) != 0)
		 		{
		 			recv_len = descriptor & 0x00000FFF;
		 			recv_addr = eth_rd_buf_0;
		 			read_queue = 1;
		 			CLI_printf("received data at buffer 0\n\r");
		 			CLI_printf("length : %d\n\r", recv_len);
		 			peth->rx_desc_0 = 0;
		 		}
		 		break;
		 	case 1:
				descriptor = peth->rx_desc_1;
				if(descriptor == 0)
				{
					CLI_printf("buffer 1 desc = 0\n\r");
				}
				else
				{
					CLI_printf("descriptor1 = %x\n\r", descriptor);
				}
				if((descriptor & 0x80000000) != 0)
				{
					recv_len = descriptor & 0x00000FFF;
					recv_addr = eth_rd_buf_1;
					read_queue = 2;
					CLI_printf("received data at buffer 1\n\r");
					CLI_printf("length : %d\n\r", recv_len);
					peth->rx_desc_1 = 0;
				}
				break;
		 	case 2:
				descriptor = peth->rx_desc_2;
				if(descriptor == 0)
				{
					CLI_printf("buffer 2 desc = 0\n\r");
				}
				else
				{
					CLI_printf("descriptor2 = %x\n\r", descriptor);
				}
				if((descriptor & 0x80000000) != 0)
				{
					recv_len = descriptor & 0x00000FFF;
					recv_addr = eth_rd_buf_2;
					read_queue = 3;
					CLI_printf("received data at buffer 2\n\r");
					CLI_printf("length : %d\n\r", recv_len);
					peth->rx_desc_2 = 0;
				}
				break;
		 	case 3:
				descriptor = peth->rx_desc_3;
				if(descriptor == 0)
				{
					CLI_printf("buffer 3 desc = 0\n\r");
				}
				else
				{
					CLI_printf("descriptor3 = %x\n\r", descriptor);
				}

				if((descriptor & 0x80000000) != 0)
				{
					recv_len = descriptor & 0x00000FFF;
					recv_addr = eth_rd_buf_3;
					read_queue = 0;
					CLI_printf("received data at buffer 3\n\r");
					CLI_printf("length : %d\n\r", recv_len);
					peth->rx_desc_3 = 0;
				}
				break;
		 }
		 if(recv_len != 0)
		 {
			 break;
		 }
		 if(read_queue == 3)
		 {
			 read_queue = 0;
		 }
		 else
		 {
			 read_queue += 1;
		 }
	 }
	 if(recv_len != 0)
	 {
		 if(read_len == 0)
		 {
			 memcpy(read_buffer, recv_addr, recv_len);
//			 CLI_printf("received data : \n\r");
//			 while(test_loop < recv_len)
//			 {
//				 CLI_printf("%x \n\r", (uint32_t)(read_buffer[test_loop]));
//				 test_loop += 1;
//			 }
			 return recv_len;
		 }
		 else
		 {
			 memcpy(read_buffer, recv_addr, read_len);
			 return read_len;
		 }
	 }
	 else
	 {
		 return 0;
	 }
}

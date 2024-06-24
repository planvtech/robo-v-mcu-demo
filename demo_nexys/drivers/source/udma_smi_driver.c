/*
 * udma_mdio_driver.c
 *
 *  Created on: Sep 5, 2023
 *      Author: mkdigitals
 */
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

#include <drivers/include/udma_smi_driver.h>
#include "target/core-v-mcu/include/core-v-mcu-config.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "hal/include/hal_udma_ctrl_reg_defs.h"
#include "hal/include/hal_udma_smi_reg_defs.h"

uint8_t udma_smi_open()
{
	volatile UdmaCtrl_t*		pudma_ctrl = (UdmaCtrl_t*)UDMA_CH_ADDR_CTRL;
	//phy_addr_const = phy_addr;
	// uint16_t phy_recv_data;
	/* Enable reset and enable eth clock */
	pudma_ctrl->reg_rst |= (UDMA_CTRL_SMI0_CLKEN);
	pudma_ctrl->reg_rst &= ~(UDMA_CTRL_SMI0_CLKEN);
	pudma_ctrl->reg_cg |= (UDMA_CTRL_SMI0_CLKEN);
	// phy_addr_const = phy_addr;
	// CLI_printf("SMI init - phy_addr = %x\n\r",(uint32_t)phy_addr_const);
	// phy_recv_data = udma_smi_read(2);
	// CLI_printf("SMI init - phy_id = %x\n\r",(uint32_t)phy_recv_data);
	// phy_recv_data = udma_smi_read(1);
	// CLI_printf("SMI init - phy_status = %x\n\r",(uint32_t)phy_recv_data);
	// udma_smi_write(0, 0x1000);
	// CLI_printf("SMI init - phy ctrl set\n\r");
	// phy_recv_data = udma_smi_read(0);
	// CLI_printf("SMI init - phy_ctrl_reg = %x\n\r",(uint32_t)phy_recv_data);
	// for (uint8_t i = 0; i < 32; i ++)
	// {
	// 	phy_recv_data = udma_smi_read(i);
	// 	CLI_printf("SMI read - phy_reg %x = %x\n\r", (uint32_t)i, (uint32_t)phy_recv_data);
	// }
	return 0;
}

void	udma_smi_write(uint8_t phy_addr, uint8_t reg_addr , uint16_t write_data)
{
	UdmaSmi_t*	psmi = (UdmaSmi_t*)(UDMA_CH_ADDR_SMI);
	while(psmi->phy_busy == 1)
	{
		CLI_printf(".");
	};
	psmi->phy_addr = phy_addr;
	psmi->reg_addr = reg_addr;
	psmi->tx_data = write_data;
	psmi->phy_rw = 1;
	psmi->phy_en = 1;
	psmi->phy_en = 0;
};

uint16_t udma_smi_read(uint8_t phy_addr, uint8_t reg_addr)
{
	UdmaSmi_t*	psmi = (UdmaSmi_t*)(UDMA_CH_ADDR_SMI);
	CLI_printf("-");
	uint16_t result = 0;
	while(psmi->phy_busy == 1)
	{
		CLI_printf("-");
	}
	psmi->phy_addr = phy_addr;
	psmi->reg_addr = reg_addr;
	psmi->phy_rw = 0;
	psmi->phy_en = 1;
	psmi->phy_en = 0;
	while(psmi->phy_busy == 1)
	{
		CLI_printf("-");
	}
	while(psmi->phy_nd == 0)
	{
		CLI_printf("_");
	};

	result = (uint16_t)psmi->rx_data;
	return result;
};

void udma_smi_dump(uint8_t phy_addr){
	uint16_t phy_recv_data;
	for (uint8_t i = 0; i < 32; i ++)
	{
		phy_recv_data = udma_smi_read(phy_addr, i);
		CLI_printf("SMI read - phy_reg %x = %x\n\r", (uint32_t)i, (uint32_t)phy_recv_data);
	}
}

void udma_smi_rst(uint8_t rst_val)
{
	UdmaSmi_t*	psmi = (UdmaSmi_t*)(UDMA_CH_ADDR_SMI);
	while(psmi->phy_busy == 1)
	{
		CLI_printf(".");
	}
	psmi->phy_rstn = rst_val;
};

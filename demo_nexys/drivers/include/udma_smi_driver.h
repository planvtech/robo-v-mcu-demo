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

#ifndef __UDMA_SMI_DRIVER_H_
#define __UDMA_SMI_DRIVER_H_

#include "stdint.h"

#include "hal/include/hal_udma_ctrl_reg_defs.h"

typedef enum {
		kSMIDataValid
} udma_smi_control_type_t;
void	udma_smi_open(uint8_t phy_addr);
void	udma_smi_write(uint8_t reg_addr, uint16_t write_data);
uint16_t udma_smi_read(uint8_t reg_addr);
void	udma_smi_rst(uint8_t rst_val);

#endif //__UDMA_SMI_DRIVER_H_

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
 
#ifndef __UDMA_ETHERNET_DRIVER_H_
#define __UDMA_ETHERNET_DRIVER_H_

#include "stdint.h"

#include "hal/include/hal_udma_ctrl_reg_defs.h"

typedef enum {
		kEthDataValid
} udma_eth_control_type_t;

uint16_t udma_eth_open (uint8_t eth_id);
uint16_t udma_eth_start(uint8_t eth_id);
uint16_t udma_eth_write(uint16_t write_len, uint8_t* write_buffer);
uint16_t udma_eth_get_read_len();
uint16_t udma_eth_read(uint16_t read_len, uint8_t* read_buffer);

#endif //__UDMA_ETHERNET_DRIVER_H_

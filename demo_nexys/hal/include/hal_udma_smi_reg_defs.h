/*
 * This is a generated file
 * 
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

#ifndef __UDMA_SMI_H_
#define __UDMA_SMI_H_

//---------------------------------//
//
// Module: UDMA_SMI
//
//---------------------------------//

#ifndef __IO
#define __IO volatile
#endif

#ifndef __I
#define __I volatile
#endif

#ifndef __O
#define __O volatile
#endif

#include "stdint.h"

typedef struct {

  // Offset = 0x0000
  union {
    __IO uint32_t phy_rw;
    struct {
      __IO uint32_t  rw         :  1;
    } phy_rw_b;
  };

  // Offset = 0x0004
  union {
    __IO uint32_t phy_en;
    struct {
      __IO uint32_t  en         :  1;
    } phy_en_b;
  };

  // Offset = 0x0008
  union {
    __IO uint32_t phy_nd;
    struct {
      __IO uint32_t  nd         :  1;
    } phy_nd_b;
  };

  // Offset = 0x000c
  union {
    __IO uint32_t phy_busy;
    struct {
      __IO uint32_t  busy       :  1;
    } phy_busy_b;
  };

  // Offset = 0x0010
  union {
    __IO uint32_t phy_addr;
    struct {
      __IO uint32_t  addr       :  5;
    } phy_addr_b;
  };

  // Offset = 0x0014
  union {
    __IO uint32_t reg_addr;
    struct {
      __IO uint32_t  addr       :  5;
    } reg_addr_b;
  };

  // Offset = 0x0018
  union {
    __IO uint32_t tx_data;
    struct {
      __IO uint32_t  data       : 16;
    } tx_data_b;
  };

  // Offset = 0x001c
  union {
    __IO uint32_t rx_data;
    struct {
      __IO uint32_t  data       : 16;
    } rx_data_b;
  };

  // Offset = 0x0020
  union {
    __IO uint32_t phy_rstn;
    struct {
      __IO uint32_t  data       :  1;
    } phy_rstn_b;
  };
} UdmaSmi_t;


#define REG_PHY_RW                     0x00
#define   REG_PHY_RW_rw_LSB                        0
#define   REG_PHY_RW_rw_MASK                       0x1
#define REG_PHY_EN                     0x04
#define   REG_PHY_EN_en_LSB                        0
#define   REG_PHY_EN_en_MASK                       0x1
#define REG_PHY_ND                     0x08
#define   REG_PHY_ND_nd_LSB                        0
#define   REG_PHY_ND_nd_MASK                       0x1
#define REG_PHY_BUSY                   0x0C
#define   REG_PHY_BUSY_busy_LSB                    0
#define   REG_PHY_BUSY_busy_MASK                   0x1
#define REG_PHY_ADDR                   0x10
#define   REG_PHY_ADDR_addr_LSB                    0
#define   REG_PHY_ADDR_addr_MASK                   0x1f
#define REG_REG_ADDR                   0x14
#define   REG_REG_ADDR_addr_LSB                    0
#define   REG_REG_ADDR_addr_MASK                   0x1f
#define REG_TX_DATA                    0x18
#define   REG_TX_DATA_data_LSB                     0
#define   REG_TX_DATA_data_MASK                    0xffff
#define REG_RX_DATA                    0x1C
#define   REG_RX_DATA_data_LSB                     0
#define   REG_RX_DATA_data_MASK                    0xffff
#define REG_PHY_RSTN                   0x20
#define   REG_PHY_RSTN_data_LSB                    0
#define   REG_PHY_RSTN_data_MASK                   0x1

#ifndef __REGFIELD_OPS_
#define __REGFIELD_OPS_
static inline uint32_t regfield_read(uint32_t reg, uint32_t mask, uint32_t lsb) {
  return (reg >> lsb) & mask;
}
static inline uint32_t regfield_write(uint32_t reg, uint32_t mask, uint32_t lsb, uint32_t value) {
  reg &= ~(mask << lsb);
  reg |= (value & mask) << lsb;
  return reg;
}
#endif  // __REGFIELD_OPS_

#endif // __UDMA_SMI_H_

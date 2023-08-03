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

#ifndef __UDMA_ETHERNET_H_
#define __UDMA_ETHERNET_H_

//---------------------------------//
//
// Module: UDMA_ETHERNET
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
    __IO uint32_t rx_saddr_0;
    struct {
      __IO uint32_t  saddr_0    : 32;
    } rx_saddr_0_b;
  };

  // Offset = 0x0004
  union {
    __IO uint32_t rx_saddr_1;
    struct {
      __IO uint32_t  saddr_1    : 32;
    } rx_saddr_1_b;
  };

  // Offset = 0x0008
  union {
    __IO uint32_t rx_saddr_2;
    struct {
      __IO uint32_t  saddr_2    : 32;
    } rx_saddr_2_b;
  };

  // Offset = 0x000c
  union {
    __IO uint32_t rx_saddr_3;
    struct {
      __IO uint32_t  saddr_3    : 32;
    } rx_saddr_3_b;
  };

  // Offset = 0x0010
  union {
    __IO uint32_t rx_desc_0;
    struct {
      __IO uint32_t  desc_0     : 32;
    } rx_desc_0_b;
  };

  // Offset = 0x0014
  union {
    __IO uint32_t rx_desc_1;
    struct {
      __IO uint32_t  desc_1     : 32;
    } rx_desc_1_b;
  };

  // Offset = 0x0018
  union {
    __IO uint32_t rx_desc_2;
    struct {
      __IO uint32_t  desc_2     : 32;
    } rx_desc_2_b;
  };

  // Offset = 0x001c
  union {
    __IO uint32_t rx_desc_3;
    struct {
      __IO uint32_t  desc_3     : 32;
    } rx_desc_3_b;
  };

  // Offset = 0x0020
  union {
    __IO uint32_t eth_reg_rx_caddr;
    struct {
      __IO uint32_t  rx_caddr   : 32;
    } eth_reg_rx_caddr_b;
  };

  // Offset = 0x0024
  union {
    __IO uint32_t rx_size;
    struct {
      __IO uint32_t  size       : 16;
    } rx_size_b;
  };

  // Offset = 0x0028
  union {
    __IO uint32_t rx_cfg;
    struct {
      __IO uint32_t  continuous :  1;
      __IO uint32_t             :  3;
      __IO uint32_t  en         :  1;
      __IO uint32_t  pending    :  1;
      __IO uint32_t  clr        :  1;
    } rx_cfg_b;
  };

  // Offset = 0x002c
  union {
    __IO uint32_t tx_saddr;
    struct {
      __IO uint32_t  saddr      : 12;
    } tx_saddr_b;
  };

  // Offset = 0x0030
  union {
    __IO uint32_t tx_size;
    struct {
      __IO uint32_t  size       : 16;
    } tx_size_b;
  };

  // Offset = 0x0034
  union {
    __IO uint32_t tx_cfg;
    struct {
      __IO uint32_t  continuous :  1;
      __IO uint32_t             :  3;
      __IO uint32_t  en         :  1;
      __IO uint32_t  pending    :  1;
      __IO uint32_t  clr        :  1;
    } tx_cfg_b;
  };

  // Offset = 0x0038
  union {
    __IO uint32_t status;
    struct {
      __IO uint32_t  rx_fifo_good_frame :  1;
      __IO uint32_t  rx_fifo_bad_frame :  1;
      __IO uint32_t  rx_fifo_overflow :  1;
      __IO uint32_t  rx_error_bad_fcs :  1;
      __IO uint32_t  rx_error_bad_frame :  1;
      __IO uint32_t  tx_fifo_good_frame :  1;
      __IO uint32_t  tx_fifo_bad_frame :  1;
      __IO uint32_t  tx_fifo_overflow :  1;
      __IO uint32_t  speed      :  2;
      __IO uint32_t  busy       :  1;
    } status_b;
  };

  // Offset = 0x003c
  union {
    __IO uint32_t eth_setup;
    struct {
      __IO uint32_t             :  8;
      __IO uint32_t  tx_enable  :  1;
      __IO uint32_t  rx_enable  :  1;
    } eth_setup_b;
  };

  // Offset = 0x0040
  union {
    __IO uint32_t error;
    struct {
      __IO uint32_t  rx_error_fifo_bad_frame :  1;
      __IO uint32_t  rx_error_fifo_overflow :  1;
      __IO uint32_t  rx_error_bad_fcs :  1;
      __IO uint32_t  rx_error_bad_frame :  1;
      __IO uint32_t  tx_error_fifo_bad_frame :  1;
      __IO uint32_t  tx_error_fifo_overflow :  1;
    } error_b;
  };

  // Offset = 0x0044
  union {
    __IO uint32_t irq_en;
    struct {
      __IO uint32_t  rx_irq_en  :  1;
      __IO uint32_t  err_irq_en :  1;
    } irq_en_b;
  };

  // Offset = 0x0048
  union {
    __IO uint32_t rx_fcs;
    struct {
      __IO uint32_t  rx_fcs     : 32;
    } rx_fcs_b;
  };

  // Offset = 0x004c
  union {
    __IO uint32_t tx_fcs;
    struct {
      __IO uint32_t  tx_fcs     : 32;
    } tx_fcs_b;
  };
} UdmaEthernet_t;


#define REG_RX_SADDR_0                 0x00
#define   REG_RX_SADDR_0_SADDR_0_LSB               0
#define   REG_RX_SADDR_0_SADDR_0_MASK              0xffffffff
#define REG_RX_SADDR_1                 0x04
#define   REG_RX_SADDR_1_SADDR_1_LSB               0
#define   REG_RX_SADDR_1_SADDR_1_MASK              0xffffffff
#define REG_RX_SADDR_2                 0x08
#define   REG_RX_SADDR_2_SADDR_2_LSB               0
#define   REG_RX_SADDR_2_SADDR_2_MASK              0xffffffff
#define REG_RX_SADDR_3                 0x0C
#define   REG_RX_SADDR_3_SADDR_3_LSB               0
#define   REG_RX_SADDR_3_SADDR_3_MASK              0xffffffff
#define REG_RX_DESC_0                  0x10
#define   REG_RX_DESC_0_DESC_0_LSB                 0
#define   REG_RX_DESC_0_DESC_0_MASK                0xffffffff
#define REG_RX_DESC_1                  0x14
#define   REG_RX_DESC_1_DESC_1_LSB                 0
#define   REG_RX_DESC_1_DESC_1_MASK                0xffffffff
#define REG_RX_DESC_2                  0x18
#define   REG_RX_DESC_2_DESC_2_LSB                 0
#define   REG_RX_DESC_2_DESC_2_MASK                0xffffffff
#define REG_RX_DESC_3                  0x1C
#define   REG_RX_DESC_3_DESC_3_LSB                 0
#define   REG_RX_DESC_3_DESC_3_MASK                0xffffffff
#define REG_ETH_REG_RX_CADDR           0x20
#define   REG_ETH_REG_RX_CADDR_RX_CADDR_LSB        0
#define   REG_ETH_REG_RX_CADDR_RX_CADDR_MASK       0xffffffff
#define REG_RX_SIZE                    0x24
#define   REG_RX_SIZE_SIZE_LSB                     0
#define   REG_RX_SIZE_SIZE_MASK                    0xffff
#define REG_RX_CFG                     0x28
#define   REG_RX_CFG_CLR_LSB                       6
#define   REG_RX_CFG_CLR_MASK                      0x1
#define   REG_RX_CFG_PENDING_LSB                   5
#define   REG_RX_CFG_PENDING_MASK                  0x1
#define   REG_RX_CFG_EN_LSB                        4
#define   REG_RX_CFG_EN_MASK                       0x1
#define   REG_RX_CFG_CONTINUOUS_LSB                0
#define   REG_RX_CFG_CONTINUOUS_MASK               0x1
#define REG_TX_SADDR                   0x2C
#define   REG_TX_SADDR_SADDR_LSB                   0
#define   REG_TX_SADDR_SADDR_MASK                  0xfff
#define REG_TX_SIZE                    0x30
#define   REG_TX_SIZE_SIZE_LSB                     0
#define   REG_TX_SIZE_SIZE_MASK                    0xffff
#define REG_TX_CFG                     0x34
#define   REG_TX_CFG_CLR_LSB                       6
#define   REG_TX_CFG_CLR_MASK                      0x1
#define   REG_TX_CFG_PENDING_LSB                   5
#define   REG_TX_CFG_PENDING_MASK                  0x1
#define   REG_TX_CFG_EN_LSB                        4
#define   REG_TX_CFG_EN_MASK                       0x1
#define   REG_TX_CFG_CONTINUOUS_LSB                0
#define   REG_TX_CFG_CONTINUOUS_MASK               0x1
#define REG_STATUS                     0x38
#define   REG_STATUS_busy_LSB                      10
#define   REG_STATUS_busy_MASK                     0x1
#define   REG_STATUS_speed_LSB                     8
#define   REG_STATUS_speed_MASK                    0x3
#define   REG_STATUS_TX_FIFO_OVERFLOW_LSB          7
#define   REG_STATUS_TX_FIFO_OVERFLOW_MASK         0x1
#define   REG_STATUS_TX_FIFO_BAD_FRAME_LSB         6
#define   REG_STATUS_TX_FIFO_BAD_FRAME_MASK        0x1
#define   REG_STATUS_TX_FIFO_GOOD_FRAME_LSB        5
#define   REG_STATUS_TX_FIFO_GOOD_FRAME_MASK       0x1
#define   REG_STATUS_RX_ERROR_BAD_FRAME_LSB        4
#define   REG_STATUS_RX_ERROR_BAD_FRAME_MASK       0x1
#define   REG_STATUS_RX_ERROR_BAD_FCS_LSB          3
#define   REG_STATUS_RX_ERROR_BAD_FCS_MASK         0x1
#define   REG_STATUS_RX_FIFO_OVERFLOW_LSB          2
#define   REG_STATUS_RX_FIFO_OVERFLOW_MASK         0x1
#define   REG_STATUS_RX_FIFO_BAD_FRAME_LSB         1
#define   REG_STATUS_RX_FIFO_BAD_FRAME_MASK        0x1
#define   REG_STATUS_RX_FIFO_GOOD_FRAME_LSB        0
#define   REG_STATUS_RX_FIFO_GOOD_FRAME_MASK       0x1
#define REG_ETH_SETUP                  0x3C
#define   REG_ETH_SETUP_RX_ENABLE_LSB              9
#define   REG_ETH_SETUP_RX_ENABLE_MASK             0x1
#define   REG_ETH_SETUP_TX_ENABLE_LSB              8
#define   REG_ETH_SETUP_TX_ENABLE_MASK             0x1
#define REG_ERROR                      0x40
#define   REG_ERROR_TX_ERROR_FIFO_OVERFLOW_LSB     5
#define   REG_ERROR_TX_ERROR_FIFO_OVERFLOW_MASK    0x1
#define   REG_ERROR_TX_ERROR_FIFO_BAD_FRAME_LSB    4
#define   REG_ERROR_TX_ERROR_FIFO_BAD_FRAME_MASK   0x1
#define   REG_ERROR_RX_ERROR_BAD_FRAME_LSB         3
#define   REG_ERROR_RX_ERROR_BAD_FRAME_MASK        0x1
#define   REG_ERROR_RX_ERROR_BAD_FCS_LSB           2
#define   REG_ERROR_RX_ERROR_BAD_FCS_MASK          0x1
#define   REG_ERROR_RX_ERROR_FIFO_OVERFLOW_LSB     1
#define   REG_ERROR_RX_ERROR_FIFO_OVERFLOW_MASK    0x1
#define   REG_ERROR_RX_ERROR_FIFO_BAD_FRAME_LSB    0
#define   REG_ERROR_RX_ERROR_FIFO_BAD_FRAME_MASK   0x1
#define REG_IRQ_EN                     0x44
#define   REG_IRQ_EN_ERR_IRQ_EN_LSB                1
#define   REG_IRQ_EN_ERR_IRQ_EN_MASK               0x1
#define   REG_IRQ_EN_RX_IRQ_EN_LSB                 0
#define   REG_IRQ_EN_RX_IRQ_EN_MASK                0x1
#define REG_RX_FCS                     0x48
#define   REG_RX_FCS_rx_fcs_LSB                    0
#define   REG_RX_FCS_rx_fcs_MASK                   0xffffffff
#define REG_TX_FCS                     0x4C
#define   REG_TX_FCS_tx_fcs_LSB                    0
#define   REG_TX_FCS_tx_fcs_MASK                   0xffffffff

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

#endif // __UDMA_ETHERNET_H_

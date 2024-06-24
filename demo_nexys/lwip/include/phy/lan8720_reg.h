#ifndef LAN8720_REG_H
#define LAN8720_REG_H

#include "stdint.h"

// Basic Control Register
#define BASIC_CONTROL_REG_ADDR 0x00
#define SOFT_RESET_BIT         (1 << 15)
#define LOOPBACK_BIT           (1 << 14)
#define SPEED_SELECT_BIT       (1 << 13)
#define AUTO_NEG_ENABLE_BIT    (1 << 12)
#define POWER_DOWN_BIT         (1 << 11)
#define ISOLATE_BIT            (1 << 10)
#define RESTART_NEG_BIT        (1 << 9)
#define DUPLEX_MODE_BIT        (1 << 8)

// Basic Status Register
#define BASIC_STATUS_REG_ADDR  0x01
#define LINK_UP_BIT            (1 << 2)
#define AUTO_NEG_COMPLETE_BIT  (1 << 5)
#define LINK_STATUS_BIT        (1 << 2)

// PHY Identifier Registers
#define PHY_ID1_REG_ADDR       0x02
#define PHY_ID2_REG_ADDR       0x03

// Auto-Negotiation Advertisement Register
#define AUTO_NEG_ADV_REG_ADDR  0x04

// Auto-Negotiation Link Partner Ability Register
#define AUTO_NEG_LP_ABILITY_REG_ADDR  0x05

// Auto-Negotiation Expansion Register
#define AUTO_NEG_EXP_REG_ADDR  0x06

// Mode Control/Status Register
#define MODE_CTRL_STATUS_REG_ADDR 0x08
#define FAR_LOOPBACK_EN_BIT        (1 << 0)
#define ALT_INT_MODE_BIT           (1 << 14)
#define ENERGY_DETECT_BIT          (1 << 1)

// Special Modes Register
#define SPECIAL_MODES_REG_ADDR  0x12

// Symbol Error Counter Register
#define SYMBOL_ERR_CNT_REG_ADDR  0x1A

// Special Control/Status Indications Register
#define SPECIAL_CTRL_STATUS_REG_ADDR 0x1B
#define AUTONEG_DONE_BIT               (1 << 15)

// Interrupt Source Flag Register
#define INT_SOURCE_FLAG_REG_ADDR   0x1D

// Interrupt Mask Register
#define INT_MASK_REG_ADDR          0x1E

// PHY Special Control/Status Register
#define PHY_SPECIAL_CTRL_STATUS_REG_ADDR  0x1F




#endif // LAN8720_REG_H

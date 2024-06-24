/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @file      driver_lan8720_interface_template.c
 * @brief     driver lan8720 interface template source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2023-08-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2023/08/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "../include/phy/driver_lan8720_interface.h"

/**
 * @brief  interface smi bus init
 * @return status code
 *         - 0 success
 *         - 1 smi init failed
 * @note   none
 */
uint8_t lan8720_interface_smi_init(void)
{
    return udma_smi_open();
}

/**
 * @brief  interface smi bus deinit
 * @return status code
 *         - 0 success
 *         - 1 smi deinit failed
 * @note   none
 */
uint8_t lan8720_interface_smi_deinit(void)
{
    return 0;
}

/**
 * @brief      interface smi bus read
 * @param[in]  addr is the device address
 * @param[in]  reg is the register address
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t lan8720_interface_smi_read(uint8_t addr, uint8_t reg, uint16_t *data)
{
    *data = udma_smi_read(addr, reg);
    return 0;
}

/**
 * @brief     interface smi bus write
 * @param[in] addr is the device address
 * @param[in] reg is the register address
 * @param[in] data is the set data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t lan8720_interface_smi_write(uint8_t addr, uint8_t reg, uint16_t data)
{
    udma_smi_write(addr, reg, data);
    return 0;
}

/**
 * @brief  interface reset gpio init
 * @return status code
 *         - 0 success
 *         - 1 reset gpio init failed
 * @note   none
 */
uint8_t lan8720_interface_reset_gpio_init(void)
{
    udma_smi_rst(0);
    return 0;
}

/**
 * @brief  interface reset gpio deinit
 * @return status code
 *         - 0 success
 *         - 1 reset gpio deinit failed
 * @note   none
 */
uint8_t lan8720_interface_reset_gpio_deinit(void)
{
    udma_smi_rst(1);
    return 0;
}

/**
 * @brief     interface reset gpio write
 * @param[in] level is the set level
 * @return    status code
 *            - 0 success
 *            - 1 reset gpio write failed
 * @note      none
 */
uint8_t lan8720_interface_reset_gpio_write(uint8_t level)
{
    udma_smi_rst(level);
    return 0;
}

/**
 * @brief     interface delay ms
 * @param[in] ms
 * @note      none
 */
void lan8720_interface_delay_ms(uint32_t ms)
{
    intptr_t tstart;
    tstart = CLI_timeout_start();
    for(;;){
        if( CLI_timeout_expired(tstart, ms ) ){
            break;
        }
    }
}

/**
 * @brief     interface print format data
 * @param[in] fmt is the format data
 * @note      none
 */
void lan8720_interface_debug_print(const char *const fmt, ...)
{
	CLI_printf(fmt);
}

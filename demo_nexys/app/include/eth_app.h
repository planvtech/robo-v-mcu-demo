/*
 * eth_app.h
 *
 *  Created on: May 11, 2023
 *      Author: mkdigitals
 */

#ifndef APP_INCLUDE_ETH_APP_H_
#define APP_INCLUDE_ETH_APP_H_

#include "lwip/tcpip.h"
#include "lwip/tcp.h"
#include "lwip/netif.h"
#include "lwip/etharp.h"
#define 	ETH_TASK_PRIORITY		(tskIDLE_PRIORITY + 1)

int eth_create_task(void);

#endif /* APP_INCLUDE_ETH_APP_H_ */

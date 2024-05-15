/**
 * @file ciot_lib.h
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief CioT library header file
 * @version 0.1
 * @date 2024-05-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_LIB__H__
#define __CIOT_LIB__H__

/**
 * @defgroup hardware_types
 * @brief Types definitions of hardware resources
 */
#include "types/ciot_ble_types.h"
#include "types/ciot_ble_scn_types.h"
#include "types/ciot_tcp_types.h"
#include "types/ciot_gpio_types.h"
#include "types/ciot_tcp_types.h"
#include "types/ciot_wifi_types.h"
#include "types/ciot_storage_types.h"
#include "types/ciot_uart_types.h"
#include "types/ciot_usb_types.h"

/**
 * @defgroup hardware_interfaces
 * @brief Interfaces that implements hardware resources
 */
#include "ciot_ble.h"
#include "ciot_ble_scn.h"
#include "ciot_eth.h"
#include "ciot_gpio.h"
#include "ciot_tcp.h"
#include "ciot_wifi.h"
#include "ciot_storage.h"
#include "ciot_uart.h"
#include "ciot_usb.h"

/**
 * @defgroup software_types
 * @brief Types definitions of software resources
 */
#include "types/ciot_bridge_types.h"
#include "types/ciot_dfu_types.h"
#include "types/ciot_httpc_types.h"
#include "types/ciot_https_types.h"
#include "types/ciot_mqttc_types.h"
#include "types/ciot_ntp_types.h"
#include "types/ciot_opcuas_types.h"
#include "types/ciot_ota_types.h"
#include "types/ciot_sys_types.h"

/**
 * @defgroup software_interfaces
 * @brief Interfaces that implements software resources
 */
#include "ciot_bridge.h"
#include "ciot_dfu.h"
#include "ciot_httpc.h"
#include "ciot_https.h"
#include "ciot_mqttc.h"
#include "ciot_nrf_dfu.h"
#include "ciot_ntp.h"
#include "ciot_opcuas.h"
#include "ciot_opcuas.h"
#include "ciot_ota.h"
#include "ciot_sys.h"

#endif  //!__CIOT_LIB__H__
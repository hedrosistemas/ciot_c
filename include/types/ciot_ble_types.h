/**
 * @file ciot_ble_types.h
 * @ingroup hardware_types
 * @brief Defines data types and structures for CIOT BLE.
 * @version 0.1
 * @date 2023-11-20
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_BLE_TYPES__H__
#define __CIOT_BLE_TYPES__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

/**
 * @brief Enumeration for CIOT BLE states.
 */
typedef enum __attribute__((packed))
{
    CIOT_BLE_STATE_IDLE, /**< Idle state */
    CIOT_BLE_STATE_STARTED, /**< Started state */
} ciot_ble_state_t;

/**
 * @brief Enumeration for CIOT BLE request types.
 */
typedef enum __attribute__((packed))
{
    CIOT_BLE_REQ_UNKNOWN, /**< Unknown request type */
    CIOT_BLE_REQ_SET_MAC, /**< Set MAC request type */
} ciot_ble_req_type_t;

/**
 * @brief Structure for CIOT BLE configuration.
 */
typedef struct __attribute__((packed))
{
    uint8_t mac[6]; /**< MAC address */
} ciot_ble_cfg_t;

/**
 * @brief Structure for CIOT BLE information.
 */
typedef struct __attribute__((packed))
{
    uint8_t hw_mac[6]; /**< Hardware MAC address */
    uint8_t sw_mac[6]; /**< Software MAC address */
} ciot_ble_info_t;

/**
 * @brief Structure for CIOT BLE status.
 */
typedef struct __attribute__((packed))
{
    ciot_ble_state_t state; /**< State */
    int err_code; /**< Error code */
    ciot_ble_info_t info; /**< Information */
} ciot_ble_status_t;

/**
 * @brief Union for CIOT BLE request data.
 */
typedef union __attribute__((packed))
{
    uint8_t set_mac[6]; /**< Set MAC data */
} ciot_ble_req_data_u;

/**
 * @brief Structure for CIOT BLE request.
 */
typedef struct __attribute__((packed))
{
    ciot_ble_req_type_t type; /**< Request type */
    ciot_ble_req_data_u data; /**< Request data */
} ciot_ble_req_t;

/**
 * @brief Union for CIOT BLE data.
 */
typedef union __attribute__((packed))
{
    ciot_ble_cfg_t config; /**< Configuration */
    ciot_ble_status_t status; /**< Status */
    ciot_ble_req_t request; /**< Request */
} ciot_ble_data_u;

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_BLE_TYPES__H__

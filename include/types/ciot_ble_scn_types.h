/**
 * @file ciot_ble_scn_types.h
 * @ingroup hardware_types
 * @brief Defines data types and structures for CIOT BLE SCN.
 * @version 0.1
 * @date 2023-10-23
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_BLE_SCN_TYPES__H__
#define __CIOT_BLE_SCN_TYPES__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

/**
 * @brief Enumeration for CIOT BLE SCN states.
 */
typedef enum __attribute__((packed))
{
    CIOT_BLE_SCN_STATE_IDLE, /**< Idle state */
    CIOT_BLE_SCN_STATE_PASSIVE, /**< Passive state */
    CIOT_BLE_SCN_STATE_ACTIVE, /**< Active state */
} ciot_ble_scn_state_t;

/**
 * @brief Enumeration for CIOT BLE SCN request types.
 */
typedef enum __attribute__((packed))
{
    CIOT_BLE_SCN_REQ_UNKNOWN, /**< Unknown request type */
} ciot_ble_scn_req_type_t;

/**
 * @brief Structure for CIOT BLE SCN configuration.
 */
typedef struct __attribute__((packed))
{
    uint16_t interval; /**< Interval value */
    uint16_t window; /**< Window value */
    uint16_t timeout; /**< Timeout value */
    uint8_t active : 1; /**< Active flag */
    uint8_t brigde_mode : 1; /**< Bridge mode flag */
    uint8_t reserved : 6; /**< Reserved bits */
} ciot_ble_scn_cfg_t;

/**
 * @brief Structure for CIOT BLE SCN advertising information.
 */
typedef struct __attribute__((packed))
{
    uint8_t mac[6]; /**< MAC address */
    int8_t rssi; /**< RSSI value */
} ciot_ble_scn_adv_info_t;

/**
 * @brief Structure for CIOT BLE SCN status.
 */
typedef struct __attribute__((packed))
{
    ciot_ble_scn_state_t state; /**< State */
    ciot_ble_scn_adv_info_t adv_info; /**< Advertising information */
    int err_code; /**< Error code */
} ciot_ble_scn_status_t;

/**
 * @brief Union for CIOT BLE SCN request data.
 */
typedef union __attribute__((packed))
{
} ciot_ble_scn_req_data_u;

/**
 * @brief Structure for CIOT BLE SCN request.
 */
typedef struct __attribute__((packed))
{
    ciot_ble_scn_req_type_t type; /**< Request type */
    ciot_ble_scn_req_data_u data; /**< Request data */
} ciot_ble_scn_req_t;

/**
 * @brief Union for CIOT BLE SCN data.
 */
typedef union __attribute__((packed))
{
    ciot_ble_scn_cfg_t config; /**< Configuration */
    ciot_ble_scn_status_t status; /**< Status */
    ciot_ble_scn_req_t request; /**< Request */
} ciot_ble_scn_data_u;

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_BLE_SCN_TYPES__H__

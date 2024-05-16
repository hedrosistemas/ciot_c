/**
 * @file ciot_wifi_types.h
 * @ingroup hardware_types
 * @brief Defines data structures and types for CIOT WiFi functionality.
 * @version 0.1
 * @date 2023-10-18
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_WIFI_DATA__H__
#define __CIOT_WIFI_DATA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

#include "ciot_tcp_types.h"

/**
 * @brief Enumeration for CIOT WiFi interface types.
 */
typedef enum __attribute__((packed))
{
    CIOT_WIFI_IF_STA, /**< WiFi interface in station mode */
    CIOT_WIFI_IF_AP, /**< WiFi interface in access point mode */
} ciot_wifi_type_t;

/**
 * @brief Enumeration for CIOT WiFi scan states.
 */
typedef enum __attribute__((packed))
{
    CIOT_WIFI_SCAN_STATE_ERROR = -1, /**< WiFi scan error state */
    CIOT_WIFI_SCAN_STATE_IDLE, /**< WiFi scan idle state */
    CIOT_WIFI_SCAN_STATE_SCANNING, /**< WiFi scan in progress */
    CIOT_WIFI_SCAN_STATE_SCANNED, /**< WiFi scan completed */
} ciot_wifi_scan_state_t;

/**
 * @brief Enumeration for CIOT WiFi states.
 */
typedef enum __attribute__((packed))
{
    CIOT_WIFI_STATE_IDLE, /**< WiFi idle state */
} ciot_wifi_state_t;

/**
 * @brief Enumeration for CIOT WiFi request types.
 */
typedef enum __attribute__((packed))
{
    CIOT_WIFI_REQ_UNKNOWN, /**< Unknown WiFi request type */
    CIOT_WIFI_REQ_SCAN, /**< WiFi scan request */
} ciot_wifi_req_type_t;

/**
 * @brief Structure for CIOT WiFi access point information.
 */
typedef struct __attribute__((packed))
{
    uint8_t bssid[6]; /**< BSSID */
    char ssid[33]; /**< SSID */
    int8_t rssi; /**< RSSI */
    uint8_t authmode; /**< Authentication mode */
} ciot_wifi_ap_info_t;

/**
 * @brief Structure for CIOT WiFi configuration.
 */
typedef struct __attribute__((packed))
{
    char ssid[32]; /**< SSID */
    char password[64]; /**< Password */
    ciot_wifi_type_t type; /**< WiFi interface type */
    ciot_tcp_cfg_t tcp; /**< TCP configuration */
} ciot_wifi_cfg_t;

/**
 * @brief Structure for CIOT WiFi status.
 */
typedef struct __attribute__((packed))
{
    uint8_t disconnect_reason; /**< Disconnect reason */
    ciot_wifi_ap_info_t info; /**< Access point information */
    ciot_tcp_status_t tcp; /**< TCP status */
} ciot_wifi_status_t;

/**
 * @brief Structure for CIOT WiFi scan result.
 */
typedef struct __attribute__((packed))
{
    uint8_t count; /**< Number of access points */
    ciot_wifi_ap_info_t ap_list[8]; /**< Access point list */
} ciot_wifi_scan_result_t;

/**
 * @brief Union for CIOT WiFi request data.
 */
typedef union __attribute__((packed))
{
    ciot_wifi_scan_result_t scan_result; /**< WiFi scan result */
} ciot_wifi_req_data_u;

/**
 * @brief Structure for CIOT WiFi request.
 */
typedef struct __attribute__((packed))
{
    ciot_wifi_req_type_t type; /**< Request type */
    ciot_wifi_req_data_u data; /**< Request data */
} ciot_wifi_req_t;

/**
 * @brief Union for CIOT WiFi data.
 */
typedef union __attribute__((packed))
{
    ciot_wifi_cfg_t config; /**< Configuration data */
    ciot_wifi_status_t status; /**< Status data */
    ciot_wifi_req_t request; /**< Request data */
} ciot_wifi_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_WIFI_DATA__H__

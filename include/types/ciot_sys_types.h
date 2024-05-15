/**
 * @file ciot_sys_types.h
 * @ingroup software_types
 * @brief Defines data types and structures for CIOT system functionality.
 * @version 0.1
 * @date 2023-10-09
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_SYS_DATA__H__
#define __CIOT_SYS_DATA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

/**
 * @brief Enumeration for CIOT system request types.
 */
typedef enum __attribute__((packed))
{
    CIOT_SYS_REQ_UNKNONW, /**< Unknown system request type */
    CIOT_SYS_REQ_RESTART, /**< System restart request */
    CIOT_SYS_REQ_INIT_DFU, /**< Initialize DFU (Device Firmware Update) request */
} ciot_sys_req_type_t;

/**
 * @brief Enumeration for CIOT system hardware types.
 */
typedef enum __attribute__((packed))
{
    CIOT_SYS_HW_UNKNOWN, /**< Unknown hardware type */
    CIOT_SYS_HW_ESP8266, /**< ESP8266 hardware type */
    CIOT_SYS_HW_ARDUINO, /**< Arduino hardware type */
    CIOT_SYS_HW_ESP32, /**< ESP32 hardware type */
    CIOT_SYS_HW_NRF51, /**< NRF51 hardware type */
    CIOT_SYS_HW_NRF52, /**< NRF52 hardware type */
    CIOT_SYS_HW_LINUX, /**< Linux hardware type */
    CIOT_SYS_HW_WIN32, /**< Windows 32-bit hardware type */
} ciot_sys_hw_t;

/**
 * @brief Structure for CIOT system hardware features.
 */
typedef struct __attribute__((packed))
{
    uint16_t storage : 1; /**< Storage feature */
    uint16_t system : 1; /**< System feature */
    uint16_t uart : 1; /**< UART feature */
    uint16_t usb : 1; /**< USB feature */
    uint16_t ethernet : 1; /**< Ethernet feature */
    uint16_t wifi : 1; /**< WiFi feature */
    uint16_t ble_scn : 1; /**< BLE SCN (Serial Control) feature */
    uint16_t gpio : 1; /**< GPIO feature */
    uint16_t reserved : 8; /**< Reserved bits */
} ciot_sys_hw_features_t;

/**
 * @brief Structure for CIOT system software features.
 */
typedef struct __attribute__((packed))
{
    uint16_t ntp : 1; /**< NTP (Network Time Protocol) feature */
    uint16_t ota : 1; /**< OTA (Over-The-Air) update feature */
    uint16_t dfu : 1; /**< DFU (Device Firmware Update) feature */
    uint16_t http_client : 1; /**< HTTP client feature */
    uint16_t http_server : 1; /**< HTTP server feature */
    uint16_t mqtt_client : 1; /**< MQTT client feature */
    uint16_t timer : 1; /**< Timer feature */
    uint16_t serializer : 1; /**< Serializer feature */
    uint16_t reserved : 8; /**< Reserved bits */
} ciot_sys_sw_features_t;

/**
 * @brief Structure for CIOT system features combining hardware and software features.
 */
typedef struct __attribute__((packed))
{
    ciot_sys_hw_features_t hw; /**< Hardware features */
    ciot_sys_sw_features_t sw; /**< Software features */
} ciot_sys_features_t;

/**
 * @brief Structure for CIOT system information.
 */
typedef struct __attribute__((packed))
{
    char hw_name[16]; /**< Hardware name */
    uint8_t app_ver[3]; /**< Application version */
    ciot_sys_hw_t hardware; /**< Hardware type */
    ciot_sys_features_t features; /**< System features */
} ciot_sys_info_t;

/**
 * @brief Structure for CIOT system status.
 */
typedef struct __attribute__((packed))
{
    uint8_t rst_reason; /**< Restart reason */
    uint8_t rst_count; /**< Restart count */
    uint32_t free_memory; /**< Free memory */
    uint32_t lifetime; /**< System lifetime */
    ciot_sys_info_t info; /**< System information */
} ciot_sys_status_t;

/**
 * @brief Structure for CIOT system configuration.
 */
typedef struct __attribute__((packed))
{

} ciot_sys_cfg_t;

/**
 * @brief Union for CIOT system request data.
 */
typedef union __attribute__((packed))
{

} ciot_sys_req_data_u;

/**
 * @brief Structure for CIOT system request.
 */
typedef struct __attribute__((packed))
{
    ciot_sys_req_type_t type; /**< Request type */
    ciot_sys_req_data_u data; /**< Request data */
} ciot_sys_req_t;

/**
 * @brief Union for CIOT system data.
 */
typedef union __attribute__((packed))
{
    ciot_sys_cfg_t config; /**< System configuration */
    ciot_sys_status_t status; /**< System status */
    ciot_sys_req_t request; /**< System request */
} ciot_sys_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_SYS_DATA__H__

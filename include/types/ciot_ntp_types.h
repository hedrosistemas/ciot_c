/**
 * @file ciot_ntp_types.h
 * @ingroup software_types
 * @brief Defines data types and structures for CIOT NTP functionality.
 * @version 0.1
 * @date 2023-10-18
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_NTP_DATA__H__
#define __CIOT_NTP_DATA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <time.h>

#include "ciot_config.h"

#ifndef CIOT_CONFIG_NTP_SERVERS_COUNT
#define CIOT_CONFIG_NTP_SERVERS_COUNT 0
#endif

/**
 * @brief Enumeration for CIOT NTP state.
 */
typedef enum __attribute__((packed))
{
    HG_NTP_STATE_RESET, /**< NTP state: reset */
    HG_NTP_STATE_COMPLETED, /**< NTP state: completed */
    HG_NTP_STATE_IN_PROGRESS, /**< NTP state: in progress */
} ciot_ntp_state_t;

/**
 * @brief Enumeration for CIOT NTP request type.
 */
typedef enum __attribute__((packed))
{
    CIOT_NTP_REQ_UNKNOWN, /**< Unknown NTP request type */
} ciot_ntp_req_type_t;

/**
 * @brief Structure for CIOT NTP configuration.
 */
typedef struct __attribute__((packed))
{
    uint8_t op_mode; /**< Operation mode */
    uint8_t sync_mode; /**< Sync mode */
    uint32_t sync_interval; /**< Sync interval */
    char timezone[16]; /**< Timezone */
    char server[CIOT_CONFIG_NTP_SERVERS_COUNT][64]; /**< NTP servers */
} ciot_ntp_cfg_t;

/**
 * @brief Structure for CIOT NTP status.
 */
typedef struct __attribute__((packed))
{
    ciot_ntp_state_t state; /**< NTP state */
    uint64_t last_sync; /**< Last synchronization timestamp */
    uint16_t sync_count; /**< Synchronization count */
    uint8_t init : 1; /**< Initialization flag */
    uint8_t sync : 1; /**< Sync flag */
    uint8_t reserve : 6; /**< Reserved bits */
} ciot_ntp_status_t;

/**
 * @brief Union for CIOT NTP request data.
 */
typedef union __attribute__((packed))
{
    /* No specific request data defined */
} ciot_ntp_req_data_u;

/**
 * @brief Structure for CIOT NTP request.
 */
typedef struct __attribute__((packed))
{
    ciot_ntp_req_type_t type; /**< Request type */
    ciot_ntp_req_data_u data; /**< Request data */
} ciot_ntp_req_t;

/**
 * @brief Union for CIOT NTP data.
 */
typedef union __attribute__((packed))
{
    ciot_ntp_cfg_t config; /**< NTP configuration */
    ciot_ntp_status_t status; /**< NTP status */
    ciot_ntp_req_t request; /**< NTP request */
} ciot_ntp_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_NTP_DATA__H__

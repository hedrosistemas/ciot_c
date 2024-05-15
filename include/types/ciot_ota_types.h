/**
 * @file ciot_ota_types.h
 * @ingroup software_types
 * @brief Defines data types and structures for CIOT Over-The-Air (OTA) functionality.
 * @version 0.1
 * @date 2023-10-18
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_OTA_DATA__H__
#define __CIOT_OTA_DATA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stddef.h>

/**
 * @brief Enumeration for CIOT OTA state.
 */
typedef enum __attribute__((packed))
{
    CIOT_OTA_STATE_ERROR = -1, /**< OTA state: error */
    CIOT_OTA_STATE_IDLE, /**< OTA state: idle */
    CIOT_OTA_STATE_INIT, /**< OTA state: initialization */
    CIOT_OTA_STATE_IN_PROGRESS, /**< OTA state: in progress */
    CIOT_OTA_STATE_START, /**< OTA state: start */
    CIOT_OTA_STATE_CONNECTED, /**< OTA state: connected */
    CIOT_OTA_STATE_CHECKING_DATA, /**< OTA state: checking data */
    CIOT_OTA_STATE_DECRYPTING, /**< OTA state: decrypting */
    CIOT_OTA_STATE_FLASHING, /**< OTA state: flashing */
    CIOT_OTA_STATE_UPDATE_BOOT_PARTITION, /**< OTA state: updating boot partition */
    CIOT_OTA_STATE_DONE, /**< OTA state: done */
} ciot_ota_state_t;

/**
 * @brief Enumeration for CIOT OTA request type.
 */
typedef enum __attribute__((packed))
{
    CIOT_OTA_REQ_UNKNOWN, /**< Unknown OTA request type */
    CIOT_OTA_REQ_ROLLBACK, /**< Rollback request */
} ciot_ota_req_type_t;

/**
 * @brief Structure for CIOT OTA configuration.
 */
typedef struct __attribute__((packed))
{
    char url[128]; /**< URL for OTA update */
    uint8_t force :1; /**< Flag for forcing update */
    uint8_t encrypted :1; /**< Flag for encrypted update */
    uint8_t restart :1; /**< Flag for restarting after update */
    uint8_t reserved :5; /**< Reserved bits */
} ciot_ota_cfg_t;

/**
 * @brief Structure for CIOT OTA status.
 */
typedef struct __attribute__((packed))
{
    ciot_ota_state_t state; /**< OTA state */
    int error; /**< Error code */
    uint32_t image_size; /**< Size of the image */
    uint32_t image_read; /**< Number of bytes read */
} ciot_ota_status_t;

/**
 * @brief Union for CIOT OTA request data.
 */
typedef union __attribute__((packed))
{
    /* No specific request data defined */
} ciot_ota_req_data_u;

/**
 * @brief Structure for CIOT OTA request.
 */
typedef struct __attribute__((packed))
{
    ciot_ota_req_type_t type; /**< Request type */
    ciot_ota_req_data_u data; /**< Request data */
} ciot_ota_req_t;

/**
 * @brief Union for CIOT OTA data.
 */
typedef union __attribute__((packed))
{
    ciot_ota_cfg_t config; /**< OTA configuration */
    ciot_ota_status_t status; /**< OTA status */
    ciot_ota_req_t request; /**< OTA request */
} ciot_ota_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_OTA_DATA__H__

/**
 * @file ciot_storage_types.h
 * @ingroup hardware_types
 * @brief Defines data types and structures for CIOT storage functionality.
 * @version 0.1
 * @date 2023-10-10
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @copyright Copyright (c) 2023
 */

#ifndef __CIOT_STORAGE_DATA__H__
#define __CIOT_STORAGE_DATA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

/**
 * @brief Enumeration for CIOT storage types.
 */
typedef enum __attribute__((packed))
{
    CIOT_STORAGE_TYPE_UNKNOWN, /**< Unknown storage type */
    CIOT_STORAGE_TYPE_EEPROM, /**< EEPROM storage type */
    CIOT_STORAGE_TYPE_FLASH, /**< Flash storage type */
    CIOT_STORAGE_TYPE_FS, /**< Filesystem storage type */
} ciot_storage_type_t;

/**
 * @brief Enumeration for CIOT storage state.
 */
typedef enum __attribute__((packed))
{
    CIOT_STORAGE_STATE_IDLE, /**< Storage state: idle */
} ciot_storage_state_t;

/**
 * @brief Enumeration for CIOT storage request types.
 */
typedef enum __attribute__((packed))
{
    CIOT_STORAGE_REQ_UNKNOWN, /**< Unknown storage request type */
    CIOT_STORAGE_REQ_SAVE, /**< Save data request */
    CIOT_STORAGE_REQ_LOAD, /**< Load data request */
    CIOT_STORAGE_REQ_DELETE, /**< Delete data request */
    CIOT_STORAGE_REQ_FORMAT, /**< Format storage request */
} ciot_storage_req_type_t;

/**
 * @brief Structure for CIOT storage configuration.
 */
typedef struct __attribute__((packed))
{
    ciot_storage_type_t type; /**< Storage type */
} ciot_storage_cfg_t;

/**
 * @brief Structure for CIOT storage status.
 */
typedef struct __attribute__((packed))
{
    ciot_storage_state_t state; /**< Storage state */
} ciot_storage_status_t;

/**
 * @brief Structure for CIOT storage file data in a request.
 */
typedef struct __attribute__((packed))
{
    char path[16]; /**< File path */
    uint8_t size; /**< Data size */
    uint8_t data[255]; /**< Data content */
} ciot_storage_req_file_data_t;

/**
 * @brief Structure for CIOT storage request.
 */
typedef struct __attribute__((packed))
{
    ciot_storage_req_type_t type; /**< Request type */
    ciot_storage_req_file_data_t data; /**< Request data */
} ciot_storage_req_t;

/**
 * @brief Union for CIOT storage data.
 */
typedef union __attribute__((packed))
{
    ciot_storage_cfg_t config; /**< Storage configuration */
    ciot_storage_status_t status; /**< Storage status */
    ciot_storage_req_t request; /**< Storage request */
} ciot_storage_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_STORAGE_DATA__H__

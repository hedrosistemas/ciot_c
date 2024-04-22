/**
 * @file ciot_storage_data.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __CIOT_STORAGE_DATA__H__
#define __CIOT_STORAGE_DATA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

typedef enum __attribute__((packed))
{
    CIOT_STORAGE_TYPE_UNKNOWN,
    CIOT_STORAGE_TYPE_EEPROM,
    CIOT_STORAGE_TYPE_FLASH,
    CIOT_STORAGE_TYPE_FS,
} ciot_storage_type_t;

typedef enum __attribute__((packed))
{
    CIOT_STORAGE_STATE_IDLE,
} ciot_storage_state_t;

typedef enum __attribute__((packed))
{
    CIOT_STORAGE_REQ_UNKNOWN,
    CIOT_STORAGE_REQ_SAVE,
    CIOT_STORAGE_REQ_LOAD,
    CIOT_STORAGE_REQ_DELETE,
    CIOT_STORAGE_REQ_FORMAT,
} ciot_storage_req_type_t;

typedef struct __attribute__((packed))
{
    ciot_storage_type_t type;
} ciot_storage_cfg_t;

typedef struct __attribute__((packed))
{
    ciot_storage_state_t state;
} ciot_storage_status_t;

typedef struct __attribute__((packed))
{
    char path[16];
    uint8_t size;
    uint8_t data[255];
} ciot_storage_req_file_data_t;

typedef struct __attribute__((packed))
{
    ciot_storage_req_type_t type;
    ciot_storage_req_file_data_t data;
} ciot_storage_req_t;

typedef union __attribute__((packed))
{
    ciot_storage_cfg_t config;
    ciot_storage_status_t status;
    ciot_storage_req_t request;
} ciot_storage_data_u;

#ifdef __cplusplus
}
#endif

#endif //!__CIOT_STORAGE_DATA__H__
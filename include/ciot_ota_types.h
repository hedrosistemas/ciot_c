/**
 * @file ciot_ota_data.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_OTA_DATA__H__
#define __CIOT_OTA_DATA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stddef.h>

#include "ciot_err.h"
#include "ciot_config.h"

typedef enum __attribute__((packed))
{
    CIOT_OTA_STATE_ERROR=-1,
    CIOT_OTA_STATE_IDLE,
    CIOT_OTA_STATE_INIT,
    CIOT_OTA_STATE_IN_PROGRESS,
    CIOT_OTA_STATE_START,
    CIOT_OTA_STATE_CONNECTED,
    CIOT_OTA_STATE_CHECKING_DATA,
    CIOT_OTA_STATE_DECRYPTING,
    CIOT_OTA_STATE_FLASHING,
    CIOT_OTA_STATE_UPDATE_BOOT_PARTITION,
    CIOT_OTA_STATE_DONE,
} ciot_ota_state_t;

typedef enum __attribute__((packed))
{
    CIOT_OTA_REQ_UNKNOWN,
} ciot_ota_req_type_t;

typedef struct __attribute__((packed))
{
    char url[128];
    uint8_t force :1;
    uint8_t encrypted :1;
    uint8_t restart :1;
    uint8_t reserverd :5;
} ciot_ota_cfg_t;

typedef struct __attribute__((packed))
{
    ciot_ota_state_t state;
    ciot_err_t error;
    size_t image_size;
    size_t image_read;
} ciot_ota_status_t;

typedef union __attribute__((packed))
{

} ciot_ota_req_data_u;

typedef struct __attribute__((packed))
{
    ciot_ota_req_type_t type;
    ciot_ota_req_data_u data;
} ciot_ota_req_t;

typedef union __attribute__((packed))
{
    #if CIOT_CONFIG_FEATURE_OTA
    ciot_ota_cfg_t config;
    ciot_ota_status_t status;
    ciot_ota_req_t request;
    #endif
} ciot_ota_data_u;

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_OTA_DATA__H__
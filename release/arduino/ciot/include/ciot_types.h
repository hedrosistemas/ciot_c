/**
 * @file ciot_types.h
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_TYPES__H__
#define __CIOT_TYPES__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include "ciot_err.h"

typedef enum __attribute__((packed))
{
    CIOT_STATE_IDLE,
    CIOT_STATE_BUSY,
    CIOT_STATE_ERROR,
} ciot_state_t;

typedef enum __attribute__((packed))
{
    CIOT_REQ_UNKNOWN,
    CIOT_REQ_SAVE_IFACE_CFG,
    CIOT_REQ_DELETE_IFACE_CFG,
    CIOT_REQ_PROXY_MSG,
} ciot_req_type_t;

// typedef struct __attribute__((packed))
// {

// } ciot_cfg_t;

typedef struct __attribute__((packed))
{
    ciot_state_t state;
} ciot_status_t;

typedef struct __attribute__((packed))
{
    uint8_t iface_id;
} ciot_req_save_iface_cfg_t;

typedef struct __attribute__((packed))
{
    uint8_t iface_id;
} ciot_req_delete_iface_cfg_t;

typedef struct __attribute((packed))
{
    uint8_t iface_id;
    ciot_err_t err;
} ciot_req_result_t;

typedef struct __attribute((packed))
{
    uint8_t data[CIOT_CONFIG_MESSAGE_PAYLOAD_LEN];
    uint16_t size;
} ciot_req_proxy_msg_t;

typedef union __attribute__((packed))
{
    ciot_req_save_iface_cfg_t save_iface_cfg;
    ciot_req_delete_iface_cfg_t delete_iface_cfg;
    ciot_req_proxy_msg_t proxy_msg;
    ciot_req_result_t result;
} ciot_req_data_u;

typedef struct __attribute__((packed))
{
    ciot_req_type_t id;
    ciot_req_data_u data;
} ciot_req_t;

typedef union __attribute__((packed))
{
    // ciot_cfg_t config;
    ciot_status_t status;
    ciot_req_t req;
} ciot_data_u;

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_TYPES__H__
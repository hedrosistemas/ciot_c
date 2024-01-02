/**
 * @file ciot_bridge_types.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_BRIDGE_TYPES__H__
#define __CIOT_BRIDGE_TYPES__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

#include "ciot_config.h"

typedef enum __attribute__((packed))
{
    CIOT_BRIDGE_STATE_IDLE,
    CIOT_BRIDGE_STATE_STARTED,
    CIOT_BRIDGE_STATE_ERROR,
} ciot_bridge_state_t;

typedef enum __attribute__((packed))
{
    CIOT_BRIDGE_REQ_UNKNOWN,
} ciot_bridge_req_type_t;

typedef struct __attribute__((packed))
{
    uint8_t ifaces_id[2];
} ciot_bridge_cfg_t;

typedef struct __attribute__((packed))
{
    ciot_bridge_state_t state;
} ciot_bridge_status_t;

typedef union __attribute__((packed))
{

} ciot_bridge_req_data_u;

typedef struct __attribute__((packed))
{
    ciot_bridge_req_type_t id;
    ciot_bridge_req_data_u data;
} ciot_bridge_req_t;

typedef union __attribute__((packed))
{
    #if CIOT_CONFIG_FEATURE_BRIDGE
    ciot_bridge_cfg_t config;
    ciot_bridge_status_t status;
    ciot_bridge_req_t request;
    #endif
} ciot_bridge_data_u;

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_BRIDGE_TYPES__H__
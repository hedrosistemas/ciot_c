/**
 * @file ciot_opcuas_types.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_OPCUAS_TYPES__H__
#define __CIOT_OPCUAS_TYPES__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

typedef enum __attribute__((packed))
{
    CIOT_OPCUAS_STATE_ERROR = -1,
    CIOT_OPCUAS_STATE_IDLE,
    CIOT_OPCUAS_STATE_RUNNING,
} ciot_opcuas_state_t;

typedef enum __attribute__((packed))
{
    CIOT_OPCUAS_REQ_UNKNOWN,
    CIOT_OPCUAS_REQ_ADD_NODE,
    CIOT_OPCUAS_REQ_RUN,
} ciot_opcuas_req_type_t;

typedef struct __attribute__((packed))
{
    uint32_t port;
} ciot_opcuas_cfg_t;

typedef struct __attribute__((packed))
{
    ciot_opcuas_state_t state;
} ciot_opcuas_status_t;

typedef struct __attribute__((packed))
{
    uint16_t type;
    char localization[8];
    char display_name[32];
    char node_id[64];
} ciot_opcuas_req_add_node_t;

typedef union __attribute__((packed))
{
    ciot_opcuas_req_add_node_t add_node;
} ciot_opcuas_req_data_u;

typedef struct __attribute__((packed))
{
    ciot_opcuas_req_type_t type;
    ciot_opcuas_req_data_u data;
} ciot_opcuas_req_t;

typedef union __attribute__((packed))
{
    ciot_opcuas_cfg_t config;
    ciot_opcuas_status_t status;
    ciot_opcuas_req_t request;
} ciot_opcuas_data_u;

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_OPCUAS_TYPES__H__

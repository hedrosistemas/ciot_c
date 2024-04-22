/**
 * @file ciot_bridge.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_BRIDGE__H__
#define __CIOT_BRIDGE__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_bridge_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

#define CIOT_BRIDGE_NULL_TARGET -1

typedef struct ciot_bridge *ciot_bridge_t;

typedef struct __attribute__((packed))
{
    ciot_msg_header_t header;
    ciot_bridge_status_t status;
} ciot_bridge_status_msg_t;

ciot_bridge_t ciot_bridge_new(void *handle);

ciot_err_t ciot_bridge_start(ciot_bridge_t self, ciot_bridge_cfg_t *cfg);
ciot_err_t ciot_bridge_stop(ciot_bridge_t self);
ciot_err_t ciot_bridge_process_req(ciot_bridge_t self, ciot_bridge_req_t *req);
ciot_err_t ciot_bridge_send_data(ciot_bridge_t self, uint8_t *data, int size);

int ciot_bridge_get_target_id(ciot_bridge_t self, uint8_t sender_id);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_BRIDGE__H__
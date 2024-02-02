/**
 * @file ciot_httpc.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_HTTPC__H__
#define __CIOT_HTTPC__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_httpc_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

typedef struct ciot_httpc *ciot_httpc_t;

typedef enum ciot_httpc_event_id
{
    CIOT_HTTPC_EVENT_CONNECTING = CIOT_IFACE_EVENT_CUSTOM,
    CIOT_HTTPC_EVENT_CONNECTED,
} ciot_httpc_event_id_t;

typedef struct __attribute__((packed))
{
    ciot_msg_header_t header;
    ciot_httpc_status_t status;
} ciot_httpc_status_msg_t;

ciot_httpc_t ciot_httpc_new(void *handle);
ciot_err_t ciot_httpc_start(ciot_httpc_t self, ciot_httpc_cfg_t *cfg);
ciot_err_t ciot_httpc_stop(ciot_httpc_t self);
ciot_err_t ciot_httpc_process_req(ciot_httpc_t self, ciot_httpc_req_t *req);
ciot_err_t ciot_httpc_send_data(ciot_httpc_t self, uint8_t *data, int size);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_HTTPC__H__
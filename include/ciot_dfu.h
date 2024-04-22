/**
 * @file ciot_dfu.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_DFU__H__
#define __CIOT_DFU__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_dfu_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

typedef struct ciot_dfu *ciot_dfu_t;

typedef enum ciot_dfu_event_id
{
    CIOT_DFU_EVENT_STATE_CHANGED = CIOT_IFACE_EVENT_CUSTOM,
} ciot_dfu_event_id_t;

typedef struct __attribute__((packed))
{
    ciot_msg_header_t header;
    ciot_dfu_status_t status;
} ciot_dfu_status_msg_t;

ciot_dfu_t ciot_dfu_new(void *handle);
ciot_err_t ciot_dfu_start(ciot_dfu_t self, ciot_dfu_cfg_t *cfg);
ciot_err_t ciot_dfu_stop(ciot_dfu_t self);
ciot_err_t ciot_dfu_process_req(ciot_dfu_t self, ciot_dfu_req_t *req);
ciot_err_t ciot_dfu_send_data(ciot_dfu_t self, uint8_t *data, int size);

ciot_err_t ciot_dfu_task(ciot_dfu_t self);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_DFU__H__

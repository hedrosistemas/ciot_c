/**
 * @file ciot_sys.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_SYS__H__
#define __CIOT_SYS__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_sys_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

#define CIOT_SYS_EVT_BIT_POOLING 0x00000001

typedef struct ciot_sys *ciot_sys_t;

typedef struct __attribute__((packed))
{
    ciot_msg_header_t header;
    ciot_sys_status_t status;
} ciot_sys_status_msg_t;

ciot_sys_t ciot_sys_new(void *handle);
ciot_err_t ciot_sys_start(ciot_sys_t self, ciot_sys_cfg_t *cfg);
ciot_err_t ciot_sys_stop(ciot_sys_t self);
ciot_err_t ciot_sys_process_req(ciot_sys_t self, ciot_sys_req_t *req);
ciot_err_t ciot_sys_send_data(ciot_sys_t self, uint8_t *data, int size);
ciot_err_t ciot_sys_rst(ciot_sys_t self);

ciot_err_t ciot_sys_task(ciot_sys_t self);
ciot_err_t ciot_sys_set_event_bits(ciot_sys_t self, int event_bits);
void ciot_sys_sleep(long ms);

// common
ciot_err_t ciot_sys_update_features(ciot_sys_features_t *features);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_SYS__H__
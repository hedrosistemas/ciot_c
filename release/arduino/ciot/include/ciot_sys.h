/**
 * @file ciot_sys.h
 * @author Wesley Santos (wesleypro37@gmail.com)
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

#include "ciot_sys_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

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

ciot_err_t ciot_sys_task(ciot_sys_t self);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_SYS__H__
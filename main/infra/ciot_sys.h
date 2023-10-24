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

#include "ciot_sys_data.h"
#include "ciot_iface.h"
#include "ciot_err.h"

typedef struct ciot_iface *ciot_sys_t;

void ciot_sys_init(void);
ciot_sys_t ciot_sys_new(void *handle);
ciot_err_t ciot_sys_start(ciot_sys_t this, ciot_sys_cfg_t *cfg);
ciot_err_t ciot_sys_stop(ciot_sys_t this);
ciot_err_t ciot_sys_process_req(ciot_sys_t this, ciot_sys_req_t *req);
ciot_err_t ciot_sys_send_data(ciot_sys_t this, uint8_t *data, int size);

#endif  //!__CIOT_SYS__H__
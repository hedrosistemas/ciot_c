/**
 * @file ciot_mbus_server.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-02-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __CIOT_MBUS_SERVER__H__
#define __CIOT_MBUS_SERVER__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_config.h"
#include "ciot_types.h"
#include "ciot_iface.h"

typedef struct ciot_mbus_server *ciot_mbus_server_t;

typedef struct ciot_mbus_server_base
{
    ciot_iface_t iface;
    ciot_mbus_server_cfg_t cfg;
    ciot_mbus_server_status_t status;
} ciot_mbus_server_base_t;

ciot_mbus_server_t ciot_mbus_server_new(void *handle);
ciot_err_t ciot_mbus_server_init(ciot_mbus_server_t self);
ciot_err_t ciot_mbus_server_start(ciot_mbus_server_t self, ciot_mbus_server_cfg_t *cfg);
ciot_err_t ciot_mbus_server_stop(ciot_mbus_server_t self);
ciot_err_t ciot_mbus_server_process_req(ciot_mbus_server_t self, ciot_mbus_server_req_t *req);
ciot_err_t ciot_mbus_server_get_cfg(ciot_mbus_server_t self, ciot_mbus_server_cfg_t *cfg);
ciot_err_t ciot_mbus_server_get_status(ciot_mbus_server_t self, ciot_mbus_server_status_t *status);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_MBUS_SERVER__H__
/**
 * @file ciot_viface.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_VIFACE__H__
#define __CIOT_VIFACE__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_err.h"
#include "ciot_iface.h"

typedef struct ciot_viface *ciot_viface_t;
typedef struct {} ciot_viface_cfg_t;
typedef struct {} ciot_viface_req_t;
typedef struct {} ciot_viface_status_t;
typedef struct {} ciot_viface_info_t;

typedef struct {
    ciot_viface_cfg_t *config;
    ciot_viface_req_t *request;
    ciot_viface_status_t *status;
    ciot_viface_info_t *info;
} ciot_viface_data_t;

typedef struct ciot_viface_base
{
    ciot_iface_t iface;
    ciot_viface_cfg_t cfg;
    ciot_viface_status_t status;
    ciot_viface_info_t info;
    ciot_viface_req_t req;
    ciot_viface_data_t data;
} ciot_viface_base_t;

ciot_viface_t ciot_viface_new(void *handle, ciot_iface_type_t type);
ciot_err_t ciot_viface_init(ciot_viface_t self, ciot_iface_type_t type);
ciot_err_t ciot_viface_start(ciot_viface_t self, ciot_viface_cfg_t *cfg);
ciot_err_t ciot_viface_stop(ciot_viface_t self);
ciot_err_t ciot_viface_process_req(ciot_viface_t self, ciot_viface_req_t *req);
ciot_err_t ciot_viface_get_cfg(ciot_viface_t self, ciot_viface_cfg_t *cfg);
ciot_err_t ciot_viface_get_status(ciot_viface_t self, ciot_viface_status_t *status);
ciot_err_t ciot_viface_get_info(ciot_viface_t self, ciot_viface_info_t *info);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_VIFACE__H__
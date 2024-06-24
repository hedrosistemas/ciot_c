/**
 * @file ciot_model.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_model__H__
#define __CIOT_model__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_err.h"
#include "ciot_iface.h"

#include "ciot/proto/v1/model.pb-c.h"

typedef struct ciot_model *ciot_model_t;
typedef Ciot__ModelCfg ciot_model_cfg_t;
typedef Ciot__ModelReq ciot_model_req_t;
typedef Ciot__ModelStatus ciot_model_status_t;
typedef Ciot__ModelInfo ciot_model_info_t;
typedef Ciot__ModelReq ciot_model_req_t;
typedef Ciot__ModelData ciot_model_data_t;

typedef struct ciot_model_base
{
    ciot_iface_t iface;
    ciot_model_cfg_t cfg;
    ciot_model_status_t status;
    ciot_model_info_t info;
    ciot_model_req_t req;
    ciot_model_data_t data;
} ciot_model_base_t;

ciot_model_t ciot_model_new(void *handle);
ciot_err_t ciot_model_init(ciot_model_t self);
ciot_err_t ciot_model_start(ciot_model_t self, ciot_model_cfg_t *cfg);
ciot_err_t ciot_model_stop(ciot_model_t self);
ciot_err_t ciot_model_process_req(ciot_model_t self, ciot_model_req_t *req);
ciot_err_t ciot_model_get_cfg(ciot_model_t self, ciot_model_cfg_t *cfg);
ciot_err_t ciot_model_get_status(ciot_model_t self, ciot_model_status_t *status);
ciot_err_t ciot_model_get_info(ciot_model_t self, ciot_model_info_t *info);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_model__H__

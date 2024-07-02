/**
 * @file ciot_storage.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_STORAGE__H__
#define __CIOT_STORAGE__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_err.h"
#include "ciot_iface.h"

#include "ciot/proto/v1/storage.pb-c.h"

typedef struct ciot_storage *ciot_storage_t;
typedef Ciot__StorageCfg ciot_storage_cfg_t;
typedef Ciot__StorageReq ciot_storage_req_t;
typedef Ciot__StorageStatus ciot_storage_status_t;
typedef Ciot__StorageInfo ciot_storage_info_t;
typedef Ciot__StorageReq ciot_storage_req_t;
typedef Ciot__StorageData ciot_storage_data_t;

typedef struct ciot_storage_base
{
    ciot_iface_t iface;
    ciot_storage_cfg_t cfg;
    ciot_storage_status_t status;
    ciot_storage_info_t info;
    ciot_storage_req_t req;
    ciot_storage_data_t data;
} ciot_storage_base_t;

ciot_storage_t ciot_storage_new(void *handle);
ciot_err_t ciot_storage_init(ciot_storage_t self);
ciot_err_t ciot_storage_start(ciot_storage_t self, ciot_storage_cfg_t *cfg);
ciot_err_t ciot_storage_stop(ciot_storage_t self);
ciot_err_t ciot_storage_process_req(ciot_storage_t self, ciot_storage_req_t *req);
ciot_err_t ciot_storage_get_cfg(ciot_storage_t self, ciot_storage_cfg_t *cfg);
ciot_err_t ciot_storage_get_status(ciot_storage_t self, ciot_storage_status_t *status);
ciot_err_t ciot_storage_get_info(ciot_storage_t self, ciot_storage_info_t *info);

ciot_err_t ciot_storage_save(ciot_storage_t self, char *path, uint8_t *data, int size);
ciot_err_t ciot_storage_load(ciot_storage_t self, char *path, uint8_t *data, int size);
ciot_err_t ciot_storage_delete(ciot_storage_t self, char *path);
ciot_err_t ciot_storage_format(ciot_storage_t self);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_STORAGE__H__

/**
 * @file ciot_ota.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_ota__H__
#define __CIOT_ota__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_err.h"
#include "ciot_iface.h"

#include "ciot/proto/v1/ota.pb-c.h"

#ifndef CIOT_CONFIG_OTA_URL_LEN
#define CIOT_CONFIG_OTA_URL_LEN 64
#endif
#ifndef CIOT_CONFIG_OTA_BUF_SIZE
#define CIOT_CONFIG_OTA_BUF_SIZE 1024
#endif
#ifndef CIOT_CONFIG_OTA_TASK_STACK_SIZE
#define CIOT_CONFIG_OTA_TASK_STACK_SIZE 8192
#endif
#ifndef CIOT_CONFIG_OTA_TASK_PRIORITY
#define CIOT_CONFIG_OTA_TASK_PRIORITY (tskIDLE_PRIORITY + 4)
#endif
#ifndef CIOT_CONFIG_OTA_TASK_CORE_ID
#define CIOT_CONFIG_OTA_TASK_CORE_ID 1
#endif

typedef struct ciot_ota *ciot_ota_t;
typedef Ciot__OtaCfg ciot_ota_cfg_t;
typedef Ciot__OtaReq ciot_ota_req_t;
typedef Ciot__OtaStatus ciot_ota_status_t;
// typedef Ciot__OtaInfo ciot_ota_info_t;
typedef Ciot__OtaReq ciot_ota_req_t;
typedef Ciot__OtaData ciot_ota_data_t;

typedef struct ciot_ota_base
{
    ciot_iface_t iface;
    ciot_ota_cfg_t cfg;
    ciot_ota_status_t status;
    // ciot_ota_info_t info;
    ciot_ota_req_t req;
    ciot_ota_data_t data;
    char url[CIOT_CONFIG_OTA_URL_LEN];
} ciot_ota_base_t;

ciot_ota_t ciot_ota_new(void *handle);
ciot_err_t ciot_ota_init(ciot_ota_t self);
ciot_err_t ciot_ota_start(ciot_ota_t self, ciot_ota_cfg_t *cfg);
ciot_err_t ciot_ota_stop(ciot_ota_t self);
ciot_err_t ciot_ota_rollback(ciot_ota_t self);
ciot_err_t ciot_ota_process_req(ciot_ota_t self, ciot_ota_req_t *req);
ciot_err_t ciot_ota_get_cfg(ciot_ota_t self, ciot_ota_cfg_t *cfg);
ciot_err_t ciot_ota_get_status(ciot_ota_t self, ciot_ota_status_t *status);
// ciot_err_t ciot_ota_get_info(ciot_ota_t self, ciot_ota_info_t *info);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_ota__H__

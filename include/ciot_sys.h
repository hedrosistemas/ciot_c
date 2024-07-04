/**
 * @file ciot_sys.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_SYS__H__
#define __CIOT_SYS__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_err.h"
#include "ciot_iface.h"

#include "ciot/proto/v1/sys.pb-c.h"

#ifndef CIOT_CONFIG_MG_POOL_INTERVAL_MS
#define CIOT_CONFIG_MG_POOL_INTERVAL_MS 10
#endif

typedef struct ciot_sys *ciot_sys_t;
typedef Ciot__SysCfg ciot_sys_cfg_t;
typedef Ciot__SysReq ciot_sys_req_t;
typedef Ciot__SysStatus ciot_sys_status_t;
typedef Ciot__SysInfo ciot_sys_info_t;
typedef Ciot__SysHw ciot_sys_hw_t;
typedef Ciot__SysHwFeatures ciot_sys_hw_features_t;
typedef Ciot__SysSwFeatures ciot_sys_sw_features_t;
typedef Ciot__SysFeatures ciot_sys_features_t;
typedef Ciot__SysReq ciot_sys_req_t;
typedef Ciot__SysData ciot_sys_data_t;

typedef struct ciot_sys_base
{
    ciot_iface_t iface;
    ciot_sys_cfg_t cfg;
    ciot_sys_status_t status;
    ciot_sys_info_t info;
    ciot_sys_data_t data;
    ciot_sys_features_t features;
    ciot_sys_hw_features_t hw;
    ciot_sys_sw_features_t sw;
} ciot_sys_base_t;

ciot_sys_t ciot_sys_new(void *handle);
ciot_err_t ciot_sys_init(ciot_sys_t self);
ciot_err_t ciot_sys_start(ciot_sys_t self, ciot_sys_cfg_t *cfg);
ciot_err_t ciot_sys_stop(ciot_sys_t self);
ciot_err_t ciot_sys_process_req(ciot_sys_t self, ciot_sys_req_t *req);
ciot_err_t ciot_sys_get_cfg(ciot_sys_t self, ciot_sys_cfg_t *cfg);
ciot_err_t ciot_sys_get_status(ciot_sys_t self, ciot_sys_status_t *status);
ciot_err_t ciot_sys_get_info(ciot_sys_t self, ciot_sys_info_t *info);
ciot_err_t ciot_sys_task(ciot_sys_t self);
ciot_err_t ciot_sys_set_event_bits(ciot_sys_t self, int event_bits);
ciot_err_t ciot_sys_sleep(long ms);
ciot_err_t ciot_sys_restart(void);
ciot_err_t ciot_sys_init_dfu(void);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_SYS__H__

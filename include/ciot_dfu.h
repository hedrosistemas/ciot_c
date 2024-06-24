/**
 * @file ciot_dfu.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_dfu__H__
#define __CIOT_dfu__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_err.h"
#include "ciot_iface.h"

#include "ciot/proto/v1/dfu.pb-c.h"

typedef Ciot__DfuCfg ciot_dfu_cfg_t;
typedef Ciot__DfuReq ciot_dfu_req_t;
typedef Ciot__DfuStatus ciot_dfu_status_t;
typedef Ciot__DfuState ciot_dfu_state_t;
typedef Ciot__DfuReq ciot_dfu_req_t;
typedef Ciot__DfuData ciot_dfu_data_t;

typedef struct ciot_dfu
{
    ciot_iface_t iface;
    ciot_dfu_cfg_t cfg;
    ciot_dfu_status_t status;
    ciot_dfu_req_t req;
    ciot_dfu_data_t data;
} ciot_dfu_t;

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_dfu__H__

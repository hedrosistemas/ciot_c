/**
 * @file ciot_ota.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_OTA__H__
#define __CIOT_OTA__H__

#include "ciot_ota_data.h"
#include "ciot_iface.h"
#include "ciot_err.h"

typedef struct ciot_ota *ciot_ota_t;

typedef enum ciot_ota_event_id
{
    CIOT_OTA_EVENT_STATE_CHANGED = CIOT_IFACE_EVENT_CUSTOM,
} ciot_ota_event_id_t;

ciot_ota_t ciot_ota_new(void *handle);
ciot_err_t ciot_ota_start(ciot_ota_t this, ciot_ota_cfg_t *cfg);
ciot_err_t ciot_ota_stop(ciot_ota_t this);
ciot_err_t ciot_ota_process_req(ciot_ota_t this, ciot_ota_req_t *req);
ciot_err_t ciot_ota_send_data(ciot_ota_t this, uint8_t *data, int size);

#endif  //!__CIOT_OTA__H__
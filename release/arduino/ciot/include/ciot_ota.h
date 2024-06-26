/**
 * @file ciot_ota.h
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_OTA__H__
#define __CIOT_OTA__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_ota_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

typedef struct ciot_ota *ciot_ota_t;

typedef enum ciot_ota_event_id
{
    CIOT_OTA_EVENT_STATE_CHANGED = CIOT_IFACE_EVENT_CUSTOM,
} ciot_ota_event_id_t;

typedef struct __attribute__((packed))
{
    ciot_msg_header_t header;
    ciot_ota_status_t status;
} ciot_ota_status_msg_t;

ciot_ota_t ciot_ota_new(void *handle);
ciot_err_t ciot_ota_start(ciot_ota_t self, ciot_ota_cfg_t *cfg);
ciot_err_t ciot_ota_stop(ciot_ota_t self);
ciot_err_t ciot_ota_process_req(ciot_ota_t self, ciot_ota_req_t *req);
ciot_err_t ciot_ota_send_data(ciot_ota_t self, uint8_t *data, int size);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_OTA__H__
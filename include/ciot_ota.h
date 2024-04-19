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

#ifdef __cplusplus
extern "C" {
#endif

#include "types/ciot_ota_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

#ifndef CIOT_CONFIG_OTA_TASK_STACK_SIZE
#define CIOT_CONFIG_OTA_TASK_STACK_SIZE 8192
#endif
#ifndef CIOT_CONFIG_OTA_TASK_PRIORITY
#define CIOT_CONFIG_OTA_TASK_PRIORITY (tskIDLE_PRIORITY + 4)
#endif
#ifndef CIOT_CONFIG_OTA_TASK_CORE_ID
#define CIOT_CONFIG_OTA_TASK_CORE_ID 1
#endif
#ifndef CIOT_CONFIG_OTA_BUF_SIZE
#define CIOT_CONFIG_OTA_BUF_SIZE 1024
#endif

typedef struct ciot_ota *ciot_ota_t;

typedef enum ciot_ota_event_id
{
    CIOT_OTA_EVENT_CONNECTED = CIOT_IFACE_EVENT_CUSTOM,
    CIOT_OTA_EVENT_READING_INFO,
    CIOT_OTA_EVENT_DECRYPTING,
    CIOT_OTA_EVENT_WRITING,
    CIOT_OTA_EVENT_UPDATING_APP,
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
ciot_err_t ciot_ota_rollback(ciot_ota_t self);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_OTA__H__
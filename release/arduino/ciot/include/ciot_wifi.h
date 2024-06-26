/**
 * @file ciot_wifi.h
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_WIFI__H__
#define __CIOT_WIFI__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_wifi_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

typedef struct ciot_wifi *ciot_wifi_t;

typedef enum ciot_wifi_event_id
{
    CIOT_WIFI_EVENT_STA_START = CIOT_IFACE_EVENT_CUSTOM,
    CIOT_WIFI_EVENT_STA_STOP,
    CIOT_WIFI_EVENT_STA_CONNECTED,
    CIOT_WIFI_EVENT_STA_DISCONNECTED,
    CIOT_WIFI_EVENT_AP_START,
    CIOT_WIFI_EVENT_AP_STOP,
    CIOT_WIFI_EVENT_AP_STACONNECTED,
    CIOT_WIFI_EVENT_AP_STADISCONNECTED,
} ciot_wifi_event_id_t;

typedef struct __attribute__((packed))
{
    ciot_msg_header_t header;
    ciot_wifi_status_u status;
} ciot_wifi_status_msg_t;

ciot_err_t ciot_wifi_init(void);

ciot_wifi_t ciot_wifi_new(void *handle);
ciot_err_t ciot_wifi_start(ciot_wifi_t self, ciot_wifi_cfg_t *cfg);
ciot_err_t ciot_wifi_stop(ciot_wifi_t self);
ciot_err_t ciot_wifi_process_req(ciot_wifi_t self, ciot_wifi_req_t *req);
ciot_err_t ciot_wifi_send_data(ciot_wifi_t self, uint8_t *data, int size);

ciot_err_t ciot_wifi_get_mac(ciot_wifi_t self, ciot_wifi_type_t type, uint8_t mac[6]);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_WIFI__H__
/**
 * @file ciot_ntp.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_ntp.h"

#if CIOT_CONFIG_FEATURE_NTP && defined(CIOT_TARGET_ESP32)

#include <string.h>

#include "esp_sntp.h"
#include "esp_log.h"
#include "esp_bit_defs.h"


struct ciot_ntp
{
    ciot_iface_t iface;
    ciot_ntp_cfg_t cfg;
    ciot_ntp_status_t status;
};

static const char *TAG = "ciot_ntp";

static void ciot_ntp_sync_notification_cb(struct timeval *tv);

ciot_ntp_t self;

ciot_ntp_t ciot_ntp_new(void *handle)
{
    ciot_ntp_t self = calloc(1, sizeof(struct ciot_ntp));
    self->iface.base.ptr = self;
    self->iface.base.start = (ciot_iface_start_fn *)ciot_ntp_start;
    self->iface.base.stop = (ciot_iface_stop_fn *)ciot_ntp_stop;
    self->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_ntp_process_req;
    self->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_ntp_send_data;
    self->iface.base.cfg.ptr = &self->cfg;
    self->iface.base.cfg.size = sizeof(self->cfg);
    self->iface.base.status.ptr = &self->status;
    self->iface.base.status.size = sizeof(self->status);
    self->iface.info.type = CIOT_IFACE_TYPE_NTP;
    return self;
}

ciot_err_t ciot_ntp_start(ciot_ntp_t self, ciot_ntp_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(cfg);

    ESP_LOGI(TAG, "start");

    self = self;

    memcpy(&self->cfg, cfg, sizeof(self->cfg));

    if(self->status.init)
    {
        esp_sntp_stop();
    }

    if(self->cfg.sync_interval == 0)
    {
        self->cfg.sync_interval = CIOT_CONFIG_NTP_SYNC_INTERVAL;
    }

    for (size_t i = 0; i < CIOT_CONFIG_NTP_SERVERS_COUNT; i++)
    {
        if(self->cfg.server[i][0] != '\0')
        {
            ESP_LOGI(TAG, "start: server[%d]: %s", i, self->cfg.server[i]);
            esp_sntp_setservername(i, self->cfg.server[i]);
        }
    }
    
    if (self->cfg.timezone[0] != '\0')
    {
        strncpy(self->cfg.timezone, CIOT_CONFIG_NTP_TZ, sizeof(self->cfg.timezone));
    }

    esp_sntp_setoperatingmode(self->cfg.op_mode);
    esp_sntp_set_sync_interval(self->cfg.sync_interval);
    esp_sntp_set_sync_mode(self->cfg.sync_mode);
    esp_sntp_set_time_sync_notification_cb(ciot_ntp_sync_notification_cb);

    esp_sntp_init();
    self->status.init = 1;

    setenv("TZ", self->cfg.timezone, 1);
    tzset();
    ciot_ntp_set(self);

    return CIOT_OK;
}

ciot_err_t ciot_ntp_stop(ciot_ntp_t self)
{
    CIOT_NULL_CHECK(self);
    esp_sntp_stop();
    return CIOT_OK;
}

ciot_err_t ciot_ntp_process_req(ciot_ntp_t self, ciot_ntp_req_t *req)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_ntp_send_data(ciot_ntp_t self, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_SUPPORTED;   
}

ciot_err_t ciot_ntp_set(ciot_ntp_t ntp)
{
    self = ntp;
    return CIOT_OK;
}

static void ciot_ntp_sync_notification_cb(struct timeval *tv)
{
    ESP_LOGI(TAG, "ntp sync ok");
    ciot_iface_event_t iface_event = {0};
    ciot_ntp_status_msg_t status_msg = {0};

    status_msg.header.iface = self->iface.info;
    iface_event.data = (ciot_iface_event_data_u*)&status_msg;
    iface_event.size = sizeof(status_msg);


    self->status.sync = 1;
    self->status.sync_count++;
    self->status.last_sync = time(NULL);
    status_msg.header.type = CIOT_MSG_TYPE_START;
    status_msg.status = self->status;
    iface_event.id = CIOT_IFACE_EVENT_STARTED;

    if(self->iface.event_handler != NULL)
    {
        self->iface.event_handler(&self->iface, &iface_event, self->iface.event_args);
    }
}

#endif

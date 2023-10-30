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

#include <string.h>

#include "esp_sntp.h"
#include "esp_log.h"
#include "esp_bit_defs.h"

#include "ciot_ntp.h"

struct ciot_ntp
{
    ciot_iface_t iface;
    ciot_ntp_cfg_t cfg;
    ciot_ntp_status_t status;
};

static const char *TAG = "ciot_ntp";

static void ciot_ntp_sync_notification_cb(struct timeval *tv);

ciot_ntp_t this;

ciot_ntp_t ciot_ntp_new(void *handle)
{
    ciot_ntp_t this = calloc(1, sizeof(struct ciot_ntp));
    this->iface.base.ptr = this;
    this->iface.base.start = (ciot_iface_start_fn *)ciot_ntp_start;
    this->iface.base.stop = (ciot_iface_stop_fn *)ciot_ntp_stop;
    this->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_ntp_process_req;
    this->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_ntp_send_data;
    this->iface.base.cfg.ptr = &this->cfg;
    this->iface.base.cfg.size = sizeof(this->cfg);
    this->iface.base.status.ptr = &this->status;
    this->iface.base.status.size = sizeof(this->status);
    this->iface.info.type = CIOT_IFACE_TYPE_NTP;
    return this;
}

ciot_err_t ciot_ntp_start(ciot_ntp_t this, ciot_ntp_cfg_t *cfg)
{
    CIOT_NULL_CHECK(this);
    CIOT_NULL_CHECK(cfg);

    ESP_LOGI(TAG, "start");

    this = this;

    memcpy(&this->cfg, cfg, sizeof(this->cfg));

    if(this->status.init)
    {
        esp_sntp_stop();
    }

    if(this->cfg.sync_interval == 0)
    {
        this->cfg.sync_interval = CIOT_CONFIG_NTP_SYNC_INTERVAL;
    }

    for (size_t i = 0; i < CIOT_CONFIG_NTP_SERVERS_COUNT; i++)
    {
        if(this->cfg.server[i][0] != '\0')
        {
            ESP_LOGI(TAG, "start: server[%d]: %s", i, this->cfg.server[i]);
            esp_sntp_setservername(i, this->cfg.server[i]);
        }
    }
    
    if (this->cfg.timezone[0] != '\0')
    {
        strncpy(this->cfg.timezone, CIOT_CONFIG_NTP_TZ, sizeof(this->cfg.timezone));
    }

    esp_sntp_setoperatingmode(this->cfg.op_mode);
    esp_sntp_set_sync_interval(this->cfg.sync_interval);
    esp_sntp_set_sync_mode(this->cfg.sync_mode);
    esp_sntp_set_time_sync_notification_cb(ciot_ntp_sync_notification_cb);

    esp_sntp_init();
    this->status.init = 1;

    setenv("TZ", this->cfg.timezone, 1);
    tzset();
    ciot_ntp_set(this);

    return CIOT_OK;
}

ciot_err_t ciot_ntp_stop(ciot_ntp_t this)
{
    CIOT_NULL_CHECK(this);
    esp_sntp_stop();
    return CIOT_OK;
}

ciot_err_t ciot_ntp_process_req(ciot_ntp_t this, ciot_ntp_req_t *req)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_ntp_send_data(ciot_ntp_t this, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_SUPPORTED;   
}

ciot_err_t ciot_ntp_set(ciot_ntp_t ntp)
{
    this = ntp;
    return CIOT_OK;
}

static void ciot_ntp_sync_notification_cb(struct timeval *tv)
{
    ESP_LOGI(TAG, "ntp sync ok");
    ciot_iface_event_t event = { 0 };

    event.id = CIOT_IFACE_EVENT_STARTED;
    event.msg.type = CIOT_MSG_TYPE_EVENT;
    event.msg.iface = this->iface.info;

    this->status.sync = 1;
    this->status.sync_count++;
    this->status.last_sync = time(NULL);

    if(this->iface.event_handler != NULL)
    {
        this->iface.event_handler(this, &event, this->iface.event_args);
    }
}
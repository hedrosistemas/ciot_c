/**
 * @file ciot_ntp.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "esp_sntp.h"
#include "ciot_ntp.h"
#include "ciot_err.h"
#include "ciot_timer.h"
#include "ciot_msg.h"

// static const char *TAG = "ciot_ntp";

struct ciot_ntp
{
    ciot_ntp_base_t base;
};

void *notif_args;

static void ciot_ntp_sync_notification_cb(struct timeval *tv);

ciot_ntp_t ciot_ntp_new(void *handle)
{
    ciot_ntp_t self = calloc(1, sizeof(struct ciot_ntp));
    ciot_ntp_init(self);
    return self;
}

ciot_err_t ciot_ntp_start(ciot_ntp_t self, ciot_ntp_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);

    ciot_ntp_base_t *base = &self->base;

    if(base->status.init)
    {
        esp_sntp_stop();
    }

    ciot_ntp_set_cfg(self, cfg);

    esp_sntp_setoperatingmode(cfg->op_mode);
    esp_sntp_set_sync_interval(cfg->sync_interval);
    esp_sntp_set_sync_mode(cfg->sync_mode);
    esp_sntp_set_time_sync_notification_cb(ciot_ntp_sync_notification_cb);

    notif_args = self;
    esp_sntp_init();

    base->status.init = true;

    setenv("TZ", self->base.cfg.timezone, 1);
    tzset();

    return CIOT_ERR__OK;
}

ciot_err_t ciot_ntp_stop(ciot_ntp_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    esp_sntp_stop();
    return CIOT_ERR__OK;
}

static void ciot_ntp_sync_notification_cb(struct timeval *tv)
{
    if(notif_args == NULL) return;
    
    ciot_ntp_t self = (ciot_ntp_t)notif_args;
    ciot_ntp_base_t *base = &self->base;

    base->status.sync = 1;
    base->status.sync_count++;
    base->status.last_sync = ciot_timer_now();

    ciot_iface_event_t event = { 0 };
    event.msg = ciot_msg_get(CIOT__MSG_TYPE__MSG_TYPE_STATUS, &base->iface);
    event.type = CIOT_IFACE_EVENT_STARTED;
    ciot_iface_send_event(&base->iface, &event);
}

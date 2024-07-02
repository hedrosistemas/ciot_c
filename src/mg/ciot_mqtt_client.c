/**
 * @file ciot_mqtt_client.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-06-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdlib.h>
#include "mongoose.h"
#include "ciot_mqtt_client.h"
#include "ciot_err.h"
#include "ciot_timer.h"
#include "ciot_str.h"

static const char *TAG = "ciot_mqtt_client";

struct ciot_mqtt_client
{
    ciot_mqtt_client_base_t base;
    struct mg_mgr *mgr;
    struct mg_connection *connection;
    time_t last_ping;
    char client_id[CIOT_CONFIG_MQTT_CLIENT_ID_SIZE];
    char url[CIOT_CONFIG_MQTT_CLIENT_URL_SIZE];
    char user[CIOT_CONFIG_MQTT_USER_SIZE];
    char password[CIOT_CONFIG_MQTT_PASS_SIZE];
    char topic_d2b[CIOT_CONFIG_MQTT_TOPIC_SIZE];
    char topic_b2d[CIOT_CONFIG_MQTT_TOPIC_SIZE];
};

static void ciot_mqtt_client_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

ciot_mqtt_client_t ciot_mqtt_client_new(void *handle)
{
    ciot_mqtt_client_t self = calloc(1, sizeof(struct ciot_mqtt_client));
    ciot_mqtt_client_init(self);
    self->mgr = handle;
    return self;
}

ciot_err_t ciot_mqtt_client_start(ciot_mqtt_client_t self, ciot_mqtt_client_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);

    ciot_mqtt_client_base_t *base = &self->base;
    struct mg_mqtt_opts opts = {0};

    ciot_strncpy(self->client_id, cfg->client_id, CIOT_CONFIG_MQTT_CLIENT_ID_SIZE);
    ciot_strncpy(self->url, cfg->url, CIOT_CONFIG_MQTT_CLIENT_URL_SIZE);
    ciot_strncpy(self->user, cfg->user, CIOT_CONFIG_MQTT_USER_SIZE);
    ciot_strncpy(self->password, cfg->password, CIOT_CONFIG_MQTT_PASS_SIZE);
    if(cfg->topics != NULL)
    {
        ciot_strncpy(self->topic_b2d, cfg->topics->b2d, CIOT_CONFIG_MQTT_TOPIC_SIZE);
        ciot_strncpy(self->topic_d2b, cfg->topics->d2b, CIOT_CONFIG_MQTT_TOPIC_SIZE);
    }

    base->cfg = *cfg;

    base->cfg.client_id = self->client_id;
    base->cfg.url = self->url;
    base->cfg.user = self->user;
    base->cfg.password = self->password;
    base->cfg.topics = &self->base.topics;
    base->cfg.topics->b2d = self->topic_b2d;
    base->cfg.topics->d2b = self->topic_d2b;

    opts.client_id = mg_str(cfg->client_id);
    opts.user = mg_str(cfg->user);
    opts.pass = mg_str(cfg->password);
    opts.qos = cfg->qos;
    opts.version = 4;
    opts.keepalive = 60;
    opts.clean = true;

    base->status.state = CIOT__MQTT_CLIENT_STATE__MQTT_STATE_CONNECTING;

    self->connection = mg_mqtt_connect(self->mgr, self->url, &opts, ciot_mqtt_client_event_handler, self);

    return CIOT_ERR__OK;
}

ciot_err_t ciot_mqtt_client_stop(ciot_mqtt_client_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_mqtt_client_sub(ciot_mqtt_client_t self, char *topic, int qos)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(topic);
    CIOT_ERR_EMPTY_STRING_CHECK(topic);
    struct mg_mqtt_opts opts = {0};
    opts.topic = mg_str(topic);
    opts.qos = qos;
    mg_mqtt_sub(self->connection, &opts);
    return CIOT_ERR__OK;
}

ciot_err_t ciot_mqtt_client_pub(ciot_mqtt_client_t self, char *topic, uint8_t *data, int size, int qos)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(topic);
    CIOT_ERR_EMPTY_STRING_CHECK(topic);
    struct mg_mqtt_opts opts = {0};
    struct mg_str msg = {0};
    msg.ptr = (const char*)data;
    msg.len = size;
    opts.topic = mg_str(topic);
    opts.message = msg;
    opts.qos = qos;
    opts.retain = false;
    mg_mqtt_pub(self->connection, &opts);
    return CIOT_ERR__OK;
}

static void ciot_mqtt_client_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
    ciot_mqtt_client_t self = fn_data;
    ciot_mqtt_client_base_t *base = &self->base;
    ciot_iface_event_t iface_event = {0};
    mg_event_t mg_ev = ev;

    switch (mg_ev)
    {
    case MG_EV_ERROR:
    {
        CIOT_LOGE(TAG, "MG_EV_ERROR (%s)", (char *)ev_data);
        base->status.state = CIOT__MQTT_CLIENT_STATE__MQTT_STATE_ERROR;
        iface_event.type = CIOT_IFACE_EVENT_ERROR;
        ciot_iface_send_event(&base->iface, &iface_event);
        break;
    }
    case MG_EV_OPEN:
        CIOT_LOGD(TAG, "MG_EV_OPEN url:%s", self->url);
        base->status.state = CIOT__MQTT_CLIENT_STATE__MQTT_STATE_CONNECTING;
        iface_event.type = CIOT_IFACE_EVENT_INTERNAL;
        ciot_iface_send_event(&base->iface, &iface_event);
        break;
    case MG_EV_POLL:
    {
        if(base->status.state == CIOT__MQTT_CLIENT_STATE__MQTT_STATE_CONNECTED &&
           ciot_timer_now() >= self->last_ping + 10)
        {
            CIOT_LOGD(TAG, "MQTT_EV_PING");
            mg_mqtt_ping(c);
            self->last_ping = ciot_timer_now();
        }
        return;
    }
    case MG_EV_MQTT_OPEN:
    {
        if(base->status.state != CIOT__MQTT_CLIENT_STATE__MQTT_STATE_CONNECTED)
        {
            CIOT_LOGI(TAG, "MG_EV_MQTT_OPEN url:%s", self->url);
            base->status.conn_count++;
            base->status.state = CIOT__MQTT_CLIENT_STATE__MQTT_STATE_CONNECTED;
            iface_event.type = CIOT_IFACE_EVENT_STARTED;
            if(self->topic_b2d[0] != '\0')
            {
                ciot_mqtt_client_sub(self, self->topic_b2d, base->cfg.qos);
            }
            ciot_iface_send_event_type(&base->iface, CIOT_IFACE_EVENT_STARTED);
        }
        break;
    }
    case MG_EV_MQTT_MSG:
    {
        CIOT_LOGD(TAG, "MG_EV_MQTT_MSG");
        struct mg_mqtt_message *mm = (struct mg_mqtt_message *)ev_data;
        if(strncmp(mm->topic.ptr, base->cfg.topics->b2d, mm->topic.len) == 0)
        {
            iface_event.type = CIOT_IFACE_EVENT_REQUEST;
            iface_event.data = (uint8_t*)mm->data.ptr;
            iface_event.size = mm->data.len;
            ciot_iface_send_event(&base->iface, &iface_event);
        }
        else
        {
            ciot_mqtt_client_event_data_t event_data = {0};
            event_data.topic = (char*)mm->topic.ptr;
            event_data.data = (uint8_t*)mm->data.ptr;
            iface_event.type = CIOT_IFACE_EVENT_DATA;
            iface_event.data = (uint8_t*)&event_data;
            iface_event.size = mm->data.len;
            ciot_iface_send_event(&base->iface, &iface_event);
        }
        break;
    }
    case MG_EV_CLOSE:
    {
        CIOT_LOGI(TAG, "MG_EV_CLOSE");
        base->status.state = CIOT__MQTT_CLIENT_STATE__MQTT_STATE_DISCONNECTED;
        iface_event.type = CIOT_IFACE_EVENT_STOPPED;
        ciot_iface_send_event(&base->iface, &iface_event);
        break;
    }
    default:
        return;
    }
}

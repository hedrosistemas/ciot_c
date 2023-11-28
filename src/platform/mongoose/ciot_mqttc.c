/**
 * @file ciot_mqtt.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "ciot_mqttc.h"

#if CIOT_CONFIG_FEATURE_MQTTC && defined(CIOT_TARGET_MONGOOSE)

#include <stdlib.h>
#include "mongoose.h"
#include "ciot_log.h"

struct ciot_mqttc
{
    ciot_iface_t iface;
    ciot_mqttc_cfg_t cfg;
    ciot_mqttc_status_t status;
    struct mg_mgr *mgr;
    struct mg_connection *connection;
};

static void ciot_mqttc_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

static const char *TAG = "ciot_mqttc";

ciot_mqttc_t ciot_mqttc_new(void *handle)
{
    ciot_mqttc_t self = calloc(1, sizeof(struct ciot_mqttc));
    self->iface.base.ptr = self;
    self->iface.base.start = (ciot_iface_start_fn *)ciot_mqttc_start;
    self->iface.base.stop = (ciot_iface_stop_fn *)ciot_mqttc_stop;
    self->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_mqttc_process_req;
    self->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_mqttc_send_data;
    self->iface.base.cfg.ptr = &self->cfg;
    self->iface.base.cfg.size = sizeof(self->cfg);
    self->iface.base.status.ptr = &self->status;
    self->iface.base.status.size = sizeof(self->status);
    self->iface.info.type = CIOT_IFACE_TYPE_MQTT;
    self->mgr = handle;
    return self;
}

ciot_err_t ciot_mqttc_start(ciot_mqttc_t self, ciot_mqttc_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(cfg);
    struct mg_mqtt_opts opts = {0};
    memcpy(&self->cfg, cfg, sizeof(self->cfg));
    opts.client_id = mg_str(self->cfg.client_id);
    opts.user = mg_str(self->cfg.user);
    opts.pass = mg_str(self->cfg.pass);
    opts.qos = self->cfg.qos;
    opts.version = 4;
    opts.clean = true;
    self->status.state = CIOT_MQTT_STATE_CONNECTING;
    if (self->connection == NULL)
    {
        self->connection = mg_mqtt_connect(self->mgr, self->cfg.url, &opts, ciot_mqttc_event_handler, self);
    }
    return CIOT_OK;
}

ciot_err_t ciot_mqttc_stop(ciot_mqttc_t self)
{
    CIOT_NULL_CHECK(self);
    mg_mqtt_disconnect(self->connection, NULL);
    return CIOT_OK;
}

ciot_err_t ciot_mqttc_process_req(ciot_mqttc_t self, ciot_mqttc_req_t *req)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(req);

    switch (req->id)
    {
    case CIOT_MQTT_REQ_PUBLISH:
        return ciot_mqttc_publish(self, &req->data.publish);
    case CIOT_MQTT_REQ_SUBSCRIBE:
        return ciot_mqttc_subscribe(self, &req->data.subscribe);
    default:
        return CIOT_ERR_INVALID_ID;
    }
}

ciot_err_t ciot_mqttc_send_data(ciot_mqttc_t self, uint8_t *data, int size)
{
    CIOT_NULL_CHECK(self);
    ciot_mqttc_req_publish_t req = {0};
    memcpy(req.topic, self->cfg.topics.d2b, sizeof(req.topic));
    memcpy(req.msg, data, size);
    req.qos = self->cfg.qos;
    req.size = size;
    ciot_mqttc_publish(self, &req);
    return CIOT_OK;
}

ciot_err_t ciot_mqttc_publish(ciot_mqttc_t self, ciot_mqttc_req_publish_t *req)
{
    CIOT_NULL_CHECK(self);
    if (req->size < CIOT_CONFIG_MESSAGE_LEN)
    {
        struct mg_mqtt_opts opts = {0};
        struct mg_str msg = {0};
        msg.ptr = (const char *)req->msg;
        msg.len = req->size;
        opts.topic = mg_str(req->topic);
        opts.message = msg;
        opts.qos = req->qos;
        opts.retain = false;
        mg_mqtt_pub(self->connection, &opts);
        return CIOT_OK;
    }
    else
    {
        return CIOT_ERR_OVERFLOW;
    }
}

ciot_err_t ciot_mqttc_subscribe(ciot_mqttc_t self, ciot_mqttc_req_subscribe_t *req)
{
    CIOT_NULL_CHECK(self);
    struct mg_mqtt_opts opts = {0};
    opts.topic = mg_str(req->topic);
    opts.qos = req->qos;
    mg_mqtt_sub(self->connection, &opts);
    return CIOT_OK;
}

static void ciot_mqttc_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
    ciot_mqttc_t self = fn_data;

    if(self == NULL) return;

    ciot_iface_event_t iface_event = {0};
    ciot_mqttc_status_t iface_status = self->status;
    mg_event_t mg_evt = ev;    

    switch (mg_evt)
    {
    case MG_EV_ERROR:
    {
        CIOT_LOGE(TAG, "MG_EV_ERROR:%lu:%s", c->id, (char *)ev_data);
        iface_status.error.code = c->id;
        iface_status.state = CIOT_MQTT_STATE_ERROR;
        iface_event.id = CIOT_IFACE_EVENT_ERROR;
        iface_event.data = (ciot_iface_event_data_u*)&iface_status;
        iface_event.size = sizeof(iface_status);
        break;
    }
    case MG_EV_OPEN:
        CIOT_LOGI(TAG, "MG_EV_OPEN");
        iface_status.state = CIOT_MQTT_STATE_CONNECTING;
        iface_event.id = CIOT_MQTT_EVENT_CONNECTING;
        iface_event.data = (ciot_iface_event_data_u*)&iface_status;
        iface_event.size = sizeof(iface_status);
        break;
    case MG_EV_MQTT_OPEN:
    {
        CIOT_LOGI(TAG, "MG_EV_MQTT_OPEN url:%s", self->cfg.url);
        iface_status.conn_count++;
        iface_status.state = CIOT_MQTT_STATE_CONNECTED;
        ciot_mqttc_req_subscribe_t subs = { .qos = self->cfg.qos };
        memcpy(subs.topic, self->cfg.topics.b2d, sizeof(subs.topic));
        ciot_mqttc_subscribe(self, &subs);
        iface_event.id = CIOT_IFACE_EVENT_STARTED;
        iface_event.data = (ciot_iface_event_data_u*)&iface_status;
        iface_event.size = sizeof(iface_status);
        break;
    }
    case MG_EV_MQTT_MSG:
    {
        CIOT_LOGI(TAG, "MG_EV_MQTT_MSG");
        struct mg_mqtt_message *mm = (struct mg_mqtt_message *)ev_data;
        iface_event.id = (strncmp(mm->topic.ptr, self->cfg.topics.b2d, mm->topic.len) == 0) 
            ? CIOT_IFACE_EVENT_REQUEST 
            : CIOT_IFACE_EVENT_DATA;
        if(iface_event.id == CIOT_IFACE_EVENT_REQUEST) {
            iface_event.data = (ciot_iface_event_data_u*)mm->data.ptr;
            iface_event.size = mm->data.len;
        }
        else
        {
            ciot_mqttc_event_data_t  iface_event_data = { 0 };
            iface_event_data.payload.ptr = (uint8_t*)mm->data.ptr;
            iface_event_data.payload.size = mm->data.len;
            iface_event_data.topic = (char*)mm->topic.ptr;
            iface_event.data = (ciot_iface_event_data_u*)&iface_event_data;
            iface_event.size = sizeof(iface_event_data);
            if(self->iface.event_handler != NULL)
            {
                self->iface.event_handler(&self->iface, &iface_event, self->iface.event_args);
                return;
            }
        }
        break;
    }
    case MG_EV_CLOSE:
    {
        CIOT_LOGI(TAG, "MG_EV_CLOSE");
        iface_status.state = CIOT_MQTT_STATE_DISCONNECTED;
        iface_event.id = CIOT_IFACE_EVENT_STOPPED;
        iface_event.data = (ciot_iface_event_data_u*)&iface_status;
        iface_event.size = sizeof(iface_status);
        break;
    }
    default:
        break;
    }

    self->status = iface_status;

    if(self->iface.event_handler != NULL)
    {
        self->iface.event_handler(&self->iface, &iface_event, self->iface.event_args);
    }
}

#endif

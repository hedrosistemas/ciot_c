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

#include <stdlib.h>

#include "mongoose.h"

#include "ciot_log.h"
#include "ciot_mqttc.h"

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

static void ciot_mqtt_event_data(ciot_mqttc_t self, ciot_iface_event_t *ciot_evt, char *topic, uint8_t *data, int size)
{
    int topic_len = (uint64_t)data - (uint64_t)topic;
    ciot_evt->id = (strncmp(topic, self->cfg.topics.b2d, topic_len) == 0) 
        ? CIOT_IFACE_EVENT_DATA 
        : CIOT_MQTT_EVENT_DATA;
    if(ciot_evt->id == CIOT_IFACE_EVENT_DATA) {
        ciot_evt->size = size;
        memcpy(&ciot_evt->msg.data, data, size);
    }
    else
    {
        ciot_evt->msg.data.mqtt.msg.topic = topic;
        ciot_evt->msg.data.mqtt.msg.data = data;
        ciot_evt->msg.data.mqtt.msg.size = size;
    }
}

static void ciot_mqttc_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
    ciot_mqttc_t self = fn_data;
    ciot_iface_event_t ciot_evt = { 0 };
    mg_event_t mg_evt = ev;    

    ciot_evt.msg.type = CIOT_MSG_TYPE_EVENT;
    ciot_evt.msg.iface = self->iface.info;

    switch (mg_evt)
    {
    case MG_EV_ERROR:
        CIOT_LOGE(TAG, "MG_EV_ERROR:%d:%s", c->id, (char *)ev_data);
        self->status.error.code = c->id;
        self->status.state = CIOT_MQTT_STATE_ERROR;
        ciot_evt.id = CIOT_IFACE_EVENT_ERROR;
        ciot_evt.msg.error = self->status.error.code;
        ciot_evt.msg.data.mqtt.status = self->status;
        break;
    case MG_EV_OPEN:
        CIOT_LOGI(TAG, "MG_EV_OPEN", "");
        self->status.state = CIOT_MQTT_STATE_CONNECTING;
        ciot_evt.id = CIOT_MQTT_EVENT_CONNECTING;
        ciot_evt.msg.data.mqtt.status = self->status;
        break;
    case MG_EV_MQTT_OPEN:
    {
        CIOT_LOGI(TAG, "MG_EV_MQTT_OPEN", "");
        self->status.conn_count++;
        self->status.state = CIOT_MQTT_STATE_CONNECTED;
        ciot_evt.id = CIOT_IFACE_EVENT_STARTED;
        ciot_evt.msg.data.mqtt.status = self->status;
        ciot_mqttc_req_subscribe_t subs = { .qos = self->cfg.qos };
        memcpy(subs.topic, self->cfg.topics.b2d, sizeof(subs.topic));
        ciot_mqttc_subscribe(self, &subs);
        break;
    }
    case MG_EV_MQTT_MSG:
    {
        CIOT_LOGI(TAG, "MG_EV_MQTT_MSG", "");
        struct mg_mqtt_message *mm = (struct mg_mqtt_message *)ev_data;
        ciot_mqtt_event_data(self, &ciot_evt, (char*)mm->topic.ptr, (uint8_t*)mm->data.ptr, mm->data.len);
        break;
    }
    case MG_EV_CLOSE:
        CIOT_LOGI(TAG, "MG_EV_CLOSE", "");
        self->status.state = CIOT_MQTT_STATE_DISCONNECTED;
        ciot_evt.id = CIOT_IFACE_EVENT_STOPPED;
        ciot_evt.msg.data.mqtt.status = self->status;
        break;
    default:
        break;
    }

    if(self->iface.event_handler != NULL)
    {
        self->iface.event_handler(self, &ciot_evt, self->iface.event_args);
    }
}

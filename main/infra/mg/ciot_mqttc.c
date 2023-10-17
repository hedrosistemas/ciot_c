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

#include "stdlib.h"
#include "ciot_mqttc.h"
#include "mongoose.h"

struct ciot_mqtt
{
    ciot_iface_t iface;
    ciot_mqttc_cfg_t cfg;
    ciot_mqttc_status_t status;
    struct mg_mgr *mgr;
    struct mg_connection *connection;
};

static void ciot_mqttc_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data);

ciot_mqttc_t ciot_mqttc_new(void *handle)
{
    ciot_mqttc_t this = calloc(1, sizeof(struct ciot_mqtt));
    this->iface.base.ptr = this;
    this->iface.base.start = (ciot_iface_start_fn *)ciot_mqttc_start;
    this->iface.base.stop = (ciot_iface_stop_fn *)ciot_mqttc_stop;
    this->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_mqttc_process_req;
    this->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_mqttc_send_data;
    this->iface.base.cfg.ptr = &this->cfg;
    this->iface.base.cfg.size = sizeof(this->cfg);
    this->iface.base.status.ptr = &this->status;
    this->iface.base.status.size = sizeof(this->status);
    this->iface.info.type = CIOT_IFACE_TYPE_MQTT;
    this->mgr = handle;
    return this;
}

ciot_err_t ciot_mqttc_start(ciot_mqttc_t this, ciot_mqttc_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(this);
    CIOT_ERR_NULL_CHECK(cfg);
    struct mg_mqtt_opts opts = {0};
    memcpy(&this->cfg, cfg, sizeof(this->cfg));
    opts.user = mg_str(this->cfg.user);
    opts.pass = mg_str(this->cfg.pass);
    opts.qos = this->cfg.qos;
    opts.version = 4;
    opts.clean = true;
    this->status.state = CIOT_MQTT_STATE_CONNECTING;
    if (this->connection == NULL)
    {
        this->connection = mg_mqtt_connect(this->mgr, this->cfg.url, &opts, ciot_mqttc_event_handler, this);
    }
}

ciot_err_t ciot_mqttc_stop(ciot_mqttc_t this)
{
    CIOT_ERR_NULL_CHECK(this);
    mg_mqtt_disconnect(this->connection, NULL);
    return CIOT_OK;
}

ciot_err_t ciot_mqttc_process_req(ciot_mqttc_t this, ciot_mqttc_req_t *req)
{
    CIOT_ERR_NULL_CHECK(this);
    CIOT_ERR_NULL_CHECK(req);

    switch (req->id)
    {
    case CIOT_MQTT_REQ_PUBLISH:
        return ciot_mqttc_publish(this, &req->data.publish);
    case CIOT_MQTT_REQ_SUBSCRIBE:
        return ciot_mqttc_subscribe(this, &req->data.subscribe);
    default:
        return CIOT_ERR_INVALID_ID;
    }
}

ciot_err_t ciot_mqttc_send_data(ciot_mqttc_t this, uint8_t *data, int size)
{
    CIOT_ERR_NULL_CHECK(this);
    ciot_mqttc_req_publish_t req = {0};
    memcpy(req.topic, this->cfg.topics.d2b, sizeof(req.topic));
    memcpy(req.msg, data, size);
    req.qos = this->cfg.qos;
    req.size = size;
    ciot_mqttc_publish(this, &req);
}

ciot_err_t ciot_mqttc_publish(ciot_mqttc_t this, ciot_mqttc_req_publish_t *req)
{
    CIOT_ERR_NULL_CHECK(this);
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
        mg_mqtt_pub(this->connection, &opts);
        return CIOT_OK;
    }
    else
    {
        return CIOT_ERR_OVERFLOW;
    }
}

ciot_err_t ciot_mqttc_subscribe(ciot_mqttc_t this, ciot_mqttc_req_subscribe_t *req)
{
    CIOT_ERR_NULL_CHECK(this);
    struct mg_mqtt_opts opts = {0};
    opts.topic = mg_str(req->topic);
    opts.qos = req->qos;
    mg_mqtt_sub(this->connection, &opts);
    return CIOT_OK;
}

static void ciot_mqtt_event_data(ciot_mqttc_t this, ciot_iface_event_t *event, char *topic, uint8_t *data, int size)
{
    event->id = (strncmp(topic, this->cfg.topics.b2d, CIOT_MQTT_TOPIC_LEN) == 0) 
        ? CIOT_IFACE_EVENT_DATA 
        : CIOT_MQTT_EVENT_DATA;
    if(event->id == CIOT_IFACE_EVENT_DATA) {
        event->size = size;
        memcpy(&event->msg.data, data, size);
    }
    else
    {
        event->msg.data.mqtt.msg.topic = topic;
        event->msg.data.mqtt.msg.data = data;
        event->msg.data.mqtt.msg.size = size;
    }
}

static void ciot_mqttc_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
    ciot_mqttc_t this = fn_data;
    ciot_iface_event_t event = { 0 };

    switch (ev)
    {
    case MG_EV_ERROR:
        printf("MG_EV_ERROR:%d:%s\n", c->id, (char *)ev_data);
        this->status.error.code = c->id;
        this->status.state = CIOT_MQTT_STATE_ERROR;
        event.id = CIOT_IFACE_EVENT_ERROR;
        event.msg.error = this->status.error.code;
        event.msg.data.mqtt.status = this->status;
        break;
    case MG_EV_MQTT_OPEN:
        printf("MG_EV_MQTT_OPEN\n");
        this->status.conn_count++;
        this->status.state = CIOT_MQTT_STATE_CONNECTED;
        event.id = CIOT_IFACE_EVENT_STARTED;
        event.msg.data.mqtt.status = this->status;
        break;
    case MG_EV_MQTT_MSG:
    {
        printf("MG_EV_MQTT_MSG\n");
        struct mg_mqtt_message *mm = (struct mg_mqtt_message *)ev_data;
        ciot_mqtt_event_data(this, &event, (char*)mm->topic.ptr, mm->data.ptr, mm->data.len);
        break;
    }
    case MG_EV_CLOSE:
        printf("MG_EV_CLOSE\n");
        this->status.state = CIOT_MQTT_STATE_DISCONNECTED;
        event.id = CIOT_IFACE_EVENT_STOPPED;
        event.msg.data.mqtt.status = this->status;
        break;
    default:
        break;
    }
    (void)fn_data;
}
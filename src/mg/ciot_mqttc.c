/**
 * @file ciot_mqtt.c
 * @author Wesley Santos (wesleypro37@gmail.com)
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
    time_t last_ping;
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
    if(cfg->topics.b2d[0] != '\0' && cfg->topics.d2b[0] != '\0')
    {
        memcpy(&self->cfg, cfg, sizeof(self->cfg));
    }
    else
    {
        memcpy(&self->cfg, cfg, sizeof(self->cfg) - sizeof(self->cfg.topics));
    }
    opts.client_id = mg_str(self->cfg.client_id);
    opts.user = mg_str(self->cfg.user);
    opts.pass = mg_str(self->cfg.pass);
    opts.qos = self->cfg.qos;
    opts.version = 4;
    opts.keepalive = 60;
    opts.clean = true;
    self->status.state = CIOT_MQTT_STATE_CONNECTING;
    self->connection = mg_mqtt_connect(self->mgr, self->cfg.url, &opts, ciot_mqttc_event_handler, self);
    return CIOT_OK;
}

ciot_err_t ciot_mqttc_stop(ciot_mqttc_t self)
{
    CIOT_NULL_CHECK(self);
    struct mg_mqtt_opts opts = {0};
    mg_mqtt_disconnect(self->connection, &opts);
    return CIOT_OK;
}

ciot_err_t ciot_mqttc_process_req(ciot_mqttc_t self, ciot_mqttc_req_t *req)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(req);

    switch (req->type)
    {
    case CIOT_MQTT_REQ_PUBLISH:
        return ciot_mqttc_publish(self, req->data.publish.topic, req->data.publish.msg, req->data.publish.size, req->data.publish.qos);
    case CIOT_MQTT_REQ_SUBSCRIBE:
        return ciot_mqttc_subscribe(self, req->data.subscribe.topic, req->data.subscribe.qos);
    default:
        return CIOT_ERR_INVALID_ID;
    }
}

ciot_err_t ciot_mqttc_send_data(ciot_mqttc_t self, uint8_t *data, int size)
{
    CIOT_NULL_CHECK(self);
    ciot_mqttc_publish(self, self->cfg.topics.d2b, data, size, self->cfg.qos);
    return CIOT_OK;
}

ciot_err_t ciot_mqttc_publish(ciot_mqttc_t self, char *topic, uint8_t *data, int size, uint8_t qos)
{
    CIOT_NULL_CHECK(self);
    if(topic[0] != '\0')
    {
        struct mg_mqtt_opts opts = {0};
        struct mg_str msg = {0};
        msg.ptr = (const char *)data;
        msg.len = size;
        opts.topic = mg_str(topic);
        opts.message = msg;
        opts.qos = qos;
        opts.retain = false;
        self->status.data_rate += size;
        mg_mqtt_pub(self->connection, &opts);
    }
    return CIOT_OK;
}

ciot_err_t ciot_mqttc_subscribe(ciot_mqttc_t self, char *topic, uint8_t qos)
{
    CIOT_NULL_CHECK(self);
    struct mg_mqtt_opts opts = {0};
    opts.topic = mg_str(topic);
    opts.qos = qos;
    mg_mqtt_sub(self->connection, &opts);
    return CIOT_OK;
}

ciot_err_t ciot_mqttc_get_topics(ciot_mqttc_t self, ciot_mqttc_topics_cfg_t *topics)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(topics);
    *topics = self->cfg.topics;
    return CIOT_OK;
}

ciot_err_t ciot_mqttc_set_topics(ciot_mqttc_t self, ciot_mqttc_topics_cfg_t *topics)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(topics);
    ciot_mqttc_set_d2b_topic(self, topics->d2b);
    return ciot_mqttc_set_b2d_topic(self, topics->b2d);
}

ciot_err_t ciot_mqttc_set_d2b_topic(ciot_mqttc_t self, char *topic)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(topic);
    strcpy(self->cfg.topics.d2b, topic);
    return CIOT_OK;
}

ciot_err_t ciot_mqttc_set_b2d_topic(ciot_mqttc_t self, char *topic)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(topic);
    strcpy(self->cfg.topics.b2d, topic);
    return ciot_mqttc_subscribe(self, topic, self->cfg.qos);
}

ciot_err_t ciot_mqttc_reset_data_rate(ciot_mqttc_t self)
{
    CIOT_NULL_CHECK(self);
    self->status.data_rate = 0;
    return CIOT_OK;
}

static void ciot_mqttc_event_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
    ciot_mqttc_t self = fn_data;

    if(self == NULL) return;

    ciot_iface_event_t iface_event = {0};
    ciot_mqttc_status_msg_t status_msg = {0};
    mg_event_t mg_evt = ev;

    status_msg.header.iface = self->iface.info;
    iface_event.data = (ciot_iface_event_data_u*)&status_msg;
    iface_event.size = sizeof(status_msg);   

    switch (mg_evt)
    {
    case MG_EV_ERROR:
    {
        CIOT_LOGE(TAG, "MG_EV_ERROR:%lu:%s", c->id, (char *)ev_data);
        // self->status.error.code = (int*)ev_data;
        self->status.state = CIOT_MQTT_STATE_ERROR;
        self->status.error.code = CIOT_ERR_MONGOOSE;
        status_msg.header.type = CIOT_MSG_TYPE_GET_STATUS;
        status_msg.status = self->status;
        iface_event.type = CIOT_IFACE_EVENT_ERROR;
        break;
    }
    case MG_EV_OPEN:
        CIOT_LOGD(TAG, "MG_EV_OPEN");
        self->status.state = CIOT_MQTT_STATE_CONNECTING;
        status_msg.header.type = CIOT_MSG_TYPE_EVENT;
        status_msg.status = self->status;
        iface_event.type = CIOT_MQTT_EVENT_CONNECTING;
        break;
    case MG_EV_POLL:
    {
        if(self->status.state == CIOT_MQTT_STATE_CONNECTED && time(NULL) > self->last_ping + 10)
        {
            CIOT_LOGD(TAG, "MQTT_EV_PING");
            mg_mqtt_ping(c);
            self->last_ping = time(NULL);
        }
        return;
    }
    case MG_EV_MQTT_OPEN:
    {

        if(self->status.state != CIOT_MQTT_STATE_CONNECTED)
        {
            CIOT_LOGD(TAG, "MG_EV_MQTT_OPEN url:%s", self->cfg.url);
            self->status.conn_count++;
            self->status.state = CIOT_MQTT_STATE_CONNECTED;
            status_msg.header.type = CIOT_MSG_TYPE_GET_STATUS;
            status_msg.status = self->status;
            iface_event.type = CIOT_IFACE_EVENT_STARTED;
            if(self->cfg.topics.b2d[0] != '\0')
            {
                ciot_mqttc_subscribe(self, self->cfg.topics.b2d, self->cfg.qos);
            }
        }
        break;
    }
    case MG_EV_MQTT_MSG:
    {
        CIOT_LOGD(TAG, "MG_EV_MQTT_MSG");
        struct mg_mqtt_message *mm = (struct mg_mqtt_message *)ev_data;
        iface_event.type = (strncmp(mm->topic.ptr, self->cfg.topics.b2d, mm->topic.len) == 0) 
            ? CIOT_IFACE_EVENT_REQUEST 
            : CIOT_IFACE_EVENT_DATA;
        if(iface_event.type == CIOT_IFACE_EVENT_REQUEST) {
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
        CIOT_LOGD(TAG, "MG_EV_CLOSE");
        self->status.state = CIOT_MQTT_STATE_DISCONNECTED;
        status_msg.header.type = CIOT_MSG_TYPE_GET_STATUS;
        status_msg.status = self->status;
        iface_event.type = CIOT_IFACE_EVENT_STOPPED;
        break;
    }
    default:
        return;
    }

    if(self->iface.event_handler != NULL)
    {
        self->iface.event_handler(&self->iface, &iface_event, self->iface.event_args);
    }
}

#endif

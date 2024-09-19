/**
 * @file ciot_mqtt_client_base.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include <string.h>
#include "ciot_mqtt_client.h"
#include "ciot_config.h"

// static const char *TAG = "ciot_mqtt_client";

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req);
static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg);
static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size);

ciot_err_t ciot_mqtt_client_init(ciot_mqtt_client_t self)
{
    ciot_mqtt_client_base_t *base = (ciot_mqtt_client_base_t*)self;

    ciot_iface_init(&base->iface);
    ciot__mqtt_client_data__init(&base->data);
    ciot__mqtt_client_cfg__init(&base->cfg);
    ciot__mqtt_client_topics_cfg__init(&base->topics);
    ciot__mqtt_client_status__init(&base->status);
    ciot__mqtt_client_error__init(&base->error);

    base->iface.ptr = self;
    base->iface.process_req = ciot_iface_process_req;
    base->iface.get_data = ciot_iface_get_data;
    base->iface.send_data = ciot_iface_send_data;
    base->iface.info.type = CIOT__IFACE_TYPE__IFACE_TYPE_MQTT;

    base->cfg.topics = &base->topics;
    base->status.error = &base->error;

    base->cfg.client_id = base->client_id;
    base->cfg.url = base->url;
    base->cfg.user = base->user;
    base->cfg.password = base->password;
    base->cfg.topics->pub = base->topic_pub;
    base->cfg.topics->sub = base->topic_sub;
    base->topic_len = 0;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req)
{
    ciot_mqtt_client_t self = iface->ptr;

    switch (req->type)
    {
        case CIOT__MSG_TYPE__MSG_TYPE_START:
            return ciot_mqtt_client_start(self, req->data->mqtt_client->config);
        case CIOT__MSG_TYPE__MSG_TYPE_STOP:
            return ciot_mqtt_client_stop(self);
        case CIOT__MSG_TYPE__MSG_TYPE_REQUEST:
            return ciot_mqtt_client_process_req(self, req->data->mqtt_client->request);
    default:
        break;
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg)
{
    ciot_mqtt_client_base_t *self = iface->ptr;

    self->data.config = NULL;
    self->data.status = NULL;
    self->data.request = NULL;

    switch (msg->type)
    {
    case CIOT__MSG_TYPE__MSG_TYPE_CONFIG:
        self->topic_pub[self->topic_len] = '\0';
        self->data.config = &self->cfg;
        break;
    case CIOT__MSG_TYPE__MSG_TYPE_STATUS:
        self->data.status = &self->status;
        break;
    case CIOT__MSG_TYPE__MSG_TYPE_INFO:
        break;
    default:
        break;
    }

    self->iface.data.mqtt_client = &self->data;
    msg->data = &self->iface.data;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    ciot_mqtt_client_t self = (ciot_mqtt_client_t)iface;
    ciot_mqtt_client_base_t *base = (ciot_mqtt_client_base_t*)self;
    CIOT_ERR_NULL_CHECK(iface);
    CIOT_ERR_NULL_CHECK(data);
    ciot_mqtt_client_pub(self, base->cfg.topics->pub, data, size, base->cfg.qos);
    return CIOT_ERR__OK;
}

ciot_err_t ciot_mqtt_client_process_req(ciot_mqtt_client_t self, ciot_mqtt_client_req_t *req)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(req);    
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_mqtt_client_get_cfg(ciot_mqtt_client_t self, ciot_mqtt_client_cfg_t *cfg)
{
    ciot_mqtt_client_base_t *base = (ciot_mqtt_client_base_t*)self;
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    CIOT_ERR_INDEX_CHECK(base->topic_len, 0, sizeof(base->topic_pub));
    base->topic_pub[base->topic_len] = '\0';
    *cfg = base->cfg;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_mqtt_client_get_status(ciot_mqtt_client_t self, ciot_mqtt_client_status_t *status)
{
    ciot_mqtt_client_base_t *base = (ciot_mqtt_client_base_t*)self;
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(status);
    *status = base->status;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_mqtt_client_send(ciot_mqtt_client_t self, uint8_t *data, int size)
{
    ciot_mqtt_client_base_t *base = (ciot_mqtt_client_base_t*)self;
    return ciot_mqtt_client_pub(self, base->topic_pub, data, size, base->cfg.qos);
}

ciot_err_t ciot_mqtt_client_set_topics(ciot_mqtt_client_t self, char *pub, char *sub)
{
    ciot_mqtt_client_base_t *base = (ciot_mqtt_client_base_t*)self;
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_INDEX_CHECK(base->topic_len, 0, sizeof(base->topic_pub));
    base->cfg.topics->pub = pub;
    base->cfg.topics->sub = sub;
    base->topic_len = strlen(base->topic_pub);
    return ciot_mqtt_client_sub(self, sub, base->cfg.qos);;
}

ciot_err_t ciot_mqtt_client_set_subtopic(ciot_mqtt_client_t self, char *subtopic, int len)
{
    ciot_mqtt_client_base_t *base = (ciot_mqtt_client_base_t*)self;
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_INDEX_CHECK(base->topic_len, 0, sizeof(base->topic_pub));
    memcpy(&base->topic_pub[base->topic_len], subtopic, len);
    return CIOT_ERR__OK;
}

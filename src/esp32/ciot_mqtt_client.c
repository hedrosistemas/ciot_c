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

#ifdef CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
#include "esp_crt_bundle.h"
#endif
#include "mqtt_client.h"
#include "ciot_mqtt_client.h"
#include "ciot_err.h"
#include "ciot_timer.h"
#include "ciot_str.h"
#include "ciot_msg.h"

static const char *TAG = "ciot_mqtt_client";

struct ciot_mqtt_client
{
    ciot_mqtt_client_base_t base;
    esp_mqtt_client_handle_t handle;
};

static void ciot_mqtt_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data);

ciot_mqtt_client_t ciot_mqtt_client_new(void *handle)
{
    ciot_mqtt_client_t self = calloc(1, sizeof(struct ciot_mqtt_client));
    ciot_mqtt_client_init(self);
    return self;
}

ciot_err_t ciot_mqtt_client_start(ciot_mqtt_client_t self, ciot_mqtt_client_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);

    ciot_mqtt_client_base_t *base = &self->base;

    ciot_strncpy(base->client_id, cfg->client_id, CIOT_CONFIG_MQTT_CLIENT_ID_SIZE);
    ciot_strncpy(base->url, cfg->url, CIOT_CONFIG_MQTT_CLIENT_URL_SIZE);
    ciot_strncpy(base->user, cfg->user, CIOT_CONFIG_MQTT_USER_SIZE);
    ciot_strncpy(base->password, cfg->password, CIOT_CONFIG_MQTT_PASS_SIZE);
    if(cfg->topics != NULL)
    {
        ciot_strncpy(base->topic_b2d, cfg->topics->b2d, CIOT_CONFIG_MQTT_TOPIC_SIZE);
        ciot_strncpy(base->topic_d2b, cfg->topics->d2b, CIOT_CONFIG_MQTT_TOPIC_SIZE);
    }

    base->cfg.transport = cfg->transport;
    base->cfg.port = cfg->port;
    base->cfg.qos = cfg->qos;

    const esp_mqtt_client_config_t mqtt_client_cfg = {
        .broker.address.uri = base->url,
        .broker.address.port = base->cfg.port,
        .broker.address.transport = base->cfg.transport,
        .credentials.username = base->user,
        .credentials.authentication.password = base->password,
        .credentials.client_id = base->client_id,
 #ifdef CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
        .broker.verification.crt_bundle_attach = esp_crt_bundle_attach
#endif       
    };

    base->status.state = CIOT__MQTT_CLIENT_STATE__MQTT_STATE_CONNECTING;
    self->handle = esp_mqtt_client_init(&mqtt_client_cfg);
    esp_mqtt_client_register_event(self->handle, ESP_EVENT_ANY_ID, ciot_mqtt_event_handler, self);
    esp_err_t err = esp_mqtt_client_start(self->handle);
    return err == ESP_OK ? CIOT_ERR__OK : CIOT_ERR__FAIL;
}

ciot_err_t ciot_mqtt_client_stop(ciot_mqtt_client_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    self->base.status.state = CIOT__MQTT_CLIENT_STATE__MQTT_STATE_DISCONNECTING;
    esp_err_t err = esp_mqtt_client_stop(self->handle);
    return err == ESP_OK ? CIOT_ERR__OK : CIOT_ERR__FAIL;
}

ciot_err_t ciot_mqtt_client_sub(ciot_mqtt_client_t self, char *topic, int qos)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(topic);
    CIOT_ERR_EMPTY_STRING_CHECK(topic);
    esp_err_t err = esp_mqtt_client_subscribe(self->handle, topic, qos);
    return err == ESP_OK ? CIOT_ERR__OK : CIOT_ERR__FAIL;
}

ciot_err_t ciot_mqtt_client_pub(ciot_mqtt_client_t self, char *topic, uint8_t *data, int size, int qos)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(topic);
    CIOT_ERR_EMPTY_STRING_CHECK(topic);
    int err = 0;
    if(qos == 0)
    {
        err = esp_mqtt_client_publish(self->handle, topic, (char*)data, size, qos, false);
    }
    else
    {
        err = esp_mqtt_client_enqueue(self->handle, topic, (char*)data, size, qos, false, false);
    }
    return err <= 0 ? CIOT_ERR__OK : CIOT_ERR__FAIL;
}

static void ciot_mqtt_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    ciot_mqtt_client_t self = (ciot_mqtt_client_t)handler_args;
    ciot_mqtt_client_base_t *base = &self->base;
    esp_mqtt_event_t *mqtt_event = (esp_mqtt_event_t *)event_data;
    ciot_iface_event_t iface_event = { 0 };

    switch (event_id)
    {
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        base->status.state = CIOT__MQTT_CLIENT_STATE__MQTT_STATE_ERROR;
        base->status.error->code = mqtt_event->error_handle->connect_return_code;
        base->status.error->type = mqtt_event->error_handle->error_type;
        iface_event.type = CIOT_IFACE_EVENT_ERROR;
        iface_event.msg = ciot_msg_get(CIOT__MSG_TYPE__MSG_TYPE_STATUS, &base->iface);
        ciot_iface_send_event(&base->iface, &iface_event);
        break;
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        base->status.state = CIOT__MQTT_CLIENT_STATE__MQTT_STATE_CONNECTED;
        ciot_mqtt_client_sub(self, base->cfg.topics->b2d, base->cfg.qos);
        iface_event.type = CIOT_IFACE_EVENT_STARTED;
        iface_event.msg = ciot_msg_get(CIOT__MSG_TYPE__MSG_TYPE_STATUS, &base->iface);
        ciot_iface_send_event(&base->iface, &iface_event);
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        iface_event.type = CIOT_IFACE_EVENT_STOPPED;
        iface_event.msg = ciot_msg_get(CIOT__MSG_TYPE__MSG_TYPE_STATUS, &base->iface);
        ciot_iface_send_event(&base->iface, &iface_event);
        break;
    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED");
        iface_event.type = CIOT_IFACE_EVENT_INTERNAL;
        iface_event.msg = ciot_msg_get(CIOT__MSG_TYPE__MSG_TYPE_STATUS, &base->iface);
        ciot_iface_send_event(&base->iface, &iface_event);
        return;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED");
        iface_event.type = CIOT_IFACE_EVENT_INTERNAL;
        iface_event.msg = ciot_msg_get(CIOT__MSG_TYPE__MSG_TYPE_STATUS, &base->iface);
        ciot_iface_send_event(&base->iface, &iface_event);
        return;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        if(strncmp(mqtt_event->topic, base->cfg.topics->b2d, mqtt_event->topic_len) == 0)
        {
            iface_event.type = CIOT_IFACE_EVENT_REQUEST;
            iface_event.data = (uint8_t*)mqtt_event->data;
            iface_event.size = mqtt_event->data_len;
            ciot_iface_send_event(&base->iface, &iface_event);
        }
        else
        {
            ciot_mqtt_client_event_data_t iface_event_data = { 0 };
            iface_event_data.topic = mqtt_event->topic;
            iface_event_data.data = (uint8_t*)mqtt_event->data;
            iface_event.data = (uint8_t*)&iface_event_data;
            iface_event.size = mqtt_event->data_len;
            ciot_iface_send_event(&base->iface, &iface_event);
        }
        break;
    default:
        return;
    }
}
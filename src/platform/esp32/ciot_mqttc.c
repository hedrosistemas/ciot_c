/**
 * @file ciot_mqttc.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_mqttc.h"

#if CIOT_CONFIG_FEATURE_MQTTC && defined(CIOT_TARGET_ESP)

#include "esp_log.h"

#ifdef CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
#include "esp_crt_bundle.h"
#endif

#include "mqtt_client.h"

struct ciot_mqttc
{
    ciot_iface_t iface;
    ciot_mqttc_cfg_t cfg;
    ciot_mqttc_status_t status;
    void *handle;
};

static void ciot_mqtt_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data);

static const char *TAG = "ciot_mqtt";

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
    return self;
}

ciot_err_t ciot_mqttc_start(ciot_mqttc_t self, ciot_mqttc_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(cfg);

    if (self->status.state == CIOT_MQTT_STATE_CONNECTED)
    {
        esp_mqtt_client_disconnect(self->handle);
    }

    const esp_mqtt_client_config_t mqtt_client_cfg = {
        .broker.address.uri = self->cfg.url,
        .broker.address.port = self->cfg.port,
        .credentials.username = self->cfg.user,
        .credentials.authentication.password = self->cfg.pass,
        .credentials.client_id = self->cfg.client_id,
#ifdef CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
        .broker.verification.crt_bundle_attach = esp_crt_bundle_attach
#endif
    };

    self->status.state = CIOT_MQTT_STATE_CONNECTING;
    self->handle = esp_mqtt_client_init(&mqtt_client_cfg);
    esp_mqtt_client_register_event(self->handle, ESP_EVENT_ANY_ID, ciot_mqtt_event_handler, self);
    return esp_mqtt_client_start(self->handle);
}

ciot_err_t ciot_mqttc_stop(ciot_mqttc_t self)
{
    CIOT_NULL_CHECK(self);
    self->status.state = CIOT_MQTT_STATE_DISCONNECTING;
    return esp_mqtt_client_stop(self->handle);
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
    CIOT_NULL_CHECK(req);
    int err_code = 0;
    self->status.data_rate += req->size;
    self->status.last_msg_time = time(NULL);
    if (req->qos == 0)
    {
        err_code = esp_mqtt_client_publish(self->handle, req->topic, (char*)req->msg, req->size, req->qos, false);
    }
    else
    {
        err_code = esp_mqtt_client_enqueue(self->handle, req->topic, (char*)req->msg, req->size, req->qos, false, false);
    }
    return err_code != -1 ? CIOT_OK : CIOT_FAIL;
}

ciot_err_t ciot_mqttc_subscribe(ciot_mqttc_t self, ciot_mqttc_req_subscribe_t *req)
{
    CIOT_NULL_CHECK(self);
    if (esp_mqtt_client_subscribe(self->handle, req->topic, req->qos) != -1)
    {
        return CIOT_OK;
    }
    else
    {
        return CIOT_FAIL;
    }
}

static void ciot_mqtt_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    ciot_mqttc_t self = (ciot_mqttc_t)handler_args;

    if (self == NULL) return;

    ciot_iface_event_t iface_event = {0};
    ciot_mqttc_status_t iface_status = self->status;
    esp_mqtt_event_t *mqtt_event = (esp_mqtt_event_t*)event_data;
    iface_event.iface = self->iface.info;

    switch ((esp_mqtt_event_id_t)event_id)
    {
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        iface_status.error.code = mqtt_event->error_handle->connect_return_code;
        iface_status.error.tls_cert_verify_flags = mqtt_event->error_handle->esp_tls_cert_verify_flags;
        iface_status.error.tls_last_err = mqtt_event->error_handle->esp_tls_last_esp_err;
        iface_status.error.tls_stack_err = mqtt_event->error_handle->esp_tls_stack_err;
        iface_status.error.transport_sock = mqtt_event->error_handle->esp_transport_sock_errno;
        iface_status.error.type = mqtt_event->error_handle->error_type;
        iface_status.state = CIOT_MQTT_STATE_ERROR;
        iface_event.id = CIOT_IFACE_EVENT_ERROR;
        iface_event.data = (ciot_iface_event_data_u*)&iface_status;
        iface_event.size = sizeof(iface_status);
        break;
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        iface_status.conn_count++;
        iface_status.state = CIOT_MQTT_STATE_CONNECTED;
        iface_event.id = CIOT_IFACE_EVENT_STARTED;
        iface_event.data = (ciot_iface_event_data_u*)&iface_status;
        iface_event.size = sizeof(iface_status);
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        iface_status.state = CIOT_MQTT_STATE_DISCONNECTED;
        iface_event.id = CIOT_IFACE_EVENT_STOPPED;
        iface_event.data = (ciot_iface_event_data_u*)&iface_status;
        iface_event.size = sizeof(iface_status);
        break;
    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED");
        return;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED");
        return;
    case MQTT_EVENT_DATA:
    {
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        iface_event.id = (strncmp(mqtt_event->topic, self->cfg.topics.b2d, mqtt_event->topic_len) == 0) 
            ? CIOT_IFACE_EVENT_REQUEST 
            : CIOT_IFACE_EVENT_DATA;
        if(iface_event.id == CIOT_IFACE_EVENT_REQUEST) {
            iface_event.data = (ciot_iface_event_data_u*)mqtt_event->data;
            iface_event.size = mqtt_event->data_len;
        }
        else
        {
            ciot_mqttc_event_data_t iface_event_data = { 0 };
            iface_event_data.payload.ptr = (uint8_t*)mqtt_event->data;
            iface_event_data.payload.size = mqtt_event->data_len;
            iface_event_data.topic = mqtt_event->topic;
            iface_event.data = (ciot_iface_event_data_u*)&iface_event_data;
            if(self->iface.event_handler != NULL)
            {
                self->iface.event_handler(&self->iface, &iface_event, self->iface.event_args);
                return;
            }
        }
        break;
    }
    default:
        // ESP_LOGI(TAG, "Other event id:%d", event_id);
        return;
    }

    self->status = iface_status;

    if(self->iface.event_handler != NULL)
    {
        self->iface.event_handler(&self->iface, &iface_event, self->iface.event_args);
    }
}

#endif

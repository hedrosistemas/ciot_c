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

#include "mqtt_client.h"
#include "esp_log.h"

#ifdef CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
#include "esp_crt_bundle.h"
#endif

#include "ciot_mqttc.h"

struct ciot_mqtt
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
    return this;
}

ciot_err_t ciot_mqttc_start(ciot_mqttc_t this, ciot_mqttc_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(this);
    CIOT_ERR_NULL_CHECK(cfg);

    if (this->status.state == CIOT_MQTT_STATE_CONNECTED)
    {
        esp_mqtt_client_disconnect(this->handle);
    }

    const esp_mqtt_client_config_t mqtt_client_cfg = {
        .broker.address.uri = this->cfg.url,
        .broker.address.port = this->cfg.port,
        .credentials.username = this->cfg.user,
        .credentials.authentication.password = this->cfg.pass,
        .credentials.client_id = this->cfg.client_id,
#ifdef CONFIG_MBEDTLS_CERTIFICATE_BUNDLE
        .broker.verification.crt_bundle_attach = esp_crt_bundle_attach
#endif
    };

    this->status.state = CIOT_MQTT_STATE_CONNECTING;
    this->handle = esp_mqtt_client_init(&mqtt_client_cfg);
    esp_mqtt_client_register_event(this->handle, ESP_EVENT_ANY_ID, ciot_mqtt_event_handler, this);
    return esp_mqtt_client_start(this->handle);
}

ciot_err_t ciot_mqttc_stop(ciot_mqttc_t this)
{
    CIOT_ERR_NULL_CHECK(this);
    this->status.state = CIOT_MQTT_STATE_DISCONNECTING;
    return esp_mqtt_client_stop(this->handle);
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
    return CIOT_OK;
}

ciot_err_t ciot_mqttc_publish(ciot_mqttc_t this, ciot_mqttc_req_publish_t *req)
{
    CIOT_ERR_NULL_CHECK(this);
    CIOT_ERR_NULL_CHECK(req);
    int err_code = 0;
    this->status.data_rate += req->size;
    this->status.last_msg_time = time(NULL);
    if (req->qos == 0)
    {
        err_code = esp_mqtt_client_publish(this->handle, req->topic, (char*)req->msg, req->size, req->qos, false);
    }
    else
    {
        err_code = esp_mqtt_client_enqueue(this->handle, req->topic, (char*)req->msg, req->size, req->qos, false, false);
    }
    return err_code != -1 ? CIOT_OK : CIOT_FAIL;
}

ciot_err_t ciot_mqttc_subscribe(ciot_mqttc_t this, ciot_mqttc_req_subscribe_t *req)
{
    CIOT_ERR_NULL_CHECK(this);
    if (esp_mqtt_client_subscribe(this->handle, req->topic, req->qos) != -1)
    {
        return CIOT_OK;
    }
    else
    {
        return CIOT_FAIL;
    }
}

static void ciot_mqttc_event_data(ciot_mqttc_t this, ciot_iface_event_t *event, char *topic, uint8_t *data, int size)
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

static void ciot_mqtt_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    ciot_mqttc_t this = (ciot_mqttc_t)handler_args;
    esp_mqtt_event_t *ev_data = (esp_mqtt_event_t*)event_data;
    ciot_iface_event_t event = { 0 };

    event.msg.type = CIOT_MSG_TYPE_EVENT;
    event.msg.iface = this->iface.info;

    switch ((esp_mqtt_event_id_t)event_id)
    {
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        this->status.error.code = ev_data->error_handle->connect_return_code;
        this->status.error.tls_cert_verify_flags = ev_data->error_handle->esp_tls_cert_verify_flags;
        this->status.error.tls_last_err = ev_data->error_handle->esp_tls_last_esp_err;
        this->status.error.tls_stack_err = ev_data->error_handle->esp_tls_stack_err;
        this->status.error.transport_sock = ev_data->error_handle->esp_transport_sock_errno;
        this->status.error.type = ev_data->error_handle->error_type;
        this->status.state = CIOT_MQTT_STATE_ERROR;
        event.id = CIOT_IFACE_EVENT_ERROR;
        event.msg.error = this->status.error.code;
        event.msg.data.mqtt.status = this->status;
        break;
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        this->status.conn_count++;
        this->status.state = CIOT_MQTT_STATE_CONNECTED;
        event.id = CIOT_IFACE_EVENT_STARTED;
        event.msg.data.mqtt.status = this->status;
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        this->status.state = CIOT_MQTT_STATE_DISCONNECTED;
        event.id = CIOT_IFACE_EVENT_STOPPED;
        event.msg.data.mqtt.status = this->status;
        break;
    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED");
        event.id = CIOT_MQTT_EVENT_SUBSCRIBED;
        event.msg.data.mqtt.msg.topic = ev_data->topic;
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED");
        event.id = CIOT_MQTT_EVENT_UNSUBCRIBED;
        event.msg.data.mqtt.msg.topic = ev_data->topic;
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        ciot_mqttc_event_data(this, &event, ev_data->topic, (uint8_t*)ev_data->data, ev_data->data_len);
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event.id);
        break;
    }

    if(this->iface.event_handler != NULL)
    {
        this->iface.event_handler(this, &event, this->iface.event_args);
    }
}

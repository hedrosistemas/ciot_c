/**
 * @file ciot_wifi.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <string.h>
#include <stdbool.h>

#include "esp_err.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_bit_defs.h"
#include "lwip/ip4_addr.h"

#include "ciot_wifi.h"
#include "ciot_tcp.h"

struct ciot_wifi
{
    ciot_iface_t iface;
    ciot_tcp_t tcp;
    ciot_wifi_cfg_t cfg;
    ciot_wifi_status_u status;
};

static const char *TAG = "ciot_wifi";

static ciot_err_t ciot_wifi_set_cfg(ciot_wifi_t this, ciot_wifi_cfg_t *cfg);
static wifi_mode_t ciot_wifi_get_mode(ciot_wifi_t this, wifi_interface_t type);
static ciot_err_t ciot_wifi_tcp_event_handler(void *sender, ciot_iface_event_t *event, void *args);
static void ciot_wifi_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data);

ciot_err_t ciot_wifi_init(void)
{
    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&config));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_PS_NONE));
    return CIOT_OK;
}

ciot_wifi_t ciot_wifi_new(void *handle)
{
    ciot_wifi_t this = calloc(1, sizeof(struct ciot_wifi));
    this->iface.base.ptr = this;
    this->iface.base.start = (ciot_iface_start_fn *)ciot_wifi_start;
    this->iface.base.stop = (ciot_iface_stop_fn *)ciot_wifi_stop;
    this->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_wifi_process_req;
    this->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_wifi_send_data;
    this->iface.base.cfg.ptr = &this->cfg;
    this->iface.base.cfg.size = sizeof(this->cfg);
    this->iface.base.status.ptr = &this->status;
    this->iface.base.status.size = sizeof(this->status);
    this->iface.info.type = CIOT_IFACE_TYPE_ETH;
    return this;
}

ciot_err_t ciot_wifi_start(ciot_wifi_t this, ciot_wifi_cfg_t *cfg)
{
    ESP_LOGI(TAG, "this start: type:%d ssid:'%s', pass:'%s'", cfg->type, cfg->ssid, cfg->password);

    CIOT_NULL_CHECK(this);

    CIOT_ERROR_RETURN(ciot_wifi_set_cfg(this, cfg));

    wifi_mode_t mode = ciot_wifi_get_mode(this, cfg->type);
    wifi_config_t wifi_conf = {0};
    memcpy(&wifi_conf, cfg, sizeof(cfg->ssid) + sizeof(cfg->password));

    if (cfg->type == CIOT_WIFI_IF_AP)
    {
        wifi_conf.ap.authmode = CIOT_CONFIG_WIFI_AP_AUTH;
        wifi_conf.ap.max_connection = CIOT_CONFIG_WIFI_AP_MAX_CONN;
    }
    else if (this->status.tcp.state == CIOT_TCP_STATE_CONNECTED)
    {
        ESP_LOGI(TAG, "disconnecting from station...");
        ESP_ERROR_CHECK(esp_wifi_disconnect());
        vTaskDelay(portTICK_PERIOD_MS / 500);
    }

    ESP_LOGI(TAG, "Wifi Start");
    ESP_ERROR_CHECK(esp_wifi_set_mode(mode));
    ESP_ERROR_CHECK(esp_wifi_set_config(cfg->type, &wifi_conf));
    ESP_ERROR_CHECK(esp_wifi_start());

    if (cfg->type == CIOT_WIFI_IF_STA)
    {
        if (this->status.tcp.state == CIOT_TCP_STATE_STARTED)
        {
            ESP_LOGI(TAG, "Wifi Connect");
            this->status.tcp.state = CIOT_TCP_STATE_CONNECTING;
            ESP_ERROR_CHECK(esp_wifi_connect());
        }
        return CIOT_OK;
    }

    return CIOT_OK;
}

ciot_err_t ciot_wifi_stop(ciot_wifi_t this)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_wifi_process_req(ciot_wifi_t this, ciot_wifi_req_t *req)
{
    CIOT_NULL_CHECK(this);
    CIOT_NULL_CHECK(req);

    switch (req->id)
    {
    case CIOT_WIFI_REQ_SCAN:
        // TODO: implement scan request
        return CIOT_ERR_NOT_IMPLEMENTED;
    default:
        return CIOT_ERR_INVALID_ID;
    }
}

ciot_err_t ciot_wifi_send_data(ciot_wifi_t this, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_wifi_get_mac(ciot_wifi_t this, ciot_wifi_type_t type, uint8_t mac[6])
{
    return esp_wifi_get_mac(type, mac);
}

static ciot_err_t ciot_wifi_set_cfg(ciot_wifi_t this, ciot_wifi_cfg_t *cfg)
{
    CIOT_NULL_CHECK(this);
    CIOT_NULL_CHECK(cfg);

    if (this->cfg.type != cfg->type)
    {
        return CIOT_ERR_INVALID_TYPE;
    }

    if (this->tcp == NULL)
    {
        ciot_tcp_handle_t tcp_handle = {0};
        esp_netif_t *netif = cfg->type == CIOT_WIFI_IF_STA
                                 ? esp_netif_create_default_wifi_sta()
                                 : esp_netif_create_default_wifi_ap();
        tcp_handle.netif = netif;
        tcp_handle.cfg = &this->cfg.tcp;
        tcp_handle.status = &this->status.tcp;
        this->tcp = ciot_tcp_new(&tcp_handle);
        ciot_tcp_register_event(this->tcp, ciot_wifi_tcp_event_handler, this);
    }
    memcpy(&this->cfg, cfg, sizeof(this->cfg));

    return CIOT_OK;
}

static wifi_mode_t ciot_wifi_get_mode(ciot_wifi_t this, wifi_interface_t type)
{
    if (this == NULL)
        return WIFI_MODE_NULL;

    wifi_mode_t mode;
    ESP_ERROR_CHECK(esp_wifi_get_mode(&mode));

    switch (type)
    {
    case WIFI_IF_STA:
        if (mode == WIFI_MODE_AP || mode == WIFI_MODE_APSTA)
        {
            return WIFI_MODE_APSTA;
        }
        return WIFI_MODE_STA;
    case WIFI_IF_AP:
        if (mode == WIFI_MODE_STA || mode == WIFI_MODE_APSTA)
        {
            return WIFI_MODE_APSTA;
        }
        return WIFI_MODE_AP;
    default:
        return WIFI_MODE_NULL;
    }

    return WIFI_MODE_NULL;
}

static ciot_err_t ciot_wifi_tcp_event_handler(void *sender, ciot_iface_event_t *event, void *args)
{
    CIOT_NULL_CHECK(args);

    ciot_wifi_t this = (ciot_wifi_t)args;
    if (this->iface.event_handler != NULL)
    {
        return this->iface.event_handler(this, event, this->iface.event_args);
    }

    return CIOT_ERR_INVALID_STATE;
}

static void ciot_wifi_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    ciot_wifi_t this = (ciot_wifi_t)handler_args;
    ciot_iface_event_t event = {0};

    event.msg.type = CIOT_MSG_TYPE_EVENT;
    event.msg.iface = this->iface.info;

    switch (event_id)
    {
    case WIFI_EVENT_SCAN_DONE:
    {
        ESP_LOGI(TAG, "WIFI_EVENT_SCAN_DONE");
        wifi_event_sta_scan_done_t *data = (wifi_event_sta_scan_done_t *)event_data;
        this->status.sta.scan = CIOT_WIFI_SCAN_STATE_SCANNED;
        event.id = CIOT_IFACE_EVENT_REQ_DONE;
        event.msg.data.wifi.request.id = CIOT_WIFI_REQ_SCAN;
        // TODO: get scan result and store on req data
        break;
    }
    case WIFI_EVENT_STA_START:
    {
        ESP_LOGI(TAG, "WIFI_EVENT_STA_START");
        CIOT_ERROR_PRINT(esp_wifi_get_mac(WIFI_IF_STA, this->status.tcp.info.mac));
        CIOT_ERROR_PRINT(esp_wifi_connect());
        this->status.tcp.state = CIOT_TCP_STATE_CONNECTING;
        event.id = CIOT_WIFI_EVENT_STA_START;
        break;
    }
    case WIFI_EVENT_STA_STOP:
    {
        ESP_LOGI(TAG, "WIFI_EVENT_STA_STOP");
        this->status.tcp.state = CIOT_TCP_STATE_STOPPED;
        event.id = CIOT_WIFI_EVENT_STA_STOP;
        break;
    }
    case WIFI_EVENT_STA_CONNECTED:
    {
        ESP_LOGI(TAG, "WIFI_EVENT_STA_CONNECTED");
        wifi_event_sta_connected_t *data = (wifi_event_sta_connected_t *)event_data;
        this->status.tcp.state = CIOT_TCP_STATE_CONNECTED;
        this->status.tcp.conn_count++;
        CIOT_ERROR_PRINT(ciot_tcp_start(this->tcp, &this->cfg.tcp));
        event.id = CIOT_WIFI_EVENT_STA_STOP;
        break;
    }
    case WIFI_EVENT_STA_DISCONNECTED:
    {
        ESP_LOGI(TAG, "WIFI_EVENT_STA_DISCONNECTED");
        wifi_event_sta_disconnected_t *data = (wifi_event_sta_disconnected_t *)event_data;
        this->status.tcp.state = CIOT_TCP_STATE_STARTED;
        this->status.sta.disconnect_reason = data->reason;
        event.id = CIOT_WIFI_EVENT_STA_DISCONNECTED;
        break;
    }
    case WIFI_EVENT_AP_START:
    {
        ESP_LOGI(TAG, "WIFI_EVENT_AP_START");
        this->status.tcp.state = CIOT_TCP_STATE_STARTED;
        CIOT_ERROR_PRINT(ciot_tcp_start(this->tcp, &this->cfg.tcp));
        CIOT_ERROR_PRINT(esp_wifi_get_mac(WIFI_IF_AP, this->status.tcp.info.mac));
        event.id = CIOT_WIFI_EVENT_AP_START;
        break;
    }
    case WIFI_EVENT_AP_STOP:
    {
        ESP_LOGI(TAG, "WIFI_EVENT_AP_STOP");
        this->status.tcp.state = CIOT_TCP_STATE_STOPPED;
        event.id = CIOT_WIFI_EVENT_AP_STOP;
        break;
    }
    case WIFI_EVENT_AP_STACONNECTED:
    {
        ESP_LOGI(TAG, "WIFI_EVENT_AP_STACONNECTED");
        wifi_event_ap_staconnected_t *data = (wifi_event_ap_staconnected_t *)event_data;
        this->status.tcp.state = CIOT_TCP_STATE_CONNECTED;
        this->status.tcp.conn_count++;
        event.id = CIOT_WIFI_EVENT_AP_STACONNECTED;
        break;
    }
    case WIFI_EVENT_AP_STADISCONNECTED:
    {
        ESP_LOGI(TAG, "WIFI_EVENT_AP_STADISCONNECTED");
        wifi_event_ap_stadisconnected_t *data = (wifi_event_sta_disconnected_t *)event_data;
        this->status.tcp.state = CIOT_TCP_STATE_STARTED;
        event.id = CIOT_WIFI_EVENT_AP_STADISCONNECTED;
        break;
    }
    default:
        break;
    }

    if (this->iface.event_handler != NULL)
    {
        this->iface.event_handler(this, &event, this->iface.event_args);
    }
}

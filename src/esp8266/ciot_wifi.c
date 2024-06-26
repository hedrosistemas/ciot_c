/**
 * @file ciot_wifi.c
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_wifi.h"

#if CIOT_CONFIG_FEATURE_WIFI && defined(CIOT_TARGET_ESP8266)

#include <string.h>
#include <stdbool.h>

#include "esp_err.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_bit_defs.h"
#include "lwip/ip4_addr.h"

#include "ciot_tcp.h"

struct ciot_wifi
{
    ciot_iface_t iface;
    ciot_tcp_t tcp;
    ciot_wifi_cfg_t cfg;
    ciot_wifi_status_u status;
};

static const char *TAG = "ciot_wifi";

static ciot_err_t ciot_wifi_set_cfg(ciot_wifi_t self, ciot_wifi_cfg_t *cfg);
static wifi_mode_t ciot_wifi_get_mode(ciot_wifi_t self, wifi_interface_t type);
static ciot_err_t ciot_wifi_tcp_event_handler(ciot_iface_t *iface, ciot_iface_event_t *iface_event, void *args);
static void ciot_wifi_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data);

static bool wifi_init = false;

ciot_err_t ciot_wifi_init(void)
{
    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(ciot_tcp_init());
    ESP_ERROR_CHECK(esp_wifi_init(&config));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_PS_NONE));
    return CIOT_OK;
}

ciot_wifi_t ciot_wifi_new(void *handle)
{
    ciot_wifi_t self = calloc(1, sizeof(struct ciot_wifi));
    self->iface.base.ptr = self;
    self->iface.base.start = (ciot_iface_start_fn *)ciot_wifi_start;
    self->iface.base.stop = (ciot_iface_stop_fn *)ciot_wifi_stop;
    self->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_wifi_process_req;
    self->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_wifi_send_data;
    self->iface.base.cfg.ptr = &self->cfg;
    self->iface.base.cfg.size = sizeof(self->cfg);
    self->iface.base.status.ptr = &self->status;
    self->iface.base.status.size = sizeof(self->status);
    self->iface.info.type = CIOT_IFACE_TYPE_WIFI;
    if(wifi_init == false)
    {
        wifi_init = true;
        ESP_ERROR_CHECK(ciot_wifi_init());
    }
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, ciot_wifi_event_handler, self);
    return self;
}

ciot_err_t ciot_wifi_start(ciot_wifi_t self, ciot_wifi_cfg_t *cfg)
{
    ESP_LOGI(TAG, "self start: type:%d ssid:'%s', pass:'%s'", cfg->type, cfg->ssid, cfg->password);

    CIOT_NULL_CHECK(self);

    CIOT_ERROR_RETURN(ciot_wifi_set_cfg(self, cfg));

    wifi_mode_t mode = ciot_wifi_get_mode(self, cfg->type);
    wifi_config_t wifi_conf = {0};
    memcpy(&wifi_conf, cfg, sizeof(cfg->ssid) + sizeof(cfg->password));

    if (cfg->type == CIOT_WIFI_IF_AP)
    {
        wifi_conf.ap.authmode = CIOT_CONFIG_WIFI_AP_AUTH;
        wifi_conf.ap.max_connection = CIOT_CONFIG_WIFI_AP_MAX_CONN;
        self->iface.base.status.size = sizeof(ciot_wifi_ap_status_t);
    }
    else if (self->status.tcp.state == CIOT_TCP_STATE_CONNECTED)
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
        if (self->status.tcp.state == CIOT_TCP_STATE_STARTED)
        {
            ESP_LOGI(TAG, "Wifi Connect");
            self->status.tcp.state = CIOT_TCP_STATE_CONNECTING;
            ESP_ERROR_CHECK(esp_wifi_connect());
        }
        return CIOT_OK;
    }

    return CIOT_OK;
}

ciot_err_t ciot_wifi_stop(ciot_wifi_t self)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_wifi_process_req(ciot_wifi_t self, ciot_wifi_req_t *req)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(req);

    switch (req->type)
    {
    case CIOT_WIFI_REQ_SCAN:
        return CIOT_ERR_NOT_IMPLEMENTED;
    default:
        return CIOT_ERR_INVALID_ID;
    }
}

ciot_err_t ciot_wifi_send_data(ciot_wifi_t self, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_wifi_get_mac(ciot_wifi_t self, ciot_wifi_type_t type, uint8_t mac[6])
{
    return esp_wifi_get_mac(type, mac);
}

static ciot_err_t ciot_wifi_set_cfg(ciot_wifi_t self, ciot_wifi_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(cfg);

    if (self->tcp == NULL)
    {
        ciot_tcp_handle_t tcp_handle = {0};
        tcpip_adapter_if_t netif = cfg->type == CIOT_WIFI_IF_STA
                                 ? TCPIP_ADAPTER_IF_STA
                                 : TCPIP_ADAPTER_IF_AP;
        tcp_handle.netif = netif;
        tcp_handle.cfg = &self->cfg.tcp;
        tcp_handle.status = &self->status.tcp;
        self->tcp = ciot_tcp_new(&tcp_handle);
        ciot_tcp_register_event(self->tcp, ciot_wifi_tcp_event_handler, self);
    } 
    else if (self->cfg.type != cfg->type)
    {
        return CIOT_ERR_INVALID_TYPE;
    }

    memcpy(&self->cfg, cfg, sizeof(self->cfg));

    return CIOT_OK;
}

static wifi_mode_t ciot_wifi_get_mode(ciot_wifi_t self, wifi_interface_t type)
{
    if (self == NULL)
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

static ciot_err_t ciot_wifi_tcp_event_handler(ciot_iface_t *iface, ciot_iface_event_t *iface_event, void *args)
{
    CIOT_NULL_CHECK(args);

    ciot_wifi_t self = (ciot_wifi_t)args;
    if (self->iface.event_handler != NULL)
    {
        return self->iface.event_handler(&self->iface, iface_event, self->iface.event_args);
    }

    return CIOT_ERR_INVALID_STATE;
}

static void ciot_wifi_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    ciot_wifi_t self = (ciot_wifi_t)handler_args;
    ciot_iface_event_t iface_event = {0};
    ciot_wifi_status_msg_t status_msg = {0};

    status_msg.header.iface = self->iface.info;
    iface_event.data = (ciot_iface_event_data_u*)&status_msg;
    iface_event.size = sizeof(status_msg);

    if(self->cfg.type == CIOT_WIFI_IF_AP)
    {
        switch (event_id)
        {
            case WIFI_EVENT_SCAN_DONE:
            {
                ESP_LOGI(TAG, "WIFI_EVENT_SCAN_DONE");
                // wifi_event_sta_scan_done_t *data = (wifi_event_sta_scan_done_t *)event_data;
                self->status.sta.scan = CIOT_WIFI_SCAN_STATE_SCANNED;
                status_msg.header.type = CIOT_MSG_TYPE_EVENT;
                status_msg.status = self->status;
                iface_event.id = CIOT_IFACE_EVENT_DONE;
                // TODO: get scan result and store on req data
                break;
            }
            case WIFI_EVENT_STA_START:
            {
                ESP_LOGI(TAG, "WIFI_EVENT_STA_START");
                CIOT_ERROR_PRINT(esp_wifi_get_mac(WIFI_IF_STA, self->status.tcp.info.mac));
                CIOT_ERROR_PRINT(esp_wifi_connect());
                self->status.tcp.state = CIOT_TCP_STATE_CONNECTING;
                status_msg.header.type = CIOT_MSG_TYPE_EVENT;
                status_msg.status = self->status;
                iface_event.id = CIOT_WIFI_EVENT_STA_START;
                break;
            }
            case WIFI_EVENT_STA_STOP:
            {
                ESP_LOGI(TAG, "WIFI_EVENT_STA_STOP");
                self->status.tcp.state = CIOT_TCP_STATE_STOPPED;
                status_msg.header.type = CIOT_MSG_TYPE_EVENT;
                status_msg.status = self->status;
                iface_event.id = CIOT_WIFI_EVENT_STA_STOP;
                break;
            }
            case WIFI_EVENT_STA_CONNECTED:
            {
                ESP_LOGI(TAG, "WIFI_EVENT_STA_CONNECTED");
                // wifi_event_sta_connected_t *data = (wifi_event_sta_connected_t *)event_data;
                self->status.tcp.state = CIOT_TCP_STATE_CONNECTED;
                self->status.tcp.conn_count++;
                CIOT_ERROR_PRINT(ciot_tcp_start(self->tcp, &self->cfg.tcp));
                status_msg.header.type = CIOT_MSG_TYPE_EVENT;
                status_msg.status = self->status;
                iface_event.id = CIOT_WIFI_EVENT_STA_STOP;
                break;
            }
            case WIFI_EVENT_STA_DISCONNECTED:
            {
                ESP_LOGI(TAG, "WIFI_EVENT_STA_DISCONNECTED");
                wifi_event_sta_disconnected_t *data = (wifi_event_sta_disconnected_t *)event_data;
                self->status.tcp.state = CIOT_TCP_STATE_STARTED;
                self->status.sta.disconnect_reason = data->reason;
                status_msg.header.type = CIOT_MSG_TYPE_EVENT;
                status_msg.status = self->status;
                iface_event.id = CIOT_WIFI_EVENT_STA_DISCONNECTED;
                break;
            }
        }
    }

    if(self->cfg.type == CIOT_WIFI_IF_AP)
    {

        switch(event_id)
        {
            case WIFI_EVENT_AP_START:
            {
                ESP_LOGI(TAG, "WIFI_EVENT_AP_START");
                self->status.tcp.state = CIOT_TCP_STATE_STARTED;
                CIOT_ERROR_PRINT(ciot_tcp_start(self->tcp, &self->cfg.tcp));
                CIOT_ERROR_PRINT(esp_wifi_get_mac(WIFI_IF_AP, self->status.tcp.info.mac));
                status_msg.header.type = CIOT_MSG_TYPE_EVENT;
                status_msg.status = self->status;
                iface_event.id = CIOT_WIFI_EVENT_AP_START;
                break;
            }
            case WIFI_EVENT_AP_STOP:
            {
                ESP_LOGI(TAG, "WIFI_EVENT_AP_STOP");
                self->status.tcp.state = CIOT_TCP_STATE_STOPPED;
                status_msg.header.type = CIOT_MSG_TYPE_EVENT;
                status_msg.status = self->status;
                iface_event.id = CIOT_WIFI_EVENT_AP_STOP;
                break;
            }
            case WIFI_EVENT_AP_STACONNECTED:
            {
                ESP_LOGI(TAG, "WIFI_EVENT_AP_STACONNECTED");
                // wifi_event_ap_staconnected_t *data = (wifi_event_ap_staconnected_t *)event_data;
                self->status.tcp.state = CIOT_TCP_STATE_CONNECTED;
                self->status.tcp.conn_count++;
                status_msg.header.type = CIOT_MSG_TYPE_EVENT;
                status_msg.status = self->status;
                iface_event.id = CIOT_WIFI_EVENT_AP_STACONNECTED;
                break;
            }
            case WIFI_EVENT_AP_STADISCONNECTED:
            {
                ESP_LOGI(TAG, "WIFI_EVENT_AP_STADISCONNECTED");
                // wifi_event_ap_stadisconnected_t *data = (wifi_event_sta_disconnected_t *)event_data;
                self->status.tcp.state = CIOT_TCP_STATE_STARTED;
                status_msg.header.type = CIOT_MSG_TYPE_EVENT;
                status_msg.status = self->status;
                iface_event.id = CIOT_WIFI_EVENT_AP_STADISCONNECTED;
                break;
            }
            default:
                break;
        }
    }

    if (self->iface.event_handler != NULL)
    {
        self->iface.event_handler(&self->iface, &iface_event, self->iface.event_args);
    }
}

#endif
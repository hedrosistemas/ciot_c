/**
 * @file ciot_wifi.c
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
#include "esp_err.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "ciot_wifi.h"
#include "ciot_err.h"
#include "ciot_tcp.h"
#include "ciot_storage.h"

// static const char *TAG = "ciot_wifi";

struct ciot_wifi
{
    ciot_wifi_base_t base;
};

static ciot_err_t ciot_wifi_set_cfg(ciot_wifi_t self, ciot_wifi_cfg_t *cfg);
static wifi_mode_t ciot_wifi_get_mode(ciot_wifi_t self, wifi_interface_t type);
static void ciot_wifi_ap_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data);
static void ciot_wifi_sta_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data);
// static ciot_err_t ciot_wifi_tcp_event_handler(ciot_iface_t *sender, ciot_iface_event_t *iface_event, void *args);

static const char *TAG = "ciot_wifi";
static bool wifi_init = false;

ciot_wifi_t ciot_wifi_new(ciot_wifi_type_t type)
{
    ciot_wifi_t self = calloc(1, sizeof(struct ciot_wifi));
    ciot_wifi_base_t *base = &self->base;

    base->cfg.type = type;

    if (base->cfg.type == CIOT__WIFI_TYPE__WIFI_TYPE_AP)
    {
        CIOT_LOGI(TAG, "Creating wifi ap");
        base->tcp = ciot_tcp_new(&base->iface, CIOT_TCP_TYPE_WIFI_AP);
        ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, ciot_wifi_ap_event_handler, self));
    }

    if (base->cfg.type == CIOT__WIFI_TYPE__WIFI_TYPE_STA)
    {
        CIOT_LOGI(TAG, "Creating wifi sta");
        base->tcp = ciot_tcp_new(&base->iface, CIOT_TCP_TYPE_WIFI_STA);
        ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, ciot_wifi_sta_event_handler, self));
    }

    if (!wifi_init)
    {
        CIOT_LOGI(TAG, "Initializing");
        wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
        // ESP_ERROR_CHECK(ciot_storage_init());
        ESP_ERROR_CHECK(esp_wifi_init(&config));
        ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
        ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_PS_NONE));
        wifi_init = true;
    }

    ciot_wifi_init(self);
    return self;
}

ciot_err_t ciot_wifi_start(ciot_wifi_t self, ciot_wifi_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);

    ciot_wifi_base_t *base = &self->base;
    ciot_tcp_base_t *tcp = (ciot_tcp_base_t *)&base->tcp;

    if(!cfg->enabled)
    {
        return CIOT_ERR__DISABLED;
    }

    CIOT_ERR_RETURN(ciot_wifi_set_cfg(self, cfg));

    wifi_mode_t mode = ciot_wifi_get_mode(self, cfg->type);
    wifi_config_t wifi_cfg = {0};

    strncpy((char *)wifi_cfg.ap.ssid, cfg->ssid, sizeof(wifi_cfg.ap.ssid));
    strncpy((char *)wifi_cfg.ap.password, cfg->password, sizeof(wifi_cfg.ap.password));

    if (cfg->type != CIOT__WIFI_TYPE__WIFI_TYPE_AP && tcp->status.state == CIOT__TCP_STATE__TCP_STATE_CONNECTED)
    {
        CIOT_LOGI(TAG, "Disconnecting");
        ESP_ERROR_CHECK(esp_wifi_disconnect());
        vTaskDelay(pdTICKS_TO_MS(500));
    }

    CIOT_LOGI(TAG, "Start");
    ESP_ERROR_CHECK(esp_wifi_set_mode(mode));
    ESP_ERROR_CHECK(esp_wifi_set_config(cfg->type, &wifi_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());

    if (cfg->type == CIOT__WIFI_TYPE__WIFI_TYPE_STA && tcp->status.state == CIOT__TCP_STATE__TCP_STATE_DISCONNECTED)
    {
        CIOT_LOGI(TAG, "Connecting");
        tcp->status.state = CIOT__TCP_STATE__TCP_STATE_CONNECTING;
        ESP_ERROR_CHECK(esp_wifi_connect());
    }

    return CIOT_ERR__OK;
}

ciot_err_t ciot_wifi_stop(ciot_wifi_t self)
{
    CIOT_LOGI(TAG, "Stopping WiFi");

    wifi_mode_t mode;
    switch (self->base.cfg.type)
    {
    case CIOT__WIFI_TYPE__WIFI_TYPE_STA:
        CIOT_LOGI(TAG, "Stopping station");
        esp_wifi_get_mode(&mode);
        return mode == WIFI_MODE_APSTA ? esp_wifi_set_mode(WIFI_MODE_AP) : esp_wifi_stop();
        break;
    case CIOT__WIFI_TYPE__WIFI_TYPE_AP:
        CIOT_LOGI(TAG, "Stopping access point");
        esp_wifi_get_mode(&mode);
        return mode == WIFI_MODE_APSTA ? esp_wifi_set_mode(WIFI_MODE_STA) : esp_wifi_stop();
    default:
        return CIOT_ERR__INVALID_TYPE;
    }
    return CIOT_ERR__OK;
}

ciot_err_t ciot_wifi_task(ciot_wifi_t self)
{
    return CIOT_ERR__NOT_SUPPORTED;
}

ciot_err_t ciot_wifi_send_bytes(ciot_iface_t *iface, uint8_t *bytes, int size)
{
    return CIOT_ERR__NOT_SUPPORTED;
}

// ciot_err_t ciot_wifi_get_mac(ciot_wifi_t self, ciot_wifi_type_t type, uint8_t mac[6])
// {
//     return esp_wifi_get_mac(type, mac);
// }

static ciot_err_t ciot_wifi_set_cfg(ciot_wifi_t self, ciot_wifi_cfg_t *cfg)
{
    CIOT_LOGI(TAG, "Configuring");

    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);

    ciot_wifi_base_t *base = &self->base;
    ciot_tcp_base_t *tcp = (ciot_tcp_base_t *)&base->tcp;

    if (self->base.cfg.type != cfg->type)
    {
        CIOT_LOGE(TAG, "Invalid wifi type: %s. Expected: %s", ciot__wifi_type__descriptor.values[cfg->type].name, ciot__wifi_type__descriptor.values[self->base.cfg.type].name);
        return CIOT_ERR__INVALID_TYPE;
    }

    if (tcp->netif == NULL)
    {
        CIOT_LOGI(TAG, "Initializing netif");
        CIOT_ERR_RETURN(ciot_tcp_init_netif(base->tcp));
        // CIOT_ERR_RETURN(ciot_iface_set_event_handler(&tcp->iface, ciot_wifi_tcp_event_handler, self));
    }

    base->cfg.type = cfg->type;
    strcpy(base->ssid, cfg->ssid);
    strcpy(base->password, cfg->password);

    if (cfg->tcp != NULL)
    {
        CIOT_LOGI(TAG, "Set tcp config");
        CIOT_ERR_RETURN(ciot_tcp_set_cfg(base->tcp, cfg->tcp));
    }

    return CIOT_ERR__OK;
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
        CIOT_LOGI(TAG, "WIFI_IF_STA");
        if (mode == WIFI_MODE_AP || mode == WIFI_MODE_APSTA)
        {
            CIOT_LOGI(TAG, "WIFI_MODE_APSTA");
            return WIFI_MODE_APSTA;
        }
        CIOT_LOGI(TAG, "WIFI_MODE_STA");
        return WIFI_MODE_STA;
    case WIFI_IF_AP:
        CIOT_LOGI(TAG, "WIFI_IF_AP");
        if (mode == WIFI_MODE_STA || mode == WIFI_MODE_APSTA)
        {
            CIOT_LOGI(TAG, "WIFI_MODE_APSTA");
            return WIFI_MODE_APSTA;
        }
        CIOT_LOGI(TAG, "WIFI_MODE_AP");
        return WIFI_MODE_AP;
    default:
        CIOT_LOGI(TAG, "WIFI_MODE_NULL");
        return WIFI_MODE_NULL;
    }

    CIOT_LOGI(TAG, "WIFI_MODE_NULL");
    return WIFI_MODE_NULL;
}

// static ciot_err_t ciot_wifi_tcp_event_handler(ciot_iface_t *sender, ciot_iface_event_t *iface_event, void *args)
// {
//     CIOT_ERR_NULL_CHECK(args);
//     ciot_wifi_t self = (ciot_wifi_t)args;
//     return ciot_iface_send_event(&self->base.iface, iface_event);
// }

static void ciot_wifi_ap_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
}

static void ciot_wifi_sta_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    ciot_wifi_t self = (ciot_wifi_t)handler_args;
    ciot_wifi_base_t *base = &self->base;
    ciot_tcp_base_t *tcp = (ciot_tcp_base_t *)base->tcp;

    switch (event_id)
    {
    case WIFI_EVENT_SCAN_DONE:
    {
        CIOT_LOGI(TAG, "WIFI_EVENT_SCAN_DONE");
        // TODO: get scan result and store on req data
        break;
    }
    case WIFI_EVENT_STA_START:
    {
        CIOT_LOGI(TAG, "WIFI_EVENT_STA_START");
        CIOT_ERR_PRINT(TAG, esp_wifi_get_mac(WIFI_IF_STA, base->info.tcp->mac.data));
        CIOT_ERR_PRINT(TAG, esp_wifi_connect());
        tcp->status.state = CIOT__TCP_STATE__TCP_STATE_CONNECTING;
        break;
    }
    case WIFI_EVENT_STA_STOP:
    {
        CIOT_LOGI(TAG, "WIFI_EVENT_STA_STOP");
        tcp->status.state = CIOT__TCP_STATE__TCP_STATE_STOPPED;
        // ciot_wifi_check_request(self, CIOT__MSG_TYPE__MSG_TYPE_STOP, &iface_event);
        break;
    }
    case WIFI_EVENT_STA_CONNECTED:
    {
        CIOT_LOGI(TAG, "WIFI_EVENT_STA_CONNECTED");
        wifi_event_sta_connected_t *data = (wifi_event_sta_connected_t *)event_data;
        tcp->status.state = CIOT__TCP_STATE__TCP_STATE_CONNECTED;
        tcp->status.conn_count++;
        base->status.disconnect_reason = 0;
        base->info.ap->authmode = data->authmode;
        memcpy(base->info.ap->bssid.data, data->bssid, sizeof(data->bssid));
        memcpy(base->info.ap->ssid, data->ssid, sizeof(data->ssid));
        CIOT_ERR_PRINT(TAG, ciot_tcp_start(base->tcp));
        break;
    }
    case WIFI_EVENT_STA_DISCONNECTED:
    {
        CIOT_LOGI(TAG, "WIFI_EVENT_STA_DISCONNECTED");
        wifi_event_sta_disconnected_t *data = (wifi_event_sta_disconnected_t *)event_data;
        tcp->status.state = CIOT__TCP_STATE__TCP_STATE_DISCONNECTED;
        base->status.disconnect_reason = data->reason;
        break;
    }
    default:
        break;
    }
}

// static void ciot_wifi_check_request(ciot_wifi_t self, ciot_msg_type_t req_type, ciot_iface_event_t *event)
// {
//     if(self->base.iface.req_status.type == req_type)
//     {
//         event->msg->type = req_type;
//     }
// }

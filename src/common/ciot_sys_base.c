/**
 * @file ciot_sys_cm.c
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-01-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdlib.h>
#include "ciot_sys.h"
#include "ciot_config.h"

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req);
static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg);
static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size);

static ciot_err_t ciot_sys_get_hw(ciot_sys_hw_t *hw);
static ciot_err_t ciot_sys_get_features(ciot_sys_features_t *features);

ciot_err_t ciot_sys_init(ciot_sys_t self)
{
    ciot_sys_base_t *base = (ciot_sys_base_t*)self;

    ciot_iface_init(&base->iface);
    ciot__sys_data__init(&base->data);
    ciot__sys_cfg__init(&base->cfg);
    ciot__sys_status__init(&base->status);
    ciot__sys_info__init(&base->info);
    ciot__sys_features__init(&base->features);
    ciot__sys_hw_features__init(&base->hw);
    ciot__sys_sw_features__init(&base->sw);

    base->iface.ptr = self;
    base->iface.process_req = ciot_iface_process_req;
    base->iface.get_data = ciot_iface_get_data;
    base->iface.send_data = ciot_iface_send_data;
    base->iface.info.type = CIOT__IFACE_TYPE__IFACE_TYPE_SYS;

    base->info.features = &base->features;
    base->info.features->hw = &base->hw;
    base->info.features->sw = &base->sw;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req)
{
    ciot_sys_t self = iface->ptr;

    switch (req->type)
    {
        case CIOT__MSG_TYPE__MSG_TYPE_START:
            return ciot_sys_start(self, req->data->sys->config);
        case CIOT__MSG_TYPE__MSG_TYPE_STOP:
            return ciot_sys_stop(self);
        case CIOT__MSG_TYPE__MSG_TYPE_REQUEST:
            return ciot_sys_process_req(self, req->data->sys->request);
    default:
        return CIOT_ERR__INVALID_TYPE;
    }
}

static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg)
{
    ciot_sys_base_t *self = iface->ptr;

    self->data.config = NULL;
    self->data.status = NULL;
    self->data.info = NULL;
    self->data.request = NULL;

    switch (msg->type)
    {
    case CIOT__MSG_TYPE__MSG_TYPE_CONFIG:
        self->data.config = &self->cfg;
        break;
    case CIOT__MSG_TYPE__MSG_TYPE_STATUS:
        self->data.status = &self->status;
        break;
    case CIOT__MSG_TYPE__MSG_TYPE_INFO:
        self->data.info = &self->info;
        ciot_sys_get_info((ciot_sys_t)self, self->data.info);
        break;
    default:
        break;
    }

    self->iface.data.sys = &self->data;
    msg->data = &self->iface.data;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    return CIOT_ERR__NOT_SUPPORTED;
}

ciot_err_t ciot_sys_process_req(ciot_sys_t self, ciot_sys_req_t *req)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(req);

    switch (req->type)
    {
    case CIOT__SYS_REQ_TYPE__SYS_REQ_TYPE_RESTART:
        return ciot_sys_restart();
    case CIOT__SYS_REQ_TYPE__SYS_REQ_TYPE_INIT_DFU:
        return ciot_sys_init_dfu();
    default:
        break;
    }

    return CIOT_ERR__NOT_SUPPORTED;
}

ciot_err_t ciot_sys_get_cfg(ciot_sys_t self, ciot_sys_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    ciot_sys_base_t *base = (ciot_sys_base_t*)self;
    *cfg = base->cfg;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_sys_get_status(ciot_sys_t self, ciot_sys_status_t *status)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(status);
    ciot_sys_base_t *base = (ciot_sys_base_t*)self;
    *status = base->status;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_sys_get_info(ciot_sys_t self, ciot_sys_info_t *info)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(info);

    static uint8_t app_ver[] = {CIOT_CONFIG_APP_VER};
    info->app_ver.data = app_ver;
    info->app_ver.len = sizeof(app_ver);
    info->hw_name = CIOT_CONFIG_HARDWARE_NAME;

    ciot_sys_get_hw(&info->hardware);
    if(info->features) ciot_sys_get_features(info->features);

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_sys_get_hw(ciot_sys_hw_t *hw)
{
    CIOT_ERR_NULL_CHECK(hw);
#if defined(ICACHE_FLASH) || defined(ICACHE_RAM_ATTR)
    *hw = CIOT__SYS_HW__SYS_HW_ESP8266;
#elif defined(_WIN32)
    *hw = CIOT__SYS_HW__SYS_HW_WIN32;
#elif defined(ARDUINO)
    *hw = CIOT__SYS_HW__SYS_HW_ARDUINO;
#elif defined(ESP_PLATFORM)
    *hw = CIOT__SYS_HW__SYS_HW_ESP32;
#elif defined(NRF51)
    *hw = CIOT__SYS_HW__SYS_HW_NRF51;
#elif defined(NRF52) || defined(NRF52840_XXAA)
    *hw = CIOT__SYS_HW__SYS_HW_NRF52;
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    *hw = CIOT__SYS_HW__SYS_HW_LINUX;
#else
    *hw = CIOT__SYS_HW__SYS_HW_UNKNOWN;
#endif
    return CIOT_ERR__OK;
}

static ciot_err_t ciot_sys_get_features(ciot_sys_features_t *features)
{
    CIOT_ERR_NULL_CHECK(features);
    CIOT_ERR_NULL_CHECK(features->hw);
    CIOT_ERR_NULL_CHECK(features->sw);

    features->hw->storage = CIOT_CONFIG_FEATURE_STORAGE;
    features->hw->sys = CIOT_CONFIG_FEATURE_SYSTEM;
    features->hw->uart = CIOT_CONFIG_FEATURE_UART;
    features->hw->usb = CIOT_CONFIG_FEATURE_USB;
    features->hw->ethernet = CIOT_CONFIG_FEATURE_ETHERNET;
    features->hw->wifi = CIOT_CONFIG_FEATURE_WIFI;
    features->hw->ble_scn = CIOT_CONFIG_FEATURE_BLE_SCN;
    features->hw->gpio = CIOT_CONFIG_FEATURE_GPIO;
    features->sw->ntp = CIOT_CONFIG_FEATURE_NTP;
    features->sw->ota = CIOT_CONFIG_FEATURE_OTA;
    features->sw->dfu = CIOT_CONFIG_FEATURE_DFU;
    features->sw->http_client = CIOT_CONFIG_FEATURE_HTTP_CLIENT;
    features->sw->http_server = CIOT_CONFIG_FEATURE_HTTP_SERVER;
    features->sw->mqtt_client = CIOT_CONFIG_FEATURE_MQTT_CLIENT;
    features->sw->timer = CIOT_CONFIG_FEATURE_TIMER;

    return CIOT_ERR__OK;
}

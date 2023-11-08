/**
 * @file ciot_sys.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "ciot_sys.h"

struct ciot_sys
{
    ciot_iface_t iface;
    ciot_sys_cfg_t cfg;
    ciot_sys_status_t status;
    time_t init_time;
};

static void ciot_sys_init(ciot_sys_t self);

ciot_sys_t ciot_sys_new(void *handle)
{
    ciot_sys_t self = calloc(1, sizeof(struct ciot_sys));
    self->iface.base.ptr = self;
    self->iface.base.start = (ciot_iface_start_fn *)ciot_sys_start;
    self->iface.base.stop = (ciot_iface_stop_fn *)ciot_sys_stop;
    self->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_sys_process_req;
    self->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_sys_send_data;
    self->iface.base.cfg.ptr = &self->cfg;
    self->iface.base.cfg.size = sizeof(self->cfg);
    self->iface.base.status.ptr = &self->status;
    self->iface.base.status.size = sizeof(ciot_sys_status_t);
    self->iface.info.type = CIOT_IFACE_TYPE_SYSTEM;
    ciot_sys_init(self);
    return self;
}

ciot_err_t ciot_sys_start(ciot_sys_t self, ciot_sys_cfg_t *cfg)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_sys_stop(ciot_sys_t self)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_sys_process_req(ciot_sys_t self, ciot_sys_req_t *req)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_sys_send_data(ciot_sys_t self, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

static void ciot_sys_init(ciot_sys_t self)
{
    char hw_name[] = CIOT_CONFIG_HARDWARE_NAME;
    uint8_t fw_ver[] = CIOT_CONFIG_FIRMWARE_VER;

    self->status.info.features.hw.storage = CIOT_CONFIG_FEATURE_STORAGE;
    self->status.info.features.hw.system = CIOT_CONFIG_FEATURE_SYSTEM;
    self->status.info.features.hw.uart = CIOT_CONFIG_FEATURE_UART;
    self->status.info.features.hw.usb = CIOT_CONFIG_FEATURE_USB;
    self->status.info.features.hw.ethernet = CIOT_CONFIG_FEATURE_ETHERNET;
    self->status.info.features.hw.wifi = CIOT_CONFIG_FEATURE_WIFI;
    self->status.info.features.hw.bluetooth = CIOT_CONFIG_FEATURE_BLE;
    
    self->status.info.features.sw.ntp = CIOT_CONFIG_FEATURE_NTP;
    self->status.info.features.sw.ota = CIOT_CONFIG_FEATURE_OTA;
    self->status.info.features.sw.http_client = CIOT_CONFIG_FEATURE_HTTPC;
    self->status.info.features.sw.http_server = CIOT_CONFIG_FEATURE_HTTPS;
    self->status.info.features.sw.mqtt_client = CIOT_CONFIG_FEATURE_MQTTC;

    self->status.rst_reason = 0;
    self->status.rst_count = 0;

    memcpy(self->status.info.hw_name, hw_name, sizeof(hw_name));
    memcpy(self->status.info.fw_ver, fw_ver, sizeof(fw_ver));
}

ciot_err_t ciot_sys_task(ciot_sys_t self)
{
    CIOT_NULL_CHECK(self);
    self->status.rst_reason = 0;
    self->status.rst_count = 0;
    self->status.free_memory = 0;
    self->status.lifetime = 0;
    return CIOT_OK;
}

/**
 * @file ciot_sys.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ciot_sys.h"
#include "ciot.h"

#if defined(CIOT_TARGET_MONGOOSE)
#include "mongoose.h"
struct mg_mgr mg;
#endif

#if CIOT_CONFIG_FEATURE_SYSTEM && defined(CIOT_TARGET_MONGOOSE)

#include <string.h>
#include <stdlib.h>

#ifdef CIOT_TARGET_WIN
#include <windows.h>
#elif defined(CIOT_TARGET_ESP8266) || defined(CIOT_TARGET_ESP32)
#include "esp_system.h"
#include "esp_event.h"
#endif  //_WIN32

struct ciot_sys
{
    ciot_iface_t iface;
    ciot_sys_cfg_t cfg;
    ciot_sys_status_t status;
    time_t init_time;
};

static ciot_sys_t sys;

static void ciot_sys_init(ciot_sys_t self);
static uint32_t ciot_sys_get_free_ram(void);

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

    #ifdef  CIOT_TARGET_ESP8266
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    #endif  //CIOT_TARGET_ESP8266

    sys = self;
    return self;
}

ciot_err_t ciot_sys_start(ciot_sys_t self, ciot_sys_cfg_t *cfg)
{
    sys->init_time = time(NULL);
    return CIOT_OK;
}

ciot_err_t ciot_sys_stop(ciot_sys_t self)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_sys_process_req(ciot_sys_t self, ciot_sys_req_t *req)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_sys_send_data(ciot_sys_t self, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_sys_rst(ciot_sys_t self)
{
    exit(0);
    return CIOT_OK;
}

ciot_err_t ciot_sys_task(ciot_sys_t self)
{
    CIOT_NULL_CHECK(self);
    sys->status.free_memory = ciot_sys_get_free_ram();
    sys->status.lifetime = time(NULL) - sys->init_time;
    mg_mgr_poll(CIOT_HANDLE, 10);
    return CIOT_OK;
}

ciot_err_t ciot_sys_set_event_bits(ciot_sys_t self, int event_bits)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

void ciot_sys_sleep(long ms)
{
    return Sleep(ms);
}

static void ciot_sys_init(ciot_sys_t self)
{
    char hw_name[] = CIOT_CONFIG_HARDWARE_NAME;
    uint8_t app_ver[] = { CIOT_CONFIG_APP_VER };

    ciot_sys_update_features(&self->status.info.features);
    
    self->status.rst_reason = 0;
    self->status.rst_count = 0;
    self->status.info.hardware = ciot_sys_get_hw();

    memcpy(self->status.info.hw_name, hw_name, sizeof(hw_name));
    memcpy(self->status.info.app_ver, app_ver, sizeof(app_ver));

    mg_mgr_init(CIOT_HANDLE);

    sys = self;
}

#if defined(CIOT_TARGET_ESP8266)

#include "esp_system.h"

static uint32_t ciot_sys_get_free_ram(void)
{
    return esp_get_free_heap_size();
}

#elif defined(CIOT_TARGET_WIN)

static uint32_t ciot_sys_get_free_ram(void)
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatusEx(&status);
    return (uint32_t)(status.ullAvailPhys / 1024);
}

#elif defined(CIOT_TARGET_LINUX)
static uint32_t ciot_sys_get_free_ram(void)
{
    FILE *meminfo = fopen("/proc/meminfo", "r");
    if (!meminfo) {
        perror("Error opening /proc/meminfo");
        return 0;
    }

    char line[128];
    uint32_t free_ram = 0;

    while (fgets(line, sizeof(line), meminfo)) {
        if (sscanf(line, "MemFree: %u kB", &free_ram) == 1) {
            break;
        }
    }

    fclose(meminfo);
    return free_ram * 1024;
}

#endif


#endif


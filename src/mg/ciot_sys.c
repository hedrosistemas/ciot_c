/**
 * @file ciot_sys.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "ciot_sys.h"
#include "ciot_err.h"
#include "ciot_timer.h"
#include "ciot_config.h"
#include "mongoose.h"

static const char *TAG = "ciot_sys";

struct ciot_sys
{
    ciot_sys_base_t base;
    time_t init_time;
};

static uint32_t ciot_sys_get_free_ram(void);

struct mg_mgr mg;

static ciot_sys_t sys;

ciot_sys_t ciot_sys_new(void *handle)
{
    ciot_sys_t self = calloc(1, sizeof(struct ciot_sys));
    ciot_sys_init(self);
    ciot_sys_get_info(self, &self->base.info);
    sys = self;
    mg_mgr_init(handle);
    return self;
}

ciot_err_t ciot_sys_start(ciot_sys_t self, ciot_sys_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    self->init_time = ciot_timer_now();
    return ciot_iface_send_event_type(&self->base.iface, CIOT_IFACE_EVENT_STARTED);
}

ciot_err_t ciot_sys_stop(ciot_sys_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    exit(0);
    return CIOT_ERR__OK;
}

ciot_err_t ciot_sys_task(ciot_sys_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    sys->base.status.free_memory = ciot_sys_get_free_ram();
    sys->base.status.lifetime = ciot_timer_now() - sys->init_time;
    mg_mgr_poll(CIOT_HANDLE, CIOT_CONFIG_MG_POOL_INTERVAL_MS);
    return CIOT_ERR__OK;
}

ciot_err_t ciot_sys_set_event_bits(ciot_sys_t self, int event_bits)
{
    return CIOT_ERR__NOT_SUPPORTED;
}

ciot_err_t ciot_sys_sleep(long ms)
{
    Sleep(ms);
    return CIOT_ERR__OK;
}

ciot_err_t ciot_sys_restart(void)
{
    return CIOT_ERR__NOT_SUPPORTED;
}

ciot_err_t ciot_sys_init_dfu(void)
{
    return CIOT_ERR__NOT_SUPPORTED;
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

#else

static uint32_t ciot_sys_get_free_ram(void)
{
    return 0;
}

#endif
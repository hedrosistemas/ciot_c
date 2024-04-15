/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdbool.h>

#include "ciot_log.h"
#include "iot_device.h"

static const char *TAG = "main";

int app_main(void)
{
    CIOT_LOGI(TAG, "Hardware Name: %s", CIOT_CONFIG_HARDWARE_NAME);
    CIOT_LOGI(TAG, "Version: %d.%d.%d", CIOT_CONFIG_APP_VER);

    iot_device_t device = iot_device_new();
    iot_device_start(device);

    while (true)
    {
        iot_device_task(device);
    }

    return 0;
}
/**
 * @file main.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-12-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __MAIN__H__
#define __MAIN__H__

#include "ciot.h"
#include "ciot_sys.h"
#include "ciot_config.h"

#define APP_CONFIG_SYSTEM \
    {                     \
    }

typedef enum app_iface
{
    APP_IFACE_SYS,
    APP_IFACE_COUNT,
} app_iface_t;

typedef struct app
{
    ciot_t ciot;
    ciot_sys_t sys;
    void *cfgs[APP_IFACE_COUNT];
    ciot_iface_t *ifaces[APP_IFACE_COUNT];
} app_t;

#endif //!__MAIN__H__

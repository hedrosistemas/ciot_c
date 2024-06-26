/**
 * @file ciot_n.h
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT__H__
#define __CIOT__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_err.h"
#include "ciot_iface.h"
#include "ciot_storage.h"
#include "ciot_bridge.h"

#ifdef CIOT_TARGET_MONGOOSE

extern struct mg_mgr mg;

#define CIOT_HANDLE &mg

#else

#define CIOT_HANDLE NULL

#endif

#ifdef CIOT_TARGET_NRF

#define app_main main

#endif

#ifdef  CIOT_TARGET_ARDUINO

#define app_main setup

#endif  //CIOT_TARGET_ARDUINO

typedef struct ciot *ciot_t;

typedef struct ciot_cfg
{
    ciot_iface_t **ifaces;
    void **cfgs;
    uint8_t count;
} ciot_cfg_t;

ciot_t ciot_new(void);
ciot_err_t ciot_start(ciot_t self, ciot_cfg_t *cfg);
ciot_err_t ciot_set_storage(ciot_t self, ciot_storage_t storage);
ciot_err_t ciot_register_event(ciot_t self, ciot_iface_event_handler_t event_handler, void *event_args);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT__H__
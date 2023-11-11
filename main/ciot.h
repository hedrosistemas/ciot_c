/**
 * @file ciot_n.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT__H__
#define __CIOT__H__

#include "ciot_err.h"
#include "ciot_iface.h"
#include "ciot_storage.h"

typedef struct ciot *ciot_t;

typedef enum ciot_state
{
    CIOT_STATE_IDLE,
    CIOT_STATE_BUSY,
    CIOT_STATE_ERROR,
} ciot_state_t; 

typedef struct ciot_cfg
{
    ciot_iface_t **ifaces;
    const void **cfgs;
    uint8_t count;
} ciot_cfg_t;

ciot_t ciot_new(void);
ciot_err_t ciot_start(ciot_t self, ciot_cfg_t *cfg);
ciot_err_t ciot_register_event(ciot_t self, ciot_iface_event_handler_t event_handler, void *event_args);

#endif  //!__CIOT__H__
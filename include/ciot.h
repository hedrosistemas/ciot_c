/**
 * @file ciot.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT__H__
#define __CIOT__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ciot_config.h"
#include "ciot_err.h"
#include "ciot_iface.h"
#include "ciot_msg.h"

typedef struct ciot *ciot_t; ///< CIOT network handle.

typedef struct ciot_cfg
{
    ciot_iface_t **ifaces; ///< Array of CIOT interfaces.
    ciot_msg_data_t **cfgs; ///< Array of configurations for the interfaces.
    uint8_t count; ///< Number of interfaces.
} ciot_cfg_t;

ciot_t ciot_new(void);
ciot_err_t ciot_start(ciot_t self, ciot_cfg_t *cfg);
ciot_err_t ciot_stop(ciot_t self);
ciot_err_t ciot_set_event_handler(ciot_t self, ciot_iface_event_handler_fn event_handler, void *event_args);
ciot_err_t ciot_task(ciot_t self);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT__H__

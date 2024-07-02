/**
 * @file ciot_usb.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "ciot_usb.h"
#include "ciot_err.h"

// static const char *TAG = "ciot_usb";

struct ciot_usb
{
    ciot_usb_base_t base;
};

ciot_usb_t ciot_usb_new(void *handle)
{
    ciot_usb_t self = calloc(1, sizeof(struct ciot_usb));
    ciot_usb_init(self);
    return self;
}

ciot_err_t ciot_usb_start(ciot_usb_t self, ciot_usb_cfg_t *cfg)
{
    return CIOT_ERR__NOT_SUPPORTED;
}

ciot_err_t ciot_usb_stop(ciot_usb_t self)
{
    return CIOT_ERR__NOT_SUPPORTED;
}

ciot_err_t ciot_usb_task(ciot_usb_t self)
{
    return CIOT_ERR__NOT_SUPPORTED;
}

ciot_err_t ciot_usb_send_bytes(ciot_iface_t *iface, uint8_t *bytes, int size)
{
    return CIOT_ERR__NOT_SUPPORTED;
}

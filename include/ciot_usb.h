/**
 * @file ciot_usb.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __CIOT_USB__H__
#define __CIOT_USB__H__

#include <stdbool.h>

#include "ciot_usb_types.h"
#include "ciot_iface.h"
#include "ciot_err.h"

typedef struct ciot_usb *ciot_usb_t;

typedef enum ciot_usb_event_id
{
    CIOT_USB_EVENT_DRV_SOF = CIOT_IFACE_EVENT_CUSTOM,
    CIOT_USB_EVENT_DRV_RESET,
    CIOT_USB_EVENT_DRV_SUSPEND,
    CIOT_USB_EVENT_DRV_RESUME,
    CIOT_USB_EVENT_DRV_WUREQ,
    CIOT_USB_EVENT_DRV_SETUP,
    CIOT_USB_EVENT_DRV_EPTRANSFER,
    CIOT_USB_EVENT_FIRST_POWER,
    CIOT_USB_EVENT_POWER_DETECTED,
    CIOT_USB_EVENT_POWER_REMOVED,
    CIOT_USB_EVENT_POWER_READY,
    CIOT_USB_EVENT_FIRST_APP,
    CIOT_USB_EVENT_INST_APPEND,
    CIOT_USB_EVENT_INST_REMOVE,
    CIOT_USB_EVENT_STARTED,
    CIOT_USB_EVENT_STOPPED,
    CIOT_USB_EVENT_STATE_CHANGED,
    CIOT_USB_EVENT_FIRST_INTERNAL,
    CIOT_USB_EVENT_HFCLK_READY,
    CIOT_USB_EVENT_START_REQ,
    CIOT_USB_EVENT_STOP_REQ,
    CIOT_USB_EVENT_SUSPEND_REQ,
    CIOT_USB_EVENT_WAKEUP_REQ,
    CIOT_USB_EVENT_SETUP_SETADDRESS,
    CIOT_USB_EVENT_DATA,
} ciot_usb_event_id_t;

ciot_usb_t ciot_usb_new(void *handle);
ciot_err_t ciot_usb_start(ciot_usb_t self, ciot_usb_cfg_t *cfg);
ciot_err_t ciot_usb_stop(ciot_usb_t self);
ciot_err_t ciot_usb_process_req(ciot_usb_t self, ciot_usb_req_t *req);
ciot_err_t ciot_usb_send_data(ciot_usb_t self, uint8_t *data, int size);
ciot_err_t ciot_usb_send_bytes(ciot_iface_t *iface, uint8_t *bytes, int size);
ciot_err_t ciot_usb_task(ciot_usb_t self);

#endif  //!__CIOT_USB__H__
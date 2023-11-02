/**
 * @file ciot_usb.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-11-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdlib.h>

#include "nrf_drv_usbd.h"
#include "nrf_drv_clock.h"

#include "app_error.h"
#include "app_util.h"
#include "app_usbd_core.h"
#include "app_usbd.h"
#include "app_usbd_string_desc.h"
#include "app_usbd_cdc_acm.h"
#include "app_usbd_serial_num.h"

#include "ciot_usb.h"
#include "ciot_s.h"

#define CDC_ACM_COMM_INTERFACE 0
#define CDC_ACM_COMM_EPIN NRF_DRV_USBD_EPIN2

#define CDC_ACM_DATA_INTERFACE 1
#define CDC_ACM_DATA_EPIN NRF_DRV_USBD_EPIN1
#define CDC_ACM_DATA_EPOUT NRF_DRV_USBD_EPOUT1

#ifndef USBD_POWER_DETECTION
#define USBD_POWER_DETECTION true
#endif

static ciot_err_t ciot_usb_on_message(void *user_ctx, uint8_t *data, int size);
static void ciot_usbd_event_handler(app_usbd_event_type_t event);
static void ciot_cdc_acm_event_handler(app_usbd_class_inst_t const *p_inst, app_usbd_cdc_acm_user_event_t event);

APP_USBD_CDC_ACM_GLOBAL_DEF(m_app_cdc_acm,
                            ciot_cdc_acm_event_handler,
                            CDC_ACM_COMM_INTERFACE,
                            CDC_ACM_DATA_INTERFACE,
                            CDC_ACM_COMM_EPIN,
                            CDC_ACM_DATA_EPIN,
                            CDC_ACM_DATA_EPOUT,
                            APP_USBD_CDC_COMM_PROTOCOL_AT_V250);

struct ciot_usb
{
    ciot_iface_t iface;
    ciot_uart_cfg_t cfg;
    ciot_uart_status_t status;
    ciot_s_t s;
    const app_usbd_class_inst_t *usb;
};

static ciot_usb_t usb;

ciot_usb_t ciot_usb_new(void *handle)
{
    ciot_usb_t self = calloc(1, sizeof(struct ciot_usb));
    self->iface.base.ptr = self;
    self->iface.base.start = (ciot_iface_start_fn *)ciot_usb_start;
    self->iface.base.stop = (ciot_iface_stop_fn *)ciot_usb_stop;
    self->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_usb_process_req;
    self->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_usb_send_data;
    self->iface.base.cfg.ptr = &self->cfg;
    self->iface.base.cfg.size = sizeof(self->cfg);
    self->iface.base.status.ptr = &self->status;
    self->iface.base.status.size = sizeof(self->status);
    self->iface.info.type = CIOT_IFACE_TYPE_USB;
    usb = self;

    ciot_s_cfg_t s_cfg = {
        .on_message_cb = ciot_usb_on_message,
        .send_bytes = ciot_usb_send_bytes,
        .user_ctx = self};
    self->s = ciot_s_new(&s_cfg);
    return self;
}

ciot_err_t ciot_usb_start(ciot_usb_t self, ciot_usb_cfg_t *cfg)
{
    ret_code_t ret;

    static const app_usbd_config_t usbd_config = {
        .ev_state_proc = ciot_usbd_event_handler,
    };

    ret = nrf_drv_clock_init();
    APP_ERROR_CHECK(ret);

    nrf_drv_clock_lfclk_request(NULL);

    while (!nrf_drv_clock_lfclk_is_running())
    {
        // wait...
    }

    // ret = app_timer_init();
    // APP_ERROR_CHECK(ret);

    app_usbd_serial_num_generate();

    ret = app_usbd_init(&usbd_config);
    APP_ERROR_CHECK(ret);

    self->usb = app_usbd_cdc_acm_class_inst_get(&m_app_cdc_acm);
    ret = app_usbd_class_append(self->usb);
    APP_ERROR_CHECK(ret);

    if (USBD_POWER_DETECTION)
    {
        ret = app_usbd_power_events_enable();
        APP_ERROR_CHECK(ret);
    }
    else
    {
        app_usbd_enable();
        app_usbd_start();
    }

    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_usb_stop(ciot_usb_t self)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_usb_process_req(ciot_usb_t self, ciot_usb_req_t *req)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_usb_send_data(ciot_usb_t self, uint8_t *data, int size)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(data);
    return ciot_s_send(self->s, data, size);
}

ciot_err_t ciot_usb_send_bytes(void *user_ctx, uint8_t *bytes, int size)
{
    ciot_usb_t self = (ciot_usb_t)user_ctx;
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(bytes);
    ret_code_t ret = app_usbd_cdc_acm_write(&m_app_cdc_acm, bytes, size);
    if (ret != NRF_SUCCESS)
    {
        return CIOT_FAIL;
    }
    else
    {
        return CIOT_OK;
    }
}

bool ciot_usb_event_queue_process()
{
    return app_usbd_event_queue_process();
}

static ciot_err_t ciot_usb_on_message(void *user_ctx, uint8_t *data, int size)
{
    ciot_usb_t self = (ciot_usb_t)user_ctx;
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(data);
    CIOT_NULL_CHECK(self->iface.event_handler);
    ciot_iface_event_t event = {0};
    event.id = CIOT_IFACE_EVENT_DATA;
    memcpy(&event.msg, data, size);
    event.size = size;
    return self->iface.event_handler(self, &event, self->iface.event_args);
}

static void ciot_usbd_event_handler(app_usbd_event_type_t event)
{
    ciot_usb_t self = usb;
    ciot_iface_event_t ciot_evt = {0};

    ciot_evt.msg.type = CIOT_MSG_TYPE_EVENT;
    ciot_evt.msg.iface = self->iface.info;

    switch (event)
    {
    case APP_USBD_EVT_POWER_DETECTED:
        if (!nrf_drv_usbd_is_enabled())
        {
            app_usbd_enable();
        }
        ciot_evt.id = CIOT_USB_EVENT_POWER_DETECTED;
        break;
    case APP_USBD_EVT_POWER_REMOVED:
        app_usbd_stop();
        ciot_evt.id = CIOT_USB_EVENT_POWER_REMOVED;
        break;
    case APP_USBD_EVT_POWER_READY:
        app_usbd_start();
        ciot_evt.id = CIOT_IFACE_EVENT_STARTED;
        break;
    case APP_USBD_EVT_STOPPED:
        app_usbd_disable();
        ciot_evt.id = CIOT_IFACE_EVENT_STOPPED;
        break;
    default:
        ciot_evt.id = event + CIOT_IFACE_EVENT_CUSTOM;
        break;
    }

    if (self->iface.event_handler != NULL)
    {
        self->iface.event_handler(self, &ciot_evt, self->iface.event_args);
    }
}

static void ciot_cdc_acm_event_handler(app_usbd_class_inst_t const *p_inst, app_usbd_cdc_acm_user_event_t event)
{
    ciot_usb_t self = usb;
    ciot_iface_event_t ciot_evt = {0};
    // app_usbd_cdc_acm_t const *p_cdc_acm = app_usbd_cdc_acm_class_get(p_inst);

    ciot_evt.msg.type = CIOT_MSG_TYPE_EVENT;
    ciot_evt.msg.iface = self->iface.info;

    switch (event)
    {
    case APP_USBD_CDC_ACM_USER_EVT_RX_DONE:
    {
        ret_code_t ret;
        uint8_t byte;
        do
        {
            // size_t size = app_usbd_cdc_acm_rx_size(p_cdc_acm);
            ret = app_usbd_cdc_acm_read(&m_app_cdc_acm, &byte, 1);
            ret = ciot_s_process_byte(self->s, byte);
            if (ret != CIOT_OK)
            {
                self->status.error = ret;
                self->status.state = CIOT_UART_STATE_CIOT_S_ERROR;
            }
        } while (ret == NRF_SUCCESS);
        return;
    }
    case APP_USBD_CDC_ACM_USER_EVT_PORT_OPEN:
    {
        uint8_t byte;
        app_usbd_cdc_acm_read(&m_app_cdc_acm, &byte, 1);
        ret_code_t ret = ciot_s_process_byte(self->s, byte);
        if (ret != CIOT_OK)
        {
            self->status.error = ret;
            self->status.state = CIOT_UART_STATE_CIOT_S_ERROR;
        }
        return;
    }
    default:
        ciot_evt.id = event + CIOT_IFACE_EVENT_CUSTOM;
        break;
    }

    if (self->iface.event_handler != NULL)
    {
        self->iface.event_handler(self, &ciot_evt, self->iface.event_args);
    }
}

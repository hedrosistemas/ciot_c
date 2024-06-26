/**
 * @file ciot_usb.c
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "ciot_usb.h"

#if CIOT_CONFIG_FEATURE_USB && defined(CIOT_TARGET_NRF)

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
#include "app_fifo.h"

#include "ciot_s.h"

#define CDC_ACM_COMM_INTERFACE 0
#define CDC_ACM_COMM_EPIN NRF_DRV_USBD_EPIN2

#define CDC_ACM_DATA_INTERFACE 1
#define CDC_ACM_DATA_EPIN NRF_DRV_USBD_EPIN1
#define CDC_ACM_DATA_EPOUT NRF_DRV_USBD_EPOUT1

static ciot_err_t ciot_usb_on_message(ciot_iface_t *iface, uint8_t *data, int size);
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

typedef struct ciot_usb_fifo
{
    app_fifo_t tx;
    uint8_t tx_buf[CIOT_CONFIG_UART_TX_BUF_SIZE];
} ciot_usb_fifo_t;

struct ciot_usb
{
    ciot_iface_t iface;
    ciot_usb_cfg_t cfg;
    ciot_usb_status_t status;
    ciot_s_t s;
    ciot_usb_fifo_t fifo;
    uint8_t rx_byte[1];
    uint8_t tx_byte[1];
    bool tx_in_progress;
    const app_usbd_class_inst_t *usb;
};

static ciot_usb_t usb;

#if CIOT_CONFIG_FEATURE_TIMER
static const char *TAG = "ciot_usb";
#endif

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
        .iface = &self->iface};
    self->s = ciot_s_new(&s_cfg);
    return self;
}

ciot_err_t ciot_usb_start(ciot_usb_t self, ciot_usb_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);

    ret_code_t ret;

    self->cfg = *cfg;

    ret = app_fifo_init(&self->fifo.tx, self->fifo.tx_buf, CIOT_CONFIG_UART_TX_BUF_SIZE);
    VERIFY_SUCCESS(ret);

    static const app_usbd_config_t usbd_config = {
        .ev_state_proc = ciot_usbd_event_handler,
    };
    ciot_s_set_bridge_mode(self->s, self->cfg.bridge_mode);

    ret = nrf_drv_clock_init();
    if(ret != NRF_ERROR_MODULE_ALREADY_INITIALIZED)
    {
        APP_ERROR_CHECK(ret);
    }

    nrf_drv_clock_lfclk_request(NULL);

    while (!nrf_drv_clock_lfclk_is_running())
    {
        // wait...
    }

    app_usbd_serial_num_generate();

    ret = app_usbd_init(&usbd_config);
    APP_ERROR_CHECK(ret);

    self->usb = app_usbd_cdc_acm_class_inst_get(&m_app_cdc_acm);
    ret = app_usbd_class_append(self->usb);
    APP_ERROR_CHECK(ret);

    // #if APP_USBD_CONFIG_POWER_EVENTS_PROCESS
    // ret = app_usbd_power_events_enable();
    // APP_ERROR_CHECK(ret);
    // #else
    // app_usbd_enable();
    // app_usbd_start();
    // #endif  //APP_USBD_CONFIG_POWER_EVENTS_PROCESS

    self->tx_in_progress = false;

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

ciot_err_t ciot_usb_send_bytes(ciot_iface_t *iface, uint8_t *bytes, int size)
{
    CIOT_NULL_CHECK(iface);
    CIOT_NULL_CHECK(bytes);
    
    uint32_t err_code;
    uint32_t len = 0;
    ciot_usb_t self = (ciot_usb_t)iface;

    err_code = app_fifo_write(&self->fifo.tx, NULL, &len);
    err_code = len < size ? CIOT_ERR_OVERFLOW : CIOT_OK;
    if(err_code == CIOT_OK)
    {
        len = size;
        err_code = app_fifo_write(&self->fifo.tx, bytes, &len);
    }
    if(!self->tx_in_progress)
    {
        self->tx_in_progress = true;
        if(app_fifo_get(&self->fifo.tx, self->tx_byte) == NRF_SUCCESS) 
        {
            err_code = app_usbd_cdc_acm_write(&m_app_cdc_acm, self->tx_byte, 1);
        }
    }

    return err_code;
}

ciot_err_t ciot_usb_set_bridge_mode(ciot_usb_t self, bool mode)
{
    CIOT_NULL_CHECK(self);
    return ciot_s_set_bridge_mode(self->s, mode);
}

ciot_err_t ciot_usb_task(ciot_usb_t self)
{
    CIOT_NULL_CHECK(self);
    
    if(self->status.state == CIOT_USB_STATE_STOPPED)
    {
        app_usbd_enable();
        app_usbd_start();
    }

    app_usbd_event_queue_process();

    ciot_err_t err = CIOT_OK;
#if CIOT_CONFIG_FEATURE_TIMER
    err = ciot_s_check_timeout(self->s);
    if (err != CIOT_OK)
    {
        CIOT_LOGE(TAG, "[%d]:%s %s[%d]", self->iface.info.id, ciot_iface_to_str(&self->iface), ciot_err_to_message(err), err);
    }
#endif
    return err;
}

static ciot_err_t ciot_usb_on_message(ciot_iface_t *iface, uint8_t *data, int size)
{
    CIOT_NULL_CHECK(iface);
    CIOT_NULL_CHECK(data);
    CIOT_NULL_CHECK(iface->event_handler);
    ciot_usb_t self = (ciot_usb_t)iface;
    ciot_iface_event_t ciot_evt = { 0 };
    
    ciot_evt.type = self->cfg.bridge_mode ? CIOT_IFACE_EVENT_DATA : CIOT_IFACE_EVENT_REQUEST;
    ciot_evt.data = (ciot_iface_event_data_u*)data;
    ciot_evt.size = size;
    return iface->event_handler(iface, &ciot_evt, iface->event_args);
}

static void ciot_usbd_event_handler(app_usbd_event_type_t event)
{
    ciot_usb_t self = usb;

    if (self == NULL) return;

    ciot_iface_event_t iface_event = {0};

    switch (event)
    {
    case APP_USBD_EVT_POWER_DETECTED:
        if (!nrf_drv_usbd_is_enabled())
        {
            self->tx_in_progress = false;
            app_usbd_enable();
        }
        iface_event.type = CIOT_USB_EVENT_POWER_DETECTED;
        break;
    case APP_USBD_EVT_POWER_REMOVED:
        app_usbd_stop();
        self->tx_in_progress = false;
        iface_event.type = CIOT_USB_EVENT_POWER_REMOVED;
        break;
    case APP_USBD_EVT_POWER_READY:
        app_usbd_start();
        self->tx_in_progress = false;
        iface_event.type = CIOT_IFACE_EVENT_STARTED;
        break;
    case APP_USBD_EVT_STARTED:
        self->status.state = CIOT_USB_STATE_STARTED;
        break;
    case APP_USBD_EVT_STOPPED:
        app_usbd_disable();
        self->status.state = CIOT_USB_STATE_STOPPED;
        self->tx_in_progress = false;
        iface_event.type = CIOT_IFACE_EVENT_STOPPED;
        break;
    default:
        return;
    }

    if (self->iface.event_handler != NULL)
    {
        self->iface.event_handler(&self->iface, &iface_event, self->iface.event_args);
    }
}

static void ciot_cdc_acm_event_handler(app_usbd_class_inst_t const *p_inst, app_usbd_cdc_acm_user_event_t event)
{
    ciot_usb_t self = usb;

    switch (event)
    {
    case APP_USBD_CDC_ACM_USER_EVT_RX_DONE:
    {
        ret_code_t ret;
        do
        {
            ciot_err_t err = ciot_s_process_byte(self->s, self->rx_byte[0]);
            if (err != CIOT_OK)
            {
                ciot_msg_t msg = {0};
                msg.iface = self->iface.info;
                msg.data.usb.status.state = ciot_iface_send_msg(&self->iface, &msg, CIOT_MSG_HEADER_SIZE);
            }
            ret = app_usbd_cdc_acm_read(&m_app_cdc_acm,
                                        self->rx_byte,
                                        1);
        } while (ret == NRF_SUCCESS);
        break;
    }
    case APP_USBD_CDC_ACM_USER_EVT_TX_DONE:
    {
        if (app_fifo_get(&self->fifo.tx, self->tx_byte) == NRF_SUCCESS)
        {
            app_usbd_cdc_acm_write(&m_app_cdc_acm, self->tx_byte, 1);
        }
        else
        {
            self->tx_in_progress = false;
        }
        break;
    }
    case APP_USBD_CDC_ACM_USER_EVT_PORT_OPEN:
    {
        self->tx_in_progress = false;
        app_usbd_cdc_acm_read(&m_app_cdc_acm, &self->rx_byte, 1);
        break;
    }
    default:
        break;
    }
}

#endif

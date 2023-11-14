/**
 * @file ciot_uart.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-31
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "ciot_uart.h"

#if (CIOT_CONFIG_FEATURE_UART && APP_FIFO_ENABLED == 0) && defined(CIOT_TARGET_NRF)

#include <stdlib.h>

#include "sdk_common.h"
#include "nrf_drv_uart.h"
#include "app_util_platform.h"

#include "ciot_s.h"

struct ciot_uart
{
    ciot_iface_t iface;
    ciot_uart_cfg_t cfg;
    ciot_uart_status_t status;
    ciot_s_t s;
    nrf_drv_uart_t uart;
};

static ciot_err_t ciot_uart_on_message(ciot_iface_t *iface, uint8_t *data, int size);

ciot_uart_t ciot_uart_new(void *handle)
{
    ciot_uart_t self = calloc(1, sizeof(struct ciot_uart));
    self->iface.base.ptr = self;
    self->iface.base.start = (ciot_iface_start_fn *)ciot_uart_start;
    self->iface.base.stop = (ciot_iface_stop_fn *)ciot_uart_stop;
    self->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_uart_process_req;
    self->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_uart_send_data;
    self->iface.base.cfg.ptr = &self->cfg;
    self->iface.base.cfg.size = sizeof(self->cfg);
    self->iface.base.status.ptr = &self->status;
    self->iface.base.status.size = sizeof(self->status);
    self->iface.info.type = CIOT_IFACE_TYPE_UART;

    ciot_s_cfg_t s_cfg = {
        .on_message_cb = ciot_uart_on_message,
        .send_bytes = ciot_uart_send_bytes,
        .iface = &self->iface
    };
    self->s = ciot_s_new(&s_cfg);
    return self;
}

ciot_err_t ciot_uart_start(ciot_uart_t self, ciot_uart_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);
    uint32_t err_code;
    self->cfg = *cfg;

    nrf_drv_uart_config_t config = NRF_DRV_UART_DEFAULT_CONFIG;
    config.baudrate = (nrf_uart_baudrate_t)self->cfg.baud_rate;
    config.hwfc = self->cfg.flow_control;
    config.interrupt_priority = APP_IRQ_PRIORITY_LOWEST;
    config.parity = self->cfg.parity;
    config.pselcts = self->cfg.cts_pin;
    config.pselrts = self->cfg.rts_pin;
    config.pselrxd = self->cfg.rx_pin;
    config.pseltxd = self->cfg.tx_pin;
    config.p_context = self;
    ciot_s_set_bridge_mode(self->s, self->cfg.bridge_mode);

    switch (cfg->num)
    {
#if UART0_ENABLED
    case 0:
        {
            nrf_drv_uart_t uart_inst = NRF_DRV_UART_INSTANCE(0);
            self->uart = uart_inst;
            break;
        }
#endif
#if UART1_ENABLED
    case 1:
        {
            nrf_drv_uart_t uart_inst = NRF_DRV_UART_INSTANCE(1);
            self->uart = uart_inst;
            break;
        }
#endif
    default:
        return CIOT_ERR_INVALID_ARG;
    }

    err_code = nrf_drv_uart_init(&self->uart, &config, NULL);
    VERIFY_SUCCESS(err_code);

    // if (self->cfg.rx_pin != UART_PIN_DISCONNECTED)
    // {
    //     uint8_t buf[1];
    //     return nrf_drv_uart_rx(&self->uart, buf, 1);
    // }
    // else
    // {
    //     return NRF_SUCCESS;
    // }

    return CIOT_OK;
}

ciot_err_t ciot_uart_stop(ciot_uart_t self)
{
    nrf_drv_uart_uninit(&self->uart);
    return NRF_SUCCESS;
}

ciot_err_t ciot_uart_send_data(ciot_uart_t self, uint8_t *data, int size)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(data);
    return ciot_s_send(self->s, data, size);
}

ciot_err_t ciot_uart_send_bytes(ciot_iface_t *iface, uint8_t *bytes, int size)
{
    CIOT_NULL_CHECK(iface);
    CIOT_NULL_CHECK(bytes);
    ciot_uart_t self = (ciot_uart_t)iface;
    ret_code_t ret = nrf_drv_uart_tx(&self->uart, bytes, size);
    if (NRF_ERROR_BUSY == ret)
    {
        return CIOT_ERR_NO_MEMORY;
    }
    else if (ret != NRF_SUCCESS)
    {
        return CIOT_FAIL;
    }
    else
    {
        return CIOT_OK;
    }
}

ciot_err_t ciot_uart_task(ciot_uart_t self)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

// static void ciot_uart_event_handler(nrf_drv_uart_event_t *event, void *context)
// {
//     ciot_uart_t self = (ciot_uart_t)context;
//     ciot_iface_event_t ciot_evt = { 0 };
//     uint32_t err_code;

//     ciot_evt.msg.type = CIOT_MSG_TYPE_EVENT;
//     ciot_evt.msg.iface = self->iface.info;

//     switch (event->type)
//     {
//         case NRF_DRV_UART_EVT_RX_DONE:
//             // If 0, then this is a RXTO event with no new bytes.
//             if(event->data.rxtx.bytes == 0)
//             {
//                // A new start RX is needed to continue to receive data
//                (void)nrf_drv_uart_rx(&self->uart, self->rx_byte, 1);
//                break;
//             }

//             // Write received byte to FIFO.
//             err_code = app_fifo_put(&self->fifo.rx, event->data.rxtx.p_data[0]);
//             if (err_code != NRF_SUCCESS)
//             {
//                 // app_uart_event.evt_type          = APP_UART_FIFO_ERROR;
//                 // app_uart_event.data.error_code   = err_code;
//                 // m_event_handler(&app_uart_event);
//             }
//             // Notify that there are data available.
//             else if (FIFO_LENGTH(self->fifo.rx) != 0)
//             {
//                 // app_uart_event.evt_type = APP_UART_DATA_READY;
//                 // m_event_handler(&app_uart_event);
//             }

//             // Start new RX if size in buffer.
//             if (FIFO_LENGTH(self->fifo.rx) <= self->fifo.rx.buf_size_mask)
//             {
//                 (void)nrf_drv_uart_rx(&self->uart, self->rx_byte, 1);
//             }
//             else
//             {
//                 // Overflow in RX FIFO.
//                 self->fifo.rx_ovf = true;
//             }

//             break;

//         case NRF_DRV_UART_EVT_ERROR:
//             // app_uart_event.evt_type                 = APP_UART_COMMUNICATION_ERROR;
//             // app_uart_event.data.error_communication = event->data.error.error_mask;
//             // (void)nrf_drv_uart_rx(&self->uart, self->rx_byte, 1);
//             // m_event_handler(&app_uart_event);
//             break;

//         case NRF_DRV_UART_EVT_TX_DONE:
//             // Get next byte from FIFO.
//             if (app_fifo_get(&self->fifo.tx, self->tx_byte) == NRF_SUCCESS)
//             {
//                 (void)nrf_drv_uart_tx(&self->uart, self->tx_byte, 1);
//             }
//             else
//             {
//                 // Last byte from FIFO transmitted, notify the application.
//                 // app_uart_event.evt_type = APP_UART_TX_EMPTY;
//                 // m_event_handler(&app_uart_event);
//             }
//             break;

//         default:
//             break;
//     }
// }

#endif

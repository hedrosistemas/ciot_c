/**
 * @file ciot_uart.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "stdio.h"

#include "ciot_s.h"
#include "ciot_uart.h"

#include "windows.h"

struct ciot_uart
{
    ciot_iface_t iface;
    ciot_uart_cfg_t cfg;
    ciot_uart_status_t status;
    ciot_s_t s;
    HANDLE handle;
};

static ciot_err_t ciot_uart_on_message(ciot_s_t s, char *data, int size);
static void ciot_uart_event_handler(void *args);

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
        .handler = self
    };
    self->s = ciot_s_new(&s_cfg);

    return self;
}

ciot_err_t ciot_uart_start(ciot_uart_t self, ciot_uart_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(cfg);

    char port_name[10];

    self->cfg = *cfg;
    
    sprintf(port_name, "\\\\.\\COM%d", self->cfg.num);
}

ciot_err_t ciot_uart_stop(ciot_uart_t self)
{

}

ciot_err_t ciot_uart_process_req(ciot_uart_t self, ciot_uart_req_t *req)
{

}

ciot_err_t ciot_uart_send_data(ciot_uart_t self, uint8_t *data, int size)
{

}

static ciot_err_t ciot_uart_on_message(ciot_s_t s, char *data, int size)
{

}

static void ciot_uart_event_handler(void *args)
{

}

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

#ifdef _WIN32

#include <stdbool.h>

#include "stdio.h"

#include "ciot_s.h"
#include "ciot_uart.h"
#include "ciot_log.h"

#include "windows.h"

#if CIOT_CONFIG_FEATURE_UART

struct ciot_uart
{
    ciot_iface_t iface;
    ciot_uart_cfg_t cfg;
    ciot_uart_status_t status;
    ciot_s_t s;
    HANDLE handle;
    DCB params;
    COMMTIMEOUTS timeouts;
    DWORD bytes_written;
    DWORD bytes_read;
    char port_name[10];
};

static ciot_err_t ciot_uart_init(ciot_uart_t self);
static ciot_err_t ciot_uart_on_message(ciot_iface_t *iface, uint8_t *data, int size);
static void ciot_uart_process_error(ciot_uart_t self, DWORD error);
static ciot_err_t ciot_uart_process_status(ciot_uart_t self, COMSTAT *status);

static const char *TAG = "ciot_uart";

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
        .iface = (ciot_iface_t*)self,
    };
    self->s = ciot_s_new(&s_cfg);

    return self;
}

ciot_err_t ciot_uart_start(ciot_uart_t self, ciot_uart_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(cfg);

    self->cfg = *cfg;
    sprintf(self->port_name, "\\\\.\\COM%d", self->cfg.num);

    self->handle = CreateFile(self->port_name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if(self->handle == INVALID_HANDLE_VALUE)
    {
        CIOT_LOGE(TAG, "Unable to open serial port %s", self->port_name);
        self->status.state = CIOT_UART_STATE_INTERNAL_ERROR;
        return CIOT_FAIL;
    }

    self->params.DCBlength = sizeof(self->params);
    if(!GetCommState(self->handle, &self->params))
    {
        CIOT_LOGE(TAG, "GetCommState failed", "");
        CloseHandle(self->handle);
        self->status.state = CIOT_UART_STATE_INTERNAL_ERROR;
        return CIOT_FAIL;
    }

    return ciot_uart_init(self);
}

ciot_err_t ciot_uart_stop(ciot_uart_t self)
{
    CIOT_LOGI(TAG, "UART_CLOSE port: %s", self->port_name);
    CloseHandle(self->handle);
    return CIOT_OK;
}

ciot_err_t ciot_uart_process_req(ciot_uart_t self, ciot_uart_req_t *req)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_uart_send_data(ciot_uart_t self, uint8_t *data, int size)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(data);
    return ciot_s_send(self->s, (char*)data, size);
}

ciot_err_t ciot_uart_send_bytes(ciot_iface_t *iface, uint8_t *bytes, int size)
{
    ciot_uart_t self = (ciot_uart_t)iface;
    CIOT_NULL_CHECK(self);
    if(self->status.state == CIOT_UART_STATE_STARTED)
    {
        CIOT_NULL_CHECK(bytes);
        WriteFile(self->handle, bytes, size, &self->bytes_written, NULL);
        return CIOT_OK;
    }
    else
    {
        CIOT_LOGE(TAG, "Port %s is closed", self->port_name);
        return CIOT_ERR_INVALID_STATE;
    }
}

static ciot_err_t ciot_uart_on_message(ciot_iface_t *iface, uint8_t *data, int size)
{
    ciot_uart_t self = (ciot_uart_t)iface;
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(data);
    CIOT_NULL_CHECK(self->iface.event_handler);
    ciot_iface_event_t event = { 0 };
    event.id = CIOT_IFACE_EVENT_DATA;
    memcpy(&event.msg, data, size);
    event.size = size;
    return self->iface.event_handler(&self->iface, &event, self->iface.event_args);
}

static ciot_err_t ciot_uart_init(ciot_uart_t self)
{
    CIOT_NULL_CHECK(self);
    self->params.BaudRate = self->cfg.baud_rate;
    self->params.ByteSize = 8;
    self->params.StopBits = ONE5STOPBITS;
    self->params.Parity = self->cfg.parity;
    self->params.fDtrControl = self->cfg.dtr;
    if(SetCommState(self->handle, &self->params) == FALSE)
    {
        CIOT_LOGE(TAG, "SetCommState error", "");
        return CIOT_FAIL;
    }

    self->timeouts.ReadIntervalTimeout = 50;
    self->timeouts.ReadTotalTimeoutConstant = 50;
    self->timeouts.ReadTotalTimeoutMultiplier = 10;
    self->timeouts.WriteTotalTimeoutConstant = 50;
    self->timeouts.WriteTotalTimeoutMultiplier = 10;
    if(SetCommTimeouts(self->handle, &self->timeouts) == FALSE)
    {
        CIOT_LOGE(TAG, "SetCommTimeouts error", "");
        return CIOT_FAIL;
    }

    return CIOT_OK;
}

ciot_err_t ciot_uart_task(ciot_uart_t self)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(self->handle);

    DWORD error;
    COMSTAT status;
    ClearCommError(self->handle, &error, &status);

    ciot_uart_process_error(self, error);
    return ciot_uart_process_status(self, &status);
}

static void ciot_uart_process_error(ciot_uart_t self, DWORD error)
{
    if(self->status.state == CIOT_UART_STATE_CLOSED && error == 0)
    {
        ciot_iface_event_t ciot_evt = { 0 };
        self->status.state = CIOT_UART_STATE_STARTED;
        ciot_evt.id = CIOT_IFACE_EVENT_STARTED;
        ciot_evt.msg.iface = self->iface.info;
        ciot_evt.msg.data.uart.status = self->status;
        if(self->iface.event_handler != NULL)
        {
            self->iface.event_handler(&self->iface, &ciot_evt, self->iface.event_args);
        }
        CIOT_LOGI(TAG, "UART_OPEN port:%s", self->port_name);
    }

    if(self->status.state == CIOT_UART_STATE_STARTED && error == CE_FRAME)
    {
        ciot_iface_event_t ciot_evt = { 0 };
        self->status.state = CIOT_UART_STATE_CLOSED;
        ciot_evt.id = CIOT_IFACE_EVENT_STOPPED;
        ciot_evt.msg.iface = self->iface.info;
        ciot_evt.msg.data.uart.status = self->status;
        if(self->iface.event_handler != NULL)
        {
            self->iface.event_handler(&self->iface, &ciot_evt, self->iface.event_args);
        }
        CIOT_LOGI(TAG, "UART_CLOSED port:%s", self->port_name);
    }
}

static ciot_err_t ciot_uart_process_status(ciot_uart_t self, COMSTAT *status)
{
    if(self->status.state != CIOT_UART_STATE_STARTED)
    {
        return CIOT_ERR_INVALID_STATE;
    }

    if(status->cbInQue > 0)
    {
        uint8_t byte;
        while (status->cbInQue > 0)
        {
            if(ReadFile(self->handle, &byte, 1, &self->bytes_read, NULL))
            {
                ciot_err_t err = ciot_s_process_byte(self->s, byte);
                if(err != CIOT_OK)
                {
                    CIOT_LOGE(TAG, "Error %d processing byte %d", err, byte);
                }
            }
            status->cbInQue--;
        }
    }
}

#endif

#endif

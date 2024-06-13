/**
 * @file ciot_uart.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "windows.h"
#include "ciot_uart.h"
#include "ciot_msg.h"
#include "ciot_err.h"

static const char *TAG = "ciot_uart";

struct ciot_uart
{
    ciot_uart_base_t base;
    HANDLE handle;
    DCB params;
    COMMTIMEOUTS timeouts;
    DWORD bytes_written;
    DWORD bytes_read;
    char port_name[10];
};

static void ciot_uart_process_error(ciot_uart_t self, DWORD error);
static ciot_err_t ciot_uart_process_status(ciot_uart_t self, COMSTAT *status);

ciot_uart_t ciot_uart_new(void *handle)
{
    ciot_uart_t self = calloc(1, sizeof(struct ciot_uart));
    ciot_uart_init(self);
    return self;
}

ciot_err_t ciot_uart_start(ciot_uart_t self, ciot_uart_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);

    ciot_uart_base_t *base = &self->base;

    base->cfg = *cfg;

    sprintf(self->port_name, "\\\\.\\COM%d", base->cfg.num);

    self->handle = CreateFile(self->port_name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if(self->handle == INVALID_HANDLE_VALUE)
    {
        CIOT_LOGE(TAG, "Unable to open serial port COM%d", base->cfg.num);
        base->status.state = CIOT__UART_STATE__UART_STATE_INTERNAL_ERROR;
        base->status.error = CIOT__UART_ERROR__UART_ERR_OPEN;
        ciot_iface_send_event_type(&base->iface, CIOT_IFACE_EVENT_STOPPED);
        return CIOT_ERR__FAIL;
    }

    self->params.DCBlength = sizeof(self->params);
    if(!GetCommState(self->handle, &self->params))
    {
        CIOT_LOGE(TAG, "GetCommState failed at COM%d", base->cfg.num);
        base->status.state = CIOT__UART_STATE__UART_STATE_INTERNAL_ERROR;
        base->status.error = CIOT__UART_ERROR__UART_ERR_OPEN;
        ciot_iface_send_event_type(&base->iface, CIOT_IFACE_EVENT_STOPPED);
        return CIOT_ERR__FAIL;
    }

    self->params.BaudRate = base->cfg.baud_rate;
    self->params.ByteSize = 8;
    self->params.StopBits = ONESTOPBIT;
    self->params.fDtrControl = base->cfg.dtr;
    if(!SetCommState(self->handle, &self->params) == FALSE)
    {
        CIOT_LOGE(TAG, "SetCommState error at COM%d", base->cfg.num);
        base->status.state = CIOT__UART_STATE__UART_STATE_INTERNAL_ERROR;
        base->status.error = CIOT__UART_ERROR__UART_ERR_OPEN;
        ciot_iface_send_event_type(&base->iface, CIOT_IFACE_EVENT_STOPPED);
        return CIOT_ERR__FAIL;
    }

    self->timeouts.ReadIntervalTimeout = 50;
    self->timeouts.ReadTotalTimeoutConstant = 50;
    self->timeouts.ReadTotalTimeoutMultiplier = 20;
    self->timeouts.WriteTotalTimeoutConstant = 50;
    self->timeouts.WriteTotalTimeoutMultiplier = 20;
    if(!SetCommTimeouts(self->handle, &self->timeouts))
    {
        CIOT_LOGE(TAG, "SetCommTimeouts error at CO%d", base->cfg.num);
        base->status.state = CIOT__UART_STATE__UART_STATE_INTERNAL_ERROR;
        base->status.error = CIOT__UART_ERROR__UART_ERR_OPEN;
        ciot_iface_send_event_type(&base->iface, CIOT_IFACE_EVENT_STOPPED);
        return CIOT_ERR__FAIL;
    }

    base->status.state = CIOT__UART_STATE__UART_STATE_STARTED;
    ciot_iface_send_event_type(&base->iface, CIOT_IFACE_EVENT_STARTED);

    return CIOT_ERR__OK;
}

ciot_err_t ciot_uart_stop(ciot_uart_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    CloseHandle(self->handle);
    return CIOT_ERR__OK;
}

ciot_err_t ciot_uart_task(ciot_uart_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(self->handle);

    DWORD error;
    COMSTAT status;
    ClearCommError(self->handle, &error, &status);

    ciot_uart_process_error(self, error);
    ciot_uart_process_status(self, &status);

    return CIOT_ERR__OK;
}

ciot_err_t ciot_uart_send_bytes(ciot_uart_t self, uint8_t *bytes, int size)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(bytes);

    ciot_uart_base_t *base = &self->base;

    if(base->status.state == CIOT__UART_STATE__UART_STATE_STARTED)
    {
        WriteFile(self->handle, bytes, size, &self->bytes_written, NULL);
        return CIOT_ERR__OK;
    }
    else
    {
        CIOT_LOGE(TAG, "Port COM%d is closed", base->cfg.num);
        return CIOT_ERR__INVALID_STATE;
    }
}

static void ciot_uart_process_error(ciot_uart_t self, DWORD error)
{
    ciot_uart_base_t base = self->base;

    if(base.status.state == CIOT__UART_STATE__UART_STATE_CLOSED && error == 0)
    {
        ciot_iface_event_t iface_event = { 0 };
        base.status.state = CIOT__UART_STATE__UART_STATE_STARTED;
        iface_event.type = CIOT_IFACE_EVENT_STARTED;
        iface_event.msg = ciot_msg_get(CIOT__MSG_TYPE__MSG_TYPE_STATUS, &base.iface);
        ciot_iface_send_event(&base.iface, &iface_event);
        CIOT_LOGI(TAG, "UART_OPEN port:%s", self->port_name);
    }

    if(base.status.state == CIOT__UART_STATE__UART_STATE_STARTED && error == CE_FRAME)
    {
        ciot_iface_event_t iface_event = { 0 };
        base.status.state = CIOT__UART_STATE__UART_STATE_CLOSED;
        iface_event.type = CIOT_IFACE_EVENT_STOPPED;
        iface_event.msg = ciot_msg_get(CIOT__MSG_TYPE__MSG_TYPE_STATUS, &base.iface);
        ciot_iface_send_event(&base.iface, &iface_event);
        CIOT_LOGI(TAG, "UART_CLOSED port:%s", self->port_name);
    }
}

static ciot_err_t ciot_uart_process_status(ciot_uart_t self, COMSTAT *status)
{
    ciot_uart_base_t base = self->base;

    if(base.status.state != CIOT__UART_STATE__UART_STATE_STARTED)
    {
        return CIOT_ERR__INVALID_STATE;
    }

    if(status->cbInQue > 0)
    {
        uint8_t byte;
        while (status->cbInQue > 0)
        {
            if(ReadFile(self->handle, &byte, 1, &self->bytes_read, NULL))
            {
                if(base.decoder != NULL)
                {
                    ciot_err_t err = base.decoder->decode(base.decoder, byte);
                    if(err != CIOT_ERR__OK)
                    {
                        CIOT_LOGE(TAG, "Error %s processing byte %d", ciot_err_to_message(err), byte);
                    }
                }
                else
                {
                    ciot_iface_event_t iface_event = {0};
                    iface_event.data = &byte;
                    iface_event.size = 1;
                    ciot_iface_send_event(&base.iface, &iface_event);
                }
            }
            status->cbInQue--;
        }
    }

    return CIOT_ERR__OK;
}
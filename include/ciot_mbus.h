/**
 * @file ciot_mbus.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-02-11
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "nanomodbus.h"
#include "ciot_iface.h"

typedef struct ciot_mbus_base
{
    ciot_iface_t *iface;
    uint8_t recv_buf[256];
    uint16_t available;
} ciot_mbus_base_t;

static int32_t read_serial(uint8_t *buf, uint16_t count, int32_t byte_timeout_ms, void *arg);
static int32_t write_serial(const uint8_t *buf, uint16_t count, int32_t byte_timeout_ms, void *arg);
static ciot_err_t ciot_mbus_event_handler(ciot_iface_t *sender, ciot_event_t *event, void *args);

ciot_err_t ciot_mbus_init(ciot_mbus_base_t *self)
{
    self->iface->event_handler = ciot_mbus_event_handler;
}

static int32_t read_serial(uint8_t *buf, uint16_t count, int32_t byte_timeout_ms, void *arg)
{
    ciot_mbus_base_t *base = arg;
    uint16_t available = base->available;
    if(available)
    {
        memcpy(buf, base->recv_buf, available);
        base->available = 0;
    }
    return available;
}

static int32_t write_serial(const uint8_t *buf, uint16_t count, int32_t byte_timeout_ms, void *arg)
{
    ciot_iface_t *iface = arg;
    return iface->send_data(iface, (uint8_t*)buf, (int)count);
}

static ciot_err_t ciot_mbus_event_handler(ciot_iface_t *sender, ciot_event_t *event, void *args)
{
    ciot_mbus_base_t *base = args;
    if(event->type == CIOT_EVENT_TYPE_DATA)
    {
        memcpy(&base->recv_buf[base->available], event->raw.bytes, event->raw.size);
    }
    return CIOT_ERR_OK;
}

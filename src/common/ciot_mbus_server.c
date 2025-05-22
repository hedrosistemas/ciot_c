/**
 * @file ciot_mbus_server.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-12-11
 *
 * @copyright Copyright (c) 2024
 *
 */
 
#include "ciot_config.h"

#if CIOT_CONFIG_FEATURE_MBUS_SERVER == 1

#include "ciot_mbus_server.h"
#include <stdlib.h>

struct ciot_mbus_server
{
    ciot_mbus_server_base_t base;
    ciot_iface_t *iface;
    nmbs_t nmbs;
};

static int32_t ciot_mbus_server_read(uint8_t *buf, uint16_t count, int32_t byte_timeout_ms, void *arg);
static int32_t ciot_mbus_server_write(const uint8_t *buf, uint16_t count, int32_t byte_timeout_ms, void *arg);
static nmbs_error ciot_mbus_server_read_coils(uint16_t address, uint16_t quantity, nmbs_bitfield coils_out, uint8_t unit_id, void *arg);
static nmbs_error ciot_mbus_server_write_multiple_coils(uint16_t address, uint16_t quantity, const nmbs_bitfield coils, uint8_t unit_id, void *arg);
static nmbs_error ciot_mbus_server_read_holding_registers(uint16_t address, uint16_t quantity, uint16_t *registers_out, uint8_t unit_id, void *arg);
static nmbs_error ciot_mbus_server_write_multiple_registers(uint16_t address, uint16_t quantity, const uint16_t *registers, uint8_t unit_id, void *arg);
static ciot_err_t ciot_mbus_server_get_error(nmbs_error error);

static const char *TAG = "ciot_mbus_server";

ciot_mbus_server_t ciot_mbus_server_new(void *handle, ciot_mbus_data_t *data, ciot_iface_t *iface)
{
    if(data == NULL) {
        CIOT_LOGE(TAG, "data is null");
        return NULL;
    }
    if(iface == NULL) {
        CIOT_LOGE(TAG, "iface is null");
        return NULL;
    }
    ciot_mbus_server_t self = calloc(1, sizeof(struct ciot_mbus_server));
    ciot_mbus_server_init(self);
    self->base.data = *data;
    self->iface = iface;
    return self;
}

ciot_err_t ciot_mbus_server_start(ciot_mbus_server_t self, ciot_mbus_server_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);

    nmbs_platform_conf platform_conf;
    nmbs_platform_conf_create(&platform_conf);
    platform_conf.read = ciot_mbus_server_read;
    platform_conf.write = ciot_mbus_server_write;
    platform_conf.arg = self;

    nmbs_callbacks callbacks;
    nmbs_callbacks_create(&callbacks);
    callbacks.arg = self;
    callbacks.read_coils = ciot_mbus_server_read_coils;
    callbacks.write_multiple_coils = ciot_mbus_server_write_multiple_coils;
    callbacks.read_holding_registers = ciot_mbus_server_read_holding_registers;
    callbacks.write_multiple_registers = ciot_mbus_server_write_multiple_registers;

    nmbs_error err = 0;
    switch (cfg->which_type)
    {
    case CIOT_MBUS_SERVER_CFG_RTU_TAG:
        platform_conf.transport = NMBS_TRANSPORT_RTU;
        break;
    case CIOT_MBUS_SERVER_CFG_TCP_TAG:
        platform_conf.transport = NMBS_TRANSPORT_TCP;
        break;
    default:
        return CIOT_ERR_INVALID_ARG;
    }

    err = nmbs_server_create(&self->nmbs, cfg->rtu.server_id, &platform_conf, &callbacks);
    if (err == NMBS_ERROR_NONE)
    {
        self->base.status.state = CIOT_MBUS_SERVER_STATE_STARTED;
        ciot_iface_send_event_type(&self->base.iface, CIOT_EVENT_TYPE_STARTED);
    }
    else
    {
        self->base.status.state = CIOT_MBUS_SERVER_STATE_ERROR;
        ciot_iface_send_event_type(&self->base.iface, CIOT_EVENT_TYPE_ERROR);
    }

    return ciot_mbus_server_get_error(err);
}

ciot_err_t ciot_mbus_server_stop(ciot_mbus_server_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_mbus_server_task(ciot_mbus_server_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    if (self->base.status.state == CIOT_MBUS_SERVER_STATE_STARTED && self->iface->state == CIOT_IFACE_STATE_STARTED)
    {
        nmbs_error err = nmbs_server_poll(&self->nmbs);
        return err != NMBS_ERROR_NONE ? ciot_mbus_server_get_error(err) : CIOT_ERR_OK;
    }
    return CIOT_ERR_OK;
}

ciot_err_t ciot_mbus_server_send_bytes(ciot_mbus_server_t self, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_mbus_server_set_reg(ciot_mbus_server_t self, uint16_t addr, void *data, uint16_t size)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_INDEX_CHECK(addr, (uint16_t)0, self->base.data.regs.count - size);
    memcpy(&self->base.data.regs.values[addr], data, size);
    return CIOT_ERR_OK;
}

ciot_err_t ciot_mbus_server_get_reg(ciot_mbus_server_t self, uint16_t addr, void *data, uint16_t size)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_INDEX_CHECK(addr, (uint16_t)0, self->base.data.regs.count - size);
    memcpy(data, &self->base.data.regs.values[addr], size);
    return CIOT_ERR_OK;
}

static int32_t ciot_mbus_server_read(uint8_t *buf, uint16_t count, int32_t byte_timeout_ms, void *arg)
{
    ciot_mbus_server_t self = (ciot_mbus_server_t)arg;
    return ciot_iface_read_bytes(self->iface, buf, count);
    // return self->iface->read_data(self->iface, buf, count);
}

static int32_t ciot_mbus_server_write(const uint8_t *buf, uint16_t count, int32_t byte_timeout_ms, void *arg)
{
    ciot_mbus_server_t self = (ciot_mbus_server_t)arg;
    return ciot_iface_send_bytes(self->iface, (uint8_t*)buf, count);
    // return self->iface->send_data(self->iface, (uint8_t *)buf, count);
}

static nmbs_error ciot_mbus_server_read_coils(uint16_t address, uint16_t quantity, nmbs_bitfield coils_out, uint8_t unit_id, void *arg)
{
    ciot_mbus_server_t self = (ciot_mbus_server_t)arg;

    if (address + quantity > self->base.data.coils.count)
    {
        return CIOT_ERR_MBUS_EXCEPTION_ILLEGAL_DATA_ADDR;
    }

    for (size_t i = 0; i < quantity; i++)
    {
        bool value = nmbs_bitfield_read(self->base.data.coils.values, address + i);
        nmbs_bitfield_write(coils_out, i, value);
    }

    return CIOT_ERR_OK;
}

static nmbs_error ciot_mbus_server_write_multiple_coils(uint16_t address, uint16_t quantity, const nmbs_bitfield coils, uint8_t unit_id, void *arg)
{
    ciot_mbus_server_t self = (ciot_mbus_server_t)arg;

    if (address + quantity > self->base.data.coils.count)
    {
        return CIOT_ERR_MBUS_EXCEPTION_ILLEGAL_DATA_ADDR;
    }

    for (int i = 0; i < quantity; i++)
    {
        nmbs_bitfield_write(self->base.data.coils.values, address + i, nmbs_bitfield_read(coils, i));
    }

    return CIOT_ERR_OK;
}

static nmbs_error ciot_mbus_server_read_holding_registers(uint16_t address, uint16_t quantity, uint16_t *registers_out, uint8_t unit_id, void *arg)
{
    ciot_mbus_server_t self = (ciot_mbus_server_t)arg;

    if (address + quantity > self->base.data.regs.count)
    {
        return CIOT_ERR_MBUS_EXCEPTION_ILLEGAL_DATA_ADDR;
    }

    for (size_t i = 0; i < quantity; i++)
    {
        registers_out[i] = self->base.data.regs.values[address + i];
    }

    return CIOT_ERR_OK;
}

static nmbs_error ciot_mbus_server_write_multiple_registers(uint16_t address, uint16_t quantity, const uint16_t *registers, uint8_t unit_id, void *arg)
{
    ciot_mbus_server_t self = (ciot_mbus_server_t)arg;

    if (address + quantity > self->base.data.regs.count)
    {
        return CIOT_ERR_MBUS_EXCEPTION_ILLEGAL_DATA_ADDR;
    }

    for (size_t i = 0; i < quantity; i++)
    {
        self->base.data.regs.values[address + i] = registers[i];
    }

    return CIOT_ERR_OK;
}

static ciot_err_t ciot_mbus_server_get_error(nmbs_error error)
{
    switch (error)
    {
    case NMBS_ERROR_INVALID_REQUEST:
        return CIOT_ERR_INVALID_REQUEST;
    case NMBS_ERROR_INVALID_UNIT_ID:
        return CIOT_ERR_INVALID_ID;
    case NMBS_ERROR_INVALID_TCP_MBAP:
        return CIOT_ERR_INVALID_TCP_MBAP;
    case NMBS_ERROR_CRC:
        return CIOT_ERR_CRC;
    case NMBS_ERROR_TRANSPORT:
        return CIOT_ERR_TRANSPORT;
    case NMBS_ERROR_TIMEOUT:
        return CIOT_ERR_TIMEOUT;
    case NMBS_ERROR_INVALID_RESPONSE:
        return CIOT_ERR_INVALID_RESPONSE;
    case NMBS_ERROR_INVALID_ARGUMENT:
        return CIOT_ERR_INVALID_ARG;
    case NMBS_ERROR_NONE:
        return CIOT_ERR_OK;
    case NMBS_EXCEPTION_ILLEGAL_FUNCTION:
        return CIOT_ERR_MBUS_EXCEPTION_ILLEGAL_FUNCTION;
    case NMBS_EXCEPTION_ILLEGAL_DATA_ADDRESS:
        return CIOT_ERR_MBUS_EXCEPTION_ILLEGAL_DATA_ADDR;
    case NMBS_EXCEPTION_ILLEGAL_DATA_VALUE:
        return CIOT_ERR_MBUS_EXCEPTION_ILLEGAL_DATA_ADDR;
    case NMBS_EXCEPTION_SERVER_DEVICE_FAILURE:
        return CIOT_ERR_MBUS_EXCEPTION_SERVER_DEVICE_FAILURE;
    default:
        return CIOT_ERR_UNKNOWN;
    }
}

ciot_err_t ciot_mbus_server_event_handler(ciot_mbus_server_t self, ciot_iface_t *sender, ciot_event_t *event)
{
    if(sender->info.id == self->iface->info.id)
    {
        switch (event->type)
        {
        case CIOT_EVENT_TYPE_STOPPED:
            CIOT_LOGI(TAG, "CIOT_MBUS_SERVER_STATE_STOPPED");
            self->base.status.state = CIOT_MBUS_SERVER_STATE_STOPPED;
            break;
        case CIOT_EVENT_TYPE_ERROR:
            CIOT_LOGI(TAG, "CIOT_MBUS_SERVER_STATE_ERROR");
            self->base.status.state = CIOT_MBUS_SERVER_STATE_ERROR;
            break;
        default:
            break;
        }
        return ciot_iface_send_event_type(&self->base.iface, event->type);
}

#endif // CIOT_CONFIG_FEATURE_MBUS_SERVER == 1
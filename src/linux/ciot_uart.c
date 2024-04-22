/**
 * @file ciot_uart.c
 * @brief
 * @version 0.1
 * @date 2023-10-30
 * @copyright Copyright (c) 2023
 */

#include "ciot_uart.h"

#if CIOT_CONFIG_FEATURE_UART && defined(CIOT_TARGET_LINUX)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <errno.h>

#include "ciot_log.h"

struct ciot_uart
{
    ciot_uart_base_t uart;
    int fd;
    char port_name[20];
    struct termios tty;
};

static ciot_err_t ciot_uart_init(ciot_uart_t self);
ciot_err_t ciot_uart_task_internal(ciot_iface_t *iface, ciot_s_t ciot_s);

ciot_err_t ciot_uart_on_message(ciot_iface_t *iface, uint8_t *data, int size);

static const char *TAG = "ciot_uart";

ciot_uart_t ciot_uart_new(void *handle)
{
    ciot_uart_t self = calloc(1, sizeof(struct ciot_uart));
    self->uart.iface.base.ptr = self;
    self->uart.iface.base.start = (ciot_iface_start_fn *)ciot_uart_start;
    self->uart.iface.base.stop = (ciot_iface_stop_fn *)ciot_uart_stop;
    self->uart.iface.base.process_req = (ciot_iface_process_req_fn *)ciot_uart_process_req;
    self->uart.iface.base.send_data = (ciot_iface_send_data_fn *)ciot_uart_send_data;
    self->uart.iface.base.cfg.ptr = &self->uart.cfg;
    self->uart.iface.base.cfg.size = sizeof(self->uart.cfg);
    self->uart.iface.base.status.ptr = &self->uart.status;
    self->uart.iface.base.status.size = sizeof(self->uart.status);
    self->uart.iface.info.type = CIOT_IFACE_TYPE_UART;

    ciot_s_cfg_t s_cfg = {
        .on_message_cb = ciot_uart_on_message,
        .send_bytes = ciot_uart_send_bytes,
        .iface = (ciot_iface_t*)self,
    };
    self->uart.s = ciot_s_new(&s_cfg);

    return self;
}

ciot_err_t ciot_uart_start(ciot_uart_t self, ciot_uart_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(cfg);

    self->uart.cfg = *cfg;
    sprintf(self->port_name, "/dev/ttyS%d", self->uart.cfg.num); // Assuming ttyS for UART

    self->fd = open(self->port_name, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if(self->fd < 0)
    {
        CIOT_LOGE(TAG, "Unable to open serial port %s: %s", self->port_name, strerror(errno));
        self->uart.status.state = CIOT_UART_STATE_INTERNAL_ERROR;
        return CIOT_FAIL;
    }

    if(tcgetattr(self->fd, &self->tty) != 0)
    {
        CIOT_LOGE(TAG, "Error on tcgetattr");
        return CIOT_FAIL;
    }

    cfsetospeed(&self->tty, self->uart.cfg.baud_rate);
    cfsetispeed(&self->tty, self->uart.cfg.baud_rate);

    // cfmakeraw(&self->uart.cfg.termios); // Set raw mode
    // cfsetospeed(&self->uart.cfg.termios, self->uart.cfg.baud_rate);
    // cfsetispeed(&self->uart.cfg.termios, self->uart.cfg.baud_rate);

    if(tcsetattr(self->fd, TCSANOW, &self->tty) < 0)
    {
        CIOT_LOGE(TAG, "Error setting serial port attributes: %s", strerror(errno));
        close(self->fd);
        self->uart.status.state = CIOT_UART_STATE_INTERNAL_ERROR;
        return CIOT_FAIL;
    }

    ciot_s_set_bridge_mode(self->uart.s, self->uart.cfg.bridge_mode);
    ciot_err_t err = ciot_uart_init(self);
    if(err != CIOT_OK)
    {
        CIOT_LOGE(TAG, "Error initializing UART: %s", ciot_err_to_message(err));
    }
    return err;
}

ciot_err_t ciot_uart_stop(ciot_uart_t self)
{
    CIOT_LOGI(TAG, "UART_CLOSE port: %s", self->port_name);
    close(self->fd);
    return CIOT_OK;
}

ciot_err_t ciot_uart_send_data(ciot_uart_t self, uint8_t *data, int size)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(data);
    return ciot_s_send(self->uart.s, (char*)data, size);
}

ciot_err_t ciot_uart_send_bytes(ciot_iface_t *iface, uint8_t *bytes, int size)
{
    ciot_uart_t self = (ciot_uart_t)iface;
    CIOT_NULL_CHECK(self);
    if(self->uart.status.state == CIOT_UART_STATE_STARTED)
    {
        CIOT_NULL_CHECK(bytes);
        ssize_t bytes_written = write(self->fd, bytes, size);
        if(bytes_written < 0)
        {
            CIOT_LOGE(TAG, "Error writing to serial port %s: %s", self->port_name, strerror(errno));
            return CIOT_FAIL;
        }
        return CIOT_OK;
    }
    else
    {
        CIOT_LOGE(TAG, "Port %s is closed", self->port_name);
        return CIOT_ERR_INVALID_STATE;
    }
}

ciot_err_t ciot_uart_set_bridge_mode(ciot_uart_t self, bool mode)
{
    CIOT_NULL_CHECK(self);
    return ciot_s_set_bridge_mode(self->uart.s, mode);
}

static ciot_err_t ciot_uart_init(ciot_uart_t self)
{
    // No additional initialization needed for Linux
    return CIOT_OK;
}

ciot_err_t ciot_uart_task(ciot_uart_t self)
{
    CIOT_NULL_CHECK(self);

    uint8_t byte;
    if(read(self->fd, &byte, 1))
    {
        ciot_err_t err = ciot_s_process_byte(self->uart.s, byte);
        if(err != CIOT_OK)
        {
            CIOT_LOGE(TAG, "Error %s processing byte %d", ciot_err_to_message(err), byte);
        }
    }

    ciot_uart_task_internal(&self->uart.iface, self->uart.s);
    return CIOT_OK;
}

#endif

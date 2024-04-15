/**
 * @file ciot_nrf_dfu.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// #if CIOT_CONFIG_FEATURE_DFU

#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>

#include "ciot_config.h"
#include "ciot_dfu.h"
#include "ciot_slip.h"

typedef enum ciot_nrf_dfu_state
{
    CIOT_NRF_DFU_STATE_IDLE,
    CIOT_NRF_DFU_STATE_WAITING_PING_RESP,
    CIOT_NRF_DFU_STATE_WAITING_CREATE_OBJ,
    CIOT_NRF_DFU_STATE_WAITING_CRC,
    CIOT_NRF_DFU_STATE_WAITING_EXCECUTE,
    CIOT_NRF_DFU_STATE_COMPLETED,
} ciot_nrf_dfu_state_t;

typedef struct ciot_dfu_crc
{
    uint32_t expected;
    uint32_t received;
} ciot_dfu_crc_t;

typedef struct ciot_dfu_msg
{
    uint32_t size;
    uint8_t data[32];
    ciot_dfu_crc_t crc;
} ciot_dfu_msg_t;

struct ciot_dfu
{
    ciot_iface_t iface;
    ciot_dfu_cfg_t cfg;
    ciot_dfu_status_t status;
    ciot_dfu_msg_t msg;
    ciot_nrf_dfu_state_t state;
};

static const char *TAG = "ciot_nrf_dfu";

ciot_dfu_t ciot_dfu_new(void *handle)
{
    ciot_dfu_t self = calloc(1, sizeof(struct ciot_dfu));
    self->iface.base.ptr = self;
    self->iface.base.start = (ciot_iface_start_fn *)ciot_dfu_start;
    self->iface.base.stop = (ciot_iface_stop_fn *)ciot_dfu_stop;
    self->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_dfu_process_req;
    self->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_dfu_send_data;
    self->iface.base.cfg.ptr = &self->cfg;
    self->iface.base.cfg.size = sizeof(self->cfg);
    self->iface.base.status.ptr = &self->status;
    self->iface.base.status.size = sizeof(self->status);
    self->iface.info.type = CIOT_IFACE_TYPE_DFU;
    return self;
}

ciot_err_t ciot_dfu_start(ciot_dfu_t self, ciot_dfu_cfg_t *cfg)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_dfu_stop(ciot_dfu_t self)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_dfu_process_req(ciot_dfu_t self, ciot_dfu_req_t *req)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_dfu_send_data(ciot_dfu_t self, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

void ciot_dfu_process_msg(ciot_dfu_t self)
{
    int idx = 0;

    // Print received message
    if(CIOT_CONFIG_LOG_LEVEL == CIOT_LOG_LEVEL_DEBUG)
    {
        char msg[128];
        for (size_t i = 0; i < self->msg.size; i++)
        {
            idx += sprintf(&msg[idx], "%x ", self->msg.data[i]);
        }
        msg[idx] = '\0';
        CIOT_LOGD(TAG, "Received: %s", msg);
    }

    // Ping response
    if(self->state == CIOT_NRF_DFU_STATE_WAITING_PING_RESP &&
       self->msg.data[0] == 0x60 &&
       self->msg.data[1] == 0x09 &&
       self->msg.data[2] == 0x01 &&
       self->msg.data[3] == 0x01 &&
       self->msg.data[4] == 0xc0)
    {
        CIOT_LOGI(TAG, "Ping Response Received");
        // event ping resp recv
    }   
}

// #endif

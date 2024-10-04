/**
 * @file ciot_dfu_nrf.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-06-07
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "ciot_dfu_nrf.h"
#include "ciot_config.h"
#include "ciot_sys.h"
#include "ciot_msg.h"
#include "ciot_utils.h"
#include "ciot_timer.h"

static const char *TAG = "ciot_dfu_nrf";

#define MAX_OBJECT_SIZE 4096
#define PING_ID 0x01
#define TIMEOUT_RESET 2
#define PKT_SET_PRN_PARAM_LEN (32)

typedef struct ciot_dfu_nrf_object
{
    uint32_t size;
    uint32_t remaining;
    ciot_dfu_nrf_packet_t *packet;
} ciot_dfu_nrf_object_t;

typedef struct ciot_dfu_nrf_crc
{
    uint32_t expected;
    uint32_t received;
} ciot_dfu_nrf_crc_t;

struct ciot_dfu_nrf
{
    ciot_dfu_t base;
    ciot_dfu_nrf_cfg_t cfg;

    uint8_t decoder_buf[256];
    ciot_iface_decoder_t decoder;

    ciot_dfu_nrf_state_t state;
    ciot_dfu_nrf_state_t last_state;
    ciot_dfu_nrf_crc_t crc;
    uint8_t data[CIOT_DFU_NRF_MAX_DFU_PKT_LEN_UART];
    uint32_t prn_counter;
    uint32_t data_transferred;
    ciot_dfu_nrf_object_t object;
    bool ping_refused;

    uint64_t timer;
};

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req);
static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg);
static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size);

static ciot_err_t ciot_dfu_nrf_set_state(ciot_dfu_nrf_t self, ciot_dfu_state_t state);
static ciot_err_t ciot_dfu_nrf_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args);
static ciot_err_t ciot_dfu_nrf_write(ciot_dfu_nrf_t self);
static ciot_err_t ciot_dfu_nrf_process_data(ciot_dfu_nrf_t self, uint8_t *data, int size);

ciot_dfu_nrf_t ciot_dfu_nrf_new(ciot_dfu_nrf_cfg_t *cfg)
{
    ciot_dfu_nrf_t self = calloc(1, sizeof(struct ciot_dfu_nrf));
    ciot_dfu_nrf_init(self);
    self->prn_counter = 0;
    self->cfg = *cfg;
    self->cfg.init_packet.type = CIOT_DFU_NRF_PACKET_TYPE_INIT;
    self->cfg.app_image.type = CIOT_DFU_NRF_PACKET_TYPE_APP_IMAGE;
    self->object.packet = &self->cfg.init_packet;
    self->decoder = ciot_decoder_slip_new(self->decoder_buf, sizeof(self->decoder_buf));
    self->decoder->event_type = CIOT_IFACE_EVENT_DATA;
    return self;
}

ciot_err_t ciot_dfu_nrf_start(ciot_dfu_nrf_t self, ciot_dfu_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_STATE_CHECK(self->base.status.state, CIOT__DFU_STATE__DFU_STATE_IDLE);

    if (cfg->type != self->cfg.dfu.type)
    {
        return CIOT_ERR__INVALID_TYPE;
    }

    self->state = CIOT_DFU_NRF_STATE_IDLE;
    ciot_dfu_nrf_set_state(self, CIOT__DFU_STATE__DFU_STATE_STARTING);
    ciot_iface_set_decoder(self->cfg.iface, self->decoder);
    ciot_iface_set_event_handler(self->cfg.iface, ciot_dfu_nrf_event_handler, self);

    ciot_msg_t msg = {
        .type = CIOT__MSG_TYPE__MSG_TYPE_START,
        .data = self->cfg.iface_cfg};
    self->base.status.error = self->cfg.iface->process_req(self->cfg.iface, &msg);

    return self->base.status.error;
}

ciot_err_t ciot_dfu_nrf_stop(ciot_dfu_nrf_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    ciot_iface_set_event_handler(self->cfg.iface, NULL, NULL);
    self->cfg.iface->req_status.state = CIOT_IFACE_REQ_STATE_IDLE;
    self->prn_counter = 0;
    self->data_transferred = 0;
    self->crc.expected = 0;
    self->crc.received = 0;
    self->object.packet = &self->cfg.init_packet;

    ciot_msg_t msg = {
        .type = CIOT__MSG_TYPE__MSG_TYPE_STOP,
    };
    self->cfg.iface->process_req(self->cfg.iface, &msg);

    return CIOT_ERR__OK;
}

ciot_err_t ciot_dfu_nrf_init(ciot_dfu_nrf_t self)
{
    ciot_dfu_t *base = (ciot_dfu_t *)&self->base;

    ciot_iface_init(&base->iface);
    ciot__dfu_data__init(&base->data);
    ciot__dfu_cfg__init(&base->cfg);
    ciot__dfu_status__init(&base->status);

    base->iface.ptr = self;
    base->iface.process_req = ciot_iface_process_req;
    base->iface.get_data = ciot_iface_get_data;
    base->iface.send_data = ciot_iface_send_data;
    base->iface.info.type = CIOT__IFACE_TYPE__IFACE_TYPE_DFU;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req)
{
    ciot_dfu_nrf_t self = iface->ptr;

    switch (req->type)
    {
    case CIOT__MSG_TYPE__MSG_TYPE_START:
        return ciot_dfu_nrf_start(self, req->data->dfu->config);
    case CIOT__MSG_TYPE__MSG_TYPE_STOP:
        return ciot_dfu_nrf_stop(self);
    case CIOT__MSG_TYPE__MSG_TYPE_REQUEST:
        return ciot_dfu_nrf_process_req(self, req->data->dfu->request);
    default:
        break;
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg)
{
    ciot_dfu_t *self = iface->ptr;

    self->data.config = NULL;
    self->data.status = NULL;
    self->data.request = NULL;

    switch (msg->type)
    {
    case CIOT__MSG_TYPE__MSG_TYPE_CONFIG:
        self->data.config = &self->cfg;
        break;
    case CIOT__MSG_TYPE__MSG_TYPE_STATUS:
        self->data.status = &self->status;
        break;
    case CIOT__MSG_TYPE__MSG_TYPE_INFO:
        break;
    default:
        break;
    }

    self->iface.data.dfu = &self->data;
    msg->data = &self->iface.data;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    CIOT_ERR_NULL_CHECK(iface);
    CIOT_ERR_NULL_CHECK(data);
    ciot_dfu_nrf_t self = (ciot_dfu_nrf_t)iface;
    // ciot_iface_t *destiny = self->cfg.iface;
    return self->decoder->send(self->cfg.iface, data, size);
}

ciot_err_t ciot_dfu_nrf_process_req(ciot_dfu_nrf_t self, ciot_dfu_req_t *req)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(req);
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_dfu_nrf_get_cfg(ciot_dfu_nrf_t self, ciot_dfu_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    ciot_dfu_t *base = (ciot_dfu_t *)self;
    *cfg = base->cfg;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_dfu_nrf_get_status(ciot_dfu_nrf_t self, ciot_dfu_status_t *status)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(status);
    ciot_dfu_t *base = (ciot_dfu_t *)self;
    *status = base->status;
    return CIOT_ERR__OK;
}

// ciot_err_t ciot_dfu_nrf_get_info(ciot_dfu_nrf_t self, ciot_dfu_info_t *info)
// {
//     CIOT_ERR_NULL_CHECK(self);
//     CIOT_ERR_NULL_CHECK(info);
//     ciot_dfu_t *base = (ciot_dfu_t*)self;
//     *info = base->info;
//     return CIOT_ERR__OK;
// }

ciot_err_t ciot_dfu_nrf_task(ciot_dfu_nrf_t self)
{
    CIOT_ERR_NULL_CHECK(self);

    if (self->state == CIOT_DFU_NRF_STATE_IDLE || self->state == CIOT_DFU_NRF_STATE_COMPLETED)
    {
        return CIOT_ERR__OK;
    }

    ciot_err_t err = ciot_dfu_nrf_write(self);
    if (err != CIOT_ERR__OK)
    {
        self->base.status.error = err;
        self->state = CIOT_DFU_NRF_STATE_ERROR;
        ciot_dfu_nrf_set_state(self, CIOT__DFU_STATE__DFU_STATE_ERROR);
    }

    if (self->last_state == self->state)
    {
        if(ciot_timer_compare(&self->timer, 5))
        {
            CIOT_LOGE(TAG, "TIMEOUT");
            err = CIOT_ERR__TIMEOUT;
            self->base.status.error = err;
            self->state = CIOT_DFU_NRF_STATE_ERROR;
            ciot_dfu_nrf_set_state(self, CIOT__DFU_STATE__DFU_STATE_ERROR);
        }
    }
    else
    {
        self->last_state = self->state;
        ciot_timer_init(&self->timer, 5);
    }

    return err;
}

ciot_err_t ciot_dfu_nrf_read_file(ciot_dfu_nrf_packet_t *object, const char *name)
{
    FILE *file = fopen(name, "rb");

    if (file == NULL)
    {
        CIOT_LOGE(TAG, "Error opening file %s", name);
        return CIOT_ERR__NOT_FOUND;
    }

    if (object == NULL || object->data != NULL)
    {
        CIOT_LOGE(TAG, "Invalid arg");
        return CIOT_ERR__INVALID_ARG;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    object->data = (uint8_t *)malloc(file_size * sizeof(uint8_t));
    object->size = file_size;
    if (object->data == NULL)
    {
        CIOT_LOGE(TAG, "Error allocating memory");
        return CIOT_ERR__NO_MEMORY;
    }

    size_t elements_read = fread(object->data, sizeof(uint8_t), file_size, file);
    if (elements_read != file_size)
    {
        CIOT_LOGE(TAG, "Error reading file");
        return CIOT_ERR__FAIL;
    }

    return 0;
}

ciot_err_t ciot_dfu_nrf_start_bootloader(ciot_dfu_nrf_t self, ciot_iface_t *iface, int sys_id)
{
    CIOT_LOGI(TAG, "Starting bootloader");
    ciot_sys_data_t sys_data = CIOT__SYS_DATA__INIT;
    ciot_sys_req_t sys_req = CIOT__SYS_REQ__INIT;
    sys_data.request = &sys_req;
    sys_data.request->type = CIOT__SYS_REQ_TYPE__SYS_REQ_TYPE_INIT_DFU;

    ciot_msg_t *msg = ciot_msg_get_empty(CIOT__MSG_TYPE__MSG_TYPE_REQUEST, CIOT__IFACE_TYPE__IFACE_TYPE_SYS, sys_id);
    msg->data->sys = &sys_data;

    ciot_err_t err = ciot_iface_send_req(iface, msg);
    if (err != CIOT_ERR__OK)
    {
        self->base.status.error = err;
        self->state = CIOT_DFU_NRF_STATE_ERROR;
        ciot_dfu_nrf_set_state(self, CIOT__DFU_STATE__DFU_STATE_ERROR);
    }

    iface->req_status.state = CIOT_IFACE_REQ_STATE_IDLE;

    return err;
}

ciot_dfu_nrf_state_t ciot_dfu_nrf_state(ciot_dfu_nrf_t self)
{
    return self->state;
}

static ciot_err_t ciot_dfu_nrf_write(ciot_dfu_nrf_t self)
{
    CIOT_ERR_NULL_CHECK(self);

    ciot_dfu_t *base = &self->base;

    // Send Ping [x09 x01]
    if (self->state == CIOT_DFU_NRF_STATE_SEND_PING)
    {
        CIOT_LOGI(TAG, "Send ping");
        self->data[0] = CIOT_DFU_NRF_OP_PING;
        self->data[1] = PING_ID;
        self->state = CIOT_DFU_NRF_STATE_WAITING_PING_RESP;
        return ciot_iface_send_data(&base->iface, self->data, 2);
    }

    // Create command: size [x01 x01 xXXXXXXXX]
    if (self->state == CIOT_DFU_NRF_STATE_CREATE_OBJECT)
    {
        CIOT_LOGI(TAG, "Create command");
        int32_t data_remaining = self->object.packet->size - self->data_transferred;
        self->object.remaining = data_remaining >= MAX_OBJECT_SIZE ? MAX_OBJECT_SIZE : data_remaining;
        self->data[0] = CIOT_DFU_NRF_OP_OBJECT_CREATE;
        self->data[1] = self->object.packet->type;
        self->data[2] = self->object.remaining;
        self->data[3] = self->object.remaining >> 8;
        self->data[4] = self->object.remaining >> 16;
        self->data[5] = self->object.remaining >> 24;
        self->state = CIOT_DFU_NRF_STATE_WAITING_CREATE_OBJ;
        return ciot_iface_send_data(&base->iface, self->data, 6);
    }

    // Transfer data up to 64 or 20 bytes [xXX .. xXX]
    if (self->state == CIOT_DFU_NRF_STATE_WRITE_DFU_PACKAGE)
    {
        uint32_t bytes_to_write = self->object.remaining;
        bytes_to_write = bytes_to_write > self->cfg.max_package_len ? self->cfg.max_package_len : bytes_to_write;
        self->crc.expected = crc32_compute(&self->object.packet->data[self->data_transferred], bytes_to_write, &self->crc.expected);
        // self->crc.expected = ciot_crc32_le(self->crc.expected, &self->object.packet->data[self->data_transferred], bytes_to_write);

        if (self->cfg.dfu.type != CIOT__DFU_TYPE__DFU_TYPE_BLE)
        {
            uint8_t write_opcode[] = {CIOT_DFU_NRF_OP_OBJECT_WRITE};
            // ciot_iface_send_data(&base->iface, write_opcode, 1);
            self->cfg.iface->send_data(self->cfg.iface, write_opcode, 1);
            self->base.status.image_size = self->object.packet->size,
            self->base.status.image_written = self->data_transferred;
            // CIOT_LOGI(TAG, "Item %d writing %d of object [%ld / %ld]", self->object.packet->type, bytes_to_write, self->data_transferred, self->object.packet->size);
        }

        ciot_err_t err = ciot_iface_send_data(&base->iface, &self->object.packet->data[self->data_transferred], bytes_to_write);
        if (err != CIOT_ERR__OK)
        {
            CIOT_LOGE(TAG, "Error sending data (0x%x)", err);
            self->base.status.error = err;
            self->state = CIOT_DFU_NRF_STATE_ERROR;
            ciot_dfu_nrf_set_state(self, CIOT__DFU_STATE__DFU_STATE_ERROR);
        }

        self->data_transferred += bytes_to_write;
        self->object.remaining -= bytes_to_write;
        self->object.packet->transferred = self->data_transferred == self->object.packet->size;
        self->prn_counter++;

        if (self->prn_counter >= PKT_SET_PRN_PARAM_LEN || self->object.packet->transferred)
        {
            self->prn_counter = 0;
            self->state = CIOT_DFU_NRF_STATE_REQUEST_CRC;
        }

        return err;
    }

    // Calculate CRC [x03]
    if (self->state == CIOT_DFU_NRF_STATE_REQUEST_CRC)
    {
        CIOT_LOGI(TAG, "Request CRC");
        self->data[0] = CIOT_DFU_NRF_OP_CRC_GET;
        self->state = CIOT_DFU_NRF_STATE_WAITING_CRC;
        return ciot_iface_send_data(&base->iface, self->data, 1);
    }

    // Execute command [0x04]
    if (self->state == CIOT_DFU_NRF_STATE_REQUEST_EXECUTE)
    {
        CIOT_LOGI(TAG, "Execute command");
        self->data[0] = CIOT_DFU_NRF_OP_OBJECT_EXECUTE;
        self->state = CIOT_DFU_NRF_STATE_WAITING_EXECUTE;
        return ciot_iface_send_data(&base->iface, self->data, 1);
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_dfu_nrf_process_data(ciot_dfu_nrf_t self, uint8_t *data, int len)
{
    CIOT_ERR_NULL_CHECK(self);

    ciot_dfu_t *base = &self->base;
    // CIOT_LOG_BUFFER_HEX(TAG, data, len);

    base->status.code = data[2];

    for (size_t i = 0; i < len; i++)
    {
        if (data[i] == CIOT_DFU_NRF_OP_RESPONSE)
        {
            data = &data[i];
            break;
        }
        CIOT_LOGD(TAG, "Invalid initial byte: %0x", data[i]);
    }

    // Invlalid message
    if (data[0] != CIOT_DFU_NRF_OP_RESPONSE)
    {
        CIOT_LOGE(TAG, "Invalid msg");
        return CIOT_ERR__VALIDATION_FAILED;
    }

    // Ping Response Success [x60 x09 x01] or Opcode not supported [x60 x09 x03]
    if (self->state == CIOT_DFU_NRF_STATE_WAITING_PING_RESP &&
        data[0] == CIOT_DFU_NRF_OP_RESPONSE &&
        data[1] == CIOT_DFU_NRF_OP_PING &&
        data[2] == CIOT_DFU_NRF_RES_CODE_SUCCESS)
    {
        CIOT_LOGI(TAG, "Ping response sucess");
        self->state = CIOT_DFU_NRF_STATE_CREATE_OBJECT;
        ciot_dfu_nrf_set_state(self, CIOT__DFU_STATE__DFU_STATE_IN_PROGRESS);
        return CIOT_ERR__OK;
    }

    if (self->state == CIOT_DFU_NRF_STATE_WAITING_PING_RESP &&
        data[0] == CIOT_DFU_NRF_OP_RESPONSE &&
        data[2] == CIOT_DFU_NRF_RES_CODE_OP_CODE_NOT_SUPPORTED &&
        !self->ping_refused)
    {
        CIOT_LOGI(TAG, "First ping refused. Trying again...");
        self->state = CIOT_DFU_NRF_STATE_SEND_PING;
        self->ping_refused = true;
        return CIOT_ERR__OK;
    }

    // Response Create Success [x60 x01 x01]
    if (self->state == CIOT_DFU_NRF_STATE_WAITING_CREATE_OBJ &&
        data[0] == CIOT_DFU_NRF_OP_RESPONSE &&
        data[1] == CIOT_DFU_NRF_OP_OBJECT_CREATE &&
        data[2] == CIOT_DFU_NRF_RES_CODE_SUCCESS)
    {
        CIOT_LOGI(TAG, "Response create success");
        self->state = CIOT_DFU_NRF_STATE_WRITE_DFU_PACKAGE;
        return CIOT_ERR__OK;
    }

    // Response Calculate CRC Sucess: offset CRC32 [x60 x03 x01 XXXXXXXX XXXXXXXX]
    // Response PRN Success: offset CRC32 [60 03 01 XXXXXXXX XXXXXXXX]
    if (self->state == CIOT_DFU_NRF_STATE_WAITING_CRC &&
        data[0] == CIOT_DFU_NRF_OP_RESPONSE &&
        data[1] == CIOT_DFU_NRF_OP_CRC_GET &&
        data[2] == CIOT_DFU_NRF_RES_CODE_SUCCESS)
    {
        CIOT_LOGI(TAG, "CRC received");
        self->crc.received = data[len - 1] << 24;
        self->crc.received += data[len - 2] << 16;
        self->crc.received += data[len - 3] << 8;
        self->crc.received += data[len - 4];
        if (self->crc.received != self->crc.expected)
        {
            CIOT_LOGI(TAG, "CRC error: expected = %lu, received = %lu", self->crc.expected, self->crc.received);
            self->state = CIOT_DFU_NRF_STATE_ERROR;
            ciot_dfu_nrf_set_state(self, CIOT__DFU_STATE__DFU_STATE_ERROR);
            return CIOT_ERR__CHECKSUM;
        }
        if (self->object.remaining == 0)
        {
            CIOT_LOGI(TAG, "Calculate CRC Sucess: offset CRC32");
            self->state = CIOT_DFU_NRF_STATE_REQUEST_EXECUTE;
        }
        else
        {
            CIOT_LOGI(TAG, "Response PRN Sucess: offset CRC32");
            self->state = CIOT_DFU_NRF_STATE_WRITE_DFU_PACKAGE;
        }
        return CIOT_ERR__OK;
    }

    // Response Execute Sucess [x60 x04 x01]
    if (self->state == CIOT_DFU_NRF_STATE_WAITING_EXECUTE &&
        data[0] == CIOT_DFU_NRF_OP_RESPONSE &&
        data[1] == CIOT_DFU_NRF_OP_OBJECT_EXECUTE &&
        data[2] == CIOT_DFU_NRF_RES_CODE_SUCCESS)
    {
        CIOT_LOGI(TAG, "Response Execute Success");
        if (self->object.packet->transferred)
        {
            if (self->object.packet->type == CIOT_DFU_NRF_PACKET_TYPE_INIT)
            {
                CIOT_LOGI(TAG, "Init packet write completed");
                self->object.packet = &self->cfg.app_image;
                self->data_transferred = 0;
                self->crc.expected = 0;
                self->state = CIOT_DFU_NRF_STATE_CREATE_OBJECT;
                return CIOT_ERR__OK;
            }
            if (self->object.packet->type == CIOT_DFU_NRF_PACKET_TYPE_APP_IMAGE)
            {
                CIOT_LOGI(TAG, "App image write completed");
                self->state = CIOT_DFU_NRF_STATE_COMPLETED;
                ciot_dfu_nrf_set_state(self, CIOT__DFU_STATE__DFU_STATE_COMPLETED);
                ciot_dfu_nrf_stop(self);
                return CIOT_ERR__OK;
            }
        }
        else
        {
            CIOT_LOGI(TAG, "Object write completed");
            self->state = CIOT_DFU_NRF_STATE_CREATE_OBJECT;
            return CIOT_ERR__OK;
        }
    }

    // DFU completed... nothing to do...
    if (self->state == CIOT_DFU_NRF_STATE_COMPLETED)
    {
        return CIOT_ERR__OK;
    }

    if (data[2] != CIOT_DFU_NRF_RES_CODE_SUCCESS)
    {
        CIOT_LOGE(TAG, "DFU failed at state %d with response code 0x%x", self->state, data[2]);
        if (data[2] == CIOT_DFU_NRF_RES_CODE_EXT_ERROR)
        {
            CIOT_LOGE(TAG, "DFU extended error code: 0x%x", data[3]);
            base->status.error = data[3];
        }
        if (self->state != CIOT_DFU_NRF_STATE_ERROR)
        {
            ciot_dfu_nrf_stop(self);
            ciot_dfu_nrf_set_state(self, CIOT__DFU_STATE__DFU_STATE_ERROR);
        }
        self->state = CIOT_DFU_NRF_STATE_ERROR;

        return CIOT_ERR__FAIL;
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_dfu_nrf_set_state(ciot_dfu_nrf_t self, ciot_dfu_state_t state)
{
    ciot_dfu_t *base = &self->base;
    base->status.state = state;
    if (state == CIOT__DFU_STATE__DFU_STATE_ERROR)
    {
        ciot_dfu_nrf_stop(self);
    }
    if (base->iface.event_handler != NULL)
    {
        ciot_msg_t *msg = ciot_msg_get(CIOT__MSG_TYPE__MSG_TYPE_STATUS, &base->iface);
        ciot_iface_event_t iface_event = {0};
        iface_event.type = CIOT_IFACE_EVENT_INTERNAL;
        iface_event.msg = msg;
        return base->iface.event_handler(&base->iface, &iface_event, base->iface.event_args);
    }
    return CIOT_ERR__OK;
}

static ciot_err_t ciot_dfu_nrf_event_handler(ciot_iface_t *sender, ciot_iface_event_t *event, void *args)
{
    CIOT_LOGD(TAG, "Event received %s", ciot_iface_event_to_str(event));

    ciot_dfu_nrf_t self = (ciot_dfu_nrf_t)args;

    if (event->type == CIOT_IFACE_EVENT_STARTED)
    {
        CIOT_LOGI(TAG, "DFU interface started");
        ciot_dfu_nrf_set_state(self, CIOT__DFU_STATE__DFU_STATE_STARTED);
        self->state = CIOT_DFU_NRF_STATE_SEND_PING;
    }

    if (event->type == CIOT_IFACE_EVENT_DATA)
    {
        ciot_err_t err = ciot_dfu_nrf_process_data(self, event->data, event->size);
        if (err != CIOT_ERR__OK)
        {
            self->base.status.error = err;
            self->state = CIOT_DFU_NRF_STATE_ERROR;
            ciot_dfu_nrf_set_state(self, CIOT__DFU_STATE__DFU_STATE_ERROR);
        }
    }

    return CIOT_ERR__OK;
}

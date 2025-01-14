/**
 * @file ciot_decoder_s.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "ciot_decoder_s.h"
#include "ciot_iface.h"

typedef enum ciot_decoder_s_state
{
    CIOT_DECODER_S_STATE_WAIT_START_CH,
    CIOT_DECODER_S_STATE_WAIT_SIZE,
    CIOT_DECODER_S_STATE_READING,
} ciot_decoder_s_state_t;

typedef struct ciot_decoder_s *ciot_decoder_s_t;

static ciot_err_t ciot_decoder_s_decode(ciot_decoder_t base, uint8_t byte);
static ciot_err_t ciot_decoder_s_encode(ciot_decoder_t base, uint8_t *bytes, int size);
static ciot_err_t ciot_decoder_s_send(ciot_decoder_t base, ciot_iface_t *iface, uint8_t *bytes, int size);

typedef struct ciot_decoder_s_buf
{
    uint8_t *ptr;
    int len;
} ciot_decoder_s_buf_t;

struct ciot_decoder_s
{
    struct ciot_decoder base;
    ciot_decoder_s_state_t state;
    ciot_decoder_s_buf_t buf;
    int size;
    int idx;
};

static const char *TAG = "ciot_decoder_s";
static uint8_t start_ch = CIOT_DECODER_S_START_CH;
static uint8_t end_ch = CIOT_DECODER_S_END_CH;

ciot_decoder_t ciot_decoder_s_new(uint8_t *buf, int size)
{
    ciot_decoder_s_t self = calloc(1, sizeof(struct ciot_decoder_s));
    self->base.result.buf = buf;
    self->buf.ptr = buf;
    self->buf.len = size;
    self->base.decode = ciot_decoder_s_decode;
    self->base.encode = ciot_decoder_s_encode;
    self->base.send = ciot_decoder_s_send;
    return &self->base;
}

static ciot_err_t ciot_decoder_s_decode(ciot_decoder_t base, uint8_t byte)
{
    ciot_decoder_s_t self = (ciot_decoder_s_t)base;

    CIOT_ERR_NULL_CHECK(self->buf.ptr);

    if(self->idx < self->buf.len)
    {
        self->buf.ptr[self->idx++] = byte;
    }
    else
    {
        CIOT_LOGE(TAG, "Overflow");
        self->idx = 0;
        self->state = CIOT_DECODER_S_STATE_WAIT_START_CH;
        base->state = CIOT_DECODER_STATE_ERROR;
        return CIOT_ERR_OVERFLOW;
    }

    switch (self->state)
    {
    case CIOT_DECODER_S_STATE_WAIT_START_CH:
        if(byte == CIOT_DECODER_S_START_CH)
        {
            self->idx = 0;
            self->state = CIOT_DECODER_S_STATE_WAIT_SIZE;
        }
        break;
    case CIOT_DECODER_S_STATE_WAIT_SIZE:
        if(self->idx == 2)
        {
            self->idx = 0;
            self->size = self->buf.ptr[1] << 8 | self->buf.ptr[0];
            self->state = CIOT_DECODER_S_STATE_READING;
        }
        break;
    case CIOT_DECODER_S_STATE_READING:
        if(self->idx == self->size + 1 && byte == CIOT_DECODER_S_END_CH)
        {
            self->idx = 0;
            self->state = CIOT_DECODER_S_STATE_WAIT_START_CH;
            base->state = CIOT_DECODER_STATE_DONE;
            base->result.buf = self->buf.ptr;
            base->result.size = self->size;
            return CIOT_ERR_OK;
        }  
        if(self->idx == self->size + 1)
        {
            CIOT_LOGE(TAG, "Missing terminator");
            self->idx = 0;
            self->state = CIOT_DECODER_S_STATE_WAIT_START_CH;
            base->state = CIOT_DECODER_STATE_ERROR;
            return CIOT_ERR_PROTOCOL_VIOLATION;
        }
    default:
        break;
    }

    base->state = CIOT_DECODER_STATE_DECODING;

    return CIOT_ERR_OK;
}

static ciot_err_t ciot_decoder_s_encode(ciot_decoder_t base, uint8_t *bytes, int size)
{
    CIOT_ERR_NULL_CHECK(base);
    CIOT_ERR_NULL_CHECK(bytes);
    ciot_decoder_s_t self = (ciot_decoder_s_t)base;
    if (size > self->buf.len - 4) {
        return CIOT_ERR_OVERFLOW;
    }
    base->result.buf[0] = start_ch;
    memcpy(&base->result.buf[1], (uint8_t*)&size, 2);
    memcpy(&base->result.buf[3], bytes, size);
    base->result.buf[3 + size] = end_ch;
    base->result.size = 4 + size;
    return CIOT_ERR_OK;
}

static ciot_err_t ciot_decoder_s_send(ciot_decoder_t base, ciot_iface_t *iface, uint8_t *bytes, int size)
{
    CIOT_ERR_NULL_CHECK(base);
    CIOT_ERR_NULL_CHECK(bytes);
    CIOT_ERR_NULL_CHECK(iface);
    iface->send_data(iface, &start_ch, 1);
    iface->send_data(iface, (uint8_t*)&size, 2);
    iface->send_data(iface, bytes, size);
    iface->send_data(iface, &end_ch, 1);
    return CIOT_ERR_OK;
}

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

static ciot_err_t ciot_decoder_s_decode(ciot_iface_t *iface, uint8_t byte);
static ciot_err_t ciot_decoder_s_send(ciot_iface_t *iface, uint8_t *data, int size);

typedef struct ciot_decoder_s_buf
{
    uint8_t *ptr;
    int len;
} ciot_decoder_s_buf_t;

struct ciot_decoder_s
{
    struct ciot_iface_decoder base;
    ciot_decoder_s_state_t state;
    ciot_decoder_s_buf_t buf;
    int size;
    int idx;
};

static const char *TAG = "ciot_decoder_s";
static uint8_t start_ch = CIOT_DECODER_S_START_CH;
static uint8_t end_ch = CIOT_DECODER_S_END_CH;

ciot_iface_decoder_t ciot_decoder_s_new(uint8_t *buf, int size)
{
    ciot_decoder_s_t self = calloc(1, sizeof(struct ciot_decoder_s));
    self->buf.ptr = buf;
    self->buf.len = size;
    self->base.decode = ciot_decoder_s_decode;
    self->base.send = ciot_decoder_s_send;
    self->base.event_type = CIOT_IFACE_EVENT_REQUEST;
    return &self->base;
}

static ciot_err_t ciot_decoder_s_decode(ciot_iface_t *iface, uint8_t byte)
{
    ciot_decoder_s_t self = (ciot_decoder_s_t)iface->decoder;
    ciot_iface_decoder_t base = &self->base;

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
        base->state = CIOT_IFACE_DECODER_STATE_ERROR;
        return CIOT_ERR__OVERFLOW;
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
            base->state = CIOT_IFACE_DECODER_STATE_DONE;
            ciot_iface_event_t iface_event = {0};
            iface_event.type = base->event_type;
            iface_event.data = self->buf.ptr;
            iface_event.size = self->size;
            ciot_iface_send_event(iface, &iface_event);
        }  
        if(self->idx == self->size + 1)
        {
            CIOT_LOGE(TAG, "Missing terminator");
            self->idx = 0;
            self->state = CIOT_DECODER_S_STATE_WAIT_START_CH;
            base->state = CIOT_IFACE_DECODER_STATE_ERROR;
            return CIOT_ERR__PROTOCOL_VIOLATION;
        }
    default:
        break;
    }

    base->state = CIOT_IFACE_DECODER_STATE_DECODING;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_decoder_s_send(ciot_iface_t *iface, uint8_t *data, int size)
{
    CIOT_ERR_NULL_CHECK(data);
    CIOT_ERR_NULL_CHECK(iface);
    iface->send_data(iface, &start_ch, 1);
    iface->send_data(iface, (uint8_t*)&size, 2);
    iface->send_data(iface, data, size);
    iface->send_data(iface, &end_ch, 1);
    return CIOT_ERR__OK;
}

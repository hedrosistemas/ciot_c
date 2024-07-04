/**
 * @file ciot_decoder_slip.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-06-12
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdlib.h>
#include "ciot_iface.h"
#include "ciot_decoder_slip.h"

#define SLIP_BYTE_END 0xc0
#define SLIP_BYTE_ESC 0xdb
#define SLIP_BYTE_ESC_END 0xdc
#define SLIP_BYTE_ESC_ESC 0xdd

typedef struct ciot_decoder_slip *ciot_decoder_slip_t;

static ciot_err_t ciot_decoder_slip_decode(ciot_iface_t *iface, uint8_t byte);
static ciot_err_t ciot_decoder_slip_send(ciot_iface_t *iface, uint8_t *data, int size);

static uint8_t slip_byte_end = SLIP_BYTE_END;
static uint8_t slip_byte_esc = SLIP_BYTE_ESC;
static uint8_t slip_byte_esc_end = SLIP_BYTE_ESC_END;
static uint8_t slip_byte_esc_esc = SLIP_BYTE_ESC_ESC;

typedef enum ciot_decoder_slip_read_state
{
    CIOT_DECODER_SLIP_STATE_DECODING,
    CIOT_DECODER_SLIP_STATE_ESC_RECEIVED,
    CIOT_DECODER_SLIP_STATE_CLEARING_INVALID_PACKET
} ciot_decoder_slip_read_state_t;

typedef struct ciot_decoder_slip_buf
{
    uint8_t *ptr;
    int len;
} ciot_decoder_slip_buf_t;

struct ciot_decoder_slip
{
    struct ciot_iface_decoder base;
    ciot_decoder_slip_buf_t buf;
    ciot_decoder_slip_read_state_t state;
    int size;
    int idx;
};

static const char *TAG = "ciot_decoder_slip";

ciot_iface_decoder_t ciot_decoder_slip_new(uint8_t *buf, int size)
{
    ciot_decoder_slip_t self = calloc(1, sizeof(struct ciot_decoder_slip));
    self->buf.ptr = buf;
    self->buf.len = size;
    self->base.decode = ciot_decoder_slip_decode;
    self->base.send = ciot_decoder_slip_send;
    return &self->base;
}

static ciot_err_t ciot_decoder_slip_decode(ciot_iface_t *iface, uint8_t byte)
{
    ciot_decoder_slip_t self = (ciot_decoder_slip_t)iface->decoder;
    ciot_iface_decoder_t base = &self->base;
    
    CIOT_ERR_NULL_CHECK(self->buf.ptr);
    
    if(self->idx >= self->buf.len)
    {
        CIOT_LOGE(TAG, "Overflow");
        self->idx = 0;
        base->state = CIOT_IFACE_DECODER_STATE_ERROR;
        return CIOT_ERR__OVERFLOW;
    }

    switch (self->state)
    {
    case CIOT_DECODER_SLIP_STATE_DECODING:
        switch (byte)
        {
        case SLIP_BYTE_END:
            self->idx = 0;
            ciot_iface_event_t iface_event = {0};
            iface_event.type = CIOT_IFACE_EVENT_REQUEST;
            iface_event.data = self->buf.ptr;
            iface_event.size = self->size;
            ciot_iface_send_event(iface, &iface_event);
            break;
        case SLIP_BYTE_ESC:
            self->state = CIOT_DECODER_SLIP_STATE_ESC_RECEIVED;
            break;
        default:
            self->buf.ptr[self->idx++] = byte;
            break;
        }
        break;
    case CIOT_DECODER_SLIP_STATE_ESC_RECEIVED:
        switch (byte)
        {
        case SLIP_BYTE_ESC_END:
            self->buf.ptr[self->idx++] = SLIP_BYTE_END;
            self->state = CIOT_DECODER_SLIP_STATE_DECODING;
            break;
        case SLIP_BYTE_ESC_ESC:
            self->buf.ptr[self->idx++] = SLIP_BYTE_ESC;
            self->state = CIOT_DECODER_SLIP_STATE_DECODING;
            break;
        default:
            self->state = CIOT_DECODER_SLIP_STATE_CLEARING_INVALID_PACKET;
            base->state = CIOT_IFACE_DECODER_STATE_ERROR;
            return CIOT_ERR__PROTOCOL_VIOLATION;
        }
        break;
    case CIOT_DECODER_SLIP_STATE_CLEARING_INVALID_PACKET:
        if(byte == SLIP_BYTE_END)
        {
            self->state = CIOT_DECODER_SLIP_STATE_DECODING;
            self->idx = 0;
        }
        break;
    default:
        break;
    }

    base->state = CIOT_IFACE_DECODER_STATE_DECODING;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_decoder_slip_send(ciot_iface_t *iface, uint8_t *data, int size)
{
    CIOT_ERR_NULL_CHECK(data);
    CIOT_ERR_NULL_CHECK(iface);

    for (size_t i = 0; i < size; i++)
    {
        switch (data[i])
        {
        case SLIP_BYTE_END:
            iface->send_data(iface, &slip_byte_esc, 1);
            iface->send_data(iface, &slip_byte_esc_end, 1);
            break;
        case SLIP_BYTE_ESC:
            iface->send_data(iface, &slip_byte_esc, 1);
            iface->send_data(iface, &slip_byte_esc_esc, 1);
            break;
        default:
            iface->send_data(iface, &data[i], 1);
            break;
        }
    }
    
    iface->send_data(iface, &slip_byte_end, 1);

    return CIOT_ERR__OK;
}

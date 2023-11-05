/**
 * @file ciot_s.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ciot_s.h"
#include "ciot_err.h"

struct ciot_s
{
    ciot_s_cfg_t cfg;
    ciot_s_status_t status;
    uint8_t buf[CIOT_S_BUF_SIZE];
    int idx;
    int len;
};

ciot_s_t ciot_s_new(ciot_s_cfg_t *cfg)
{
    ciot_s_t s = calloc(1, sizeof(struct ciot_s));
    memcpy(&s->cfg, cfg, sizeof(*cfg));
    return s;
}

ciot_err_t ciot_s_send(ciot_s_t self, uint8_t *data, int size)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(data);
    CIOT_NULL_CHECK(self->cfg.send_bytes);
    
    uint8_t header[] = { 
        CIOT_S_START_CH, 
        size & 0xFF, 
        (size >> 8) & 0xFF
    };
    uint8_t end = CIOT_S_END_CH;

    self->cfg.send_bytes(self->cfg.user_ctx, header, sizeof(header));
    self->cfg.send_bytes(self->cfg.user_ctx, data, size);
    self->cfg.send_bytes(self->cfg.user_ctx, &end, 1);

    return CIOT_OK;
}

ciot_err_t ciot_s_process_byte(ciot_s_t self, uint8_t byte)
{
    if(self->idx < CIOT_S_BUF_SIZE)
    {
        self->buf[self->idx] = byte;
    }
    else
    {
        return CIOT_ERR_OVERFLOW;
    }

    switch (self->status)
    {
        case CIOT_S_STATUS_WAIT_START_DATA:
            if(byte == CIOT_S_START_CH)
            {
                self->idx = 0;
                self->len = 0;
                self->buf[self->idx] = byte;
                self->status = CIOT_S_STATUS_WAIT_SIZE;
            }
            break;
        case CIOT_S_STATUS_WAIT_SIZE:
            self->len++;
            if (self->len == CIOT_S_LENGHT_SIZE)
            {
                self->len = self->buf[2] << 8 | self->buf[1];
                self->status = CIOT_S_STATUS_READ_DATA;
            }
            break;
        case CIOT_S_STATUS_READ_DATA:
            if(byte == CIOT_S_END_CH)
            {
                if(self->idx - CIOT_S_HEADER_SIZE == self->len)
                {
                    if(self->cfg.on_message_cb != NULL)
                    {
                        self->cfg.on_message_cb(self->cfg.user_ctx, &self->buf[CIOT_S_HEADER_SIZE], self->len);
                    }
                    self->status = CIOT_S_STATUS_WAIT_START_DATA;
                    return CIOT_OK;
                }
                else
                {
                    self->idx = 0;
                    self->status = CIOT_S_STATUS_WAIT_START_DATA;
                    return CIOT_ERR_INVALID_SIZE;
                }
            }
            if(self->idx - CIOT_S_HEADER_SIZE == self->len)
            {
                self->idx = 0;
                self->status = CIOT_S_STATUS_WAIT_START_DATA;
                return CIOT_ERR_TERMINATOR_MISSING;
            }
            break;
    default:
        break;
    }

    self->idx++;

    return CIOT_OK;
}

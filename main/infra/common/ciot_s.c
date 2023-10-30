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
    char buf[CIOT_S_BUF_SIZE];
    int idx;
    int len;
    void *handler;
};
ciot_s_t ciot_s_new(ciot_s_cfg_t *cfg)
{
    ciot_s_t s = calloc(1, sizeof(struct ciot_s));
    memcpy(&s->base.cfg, cfg, sizeof(*cfg));
    return s;
}

ciot_err_t ciot_s_send(ciot_s_t self, char *data, int size)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(data);
    
    uint8_t header[] = { 
        (uint8_t)CIOT_S_START_CH, 
        size & 0xFF, 
        (size >> 8) & 0xFF
    };
    uint8_t end = CIOT_S_END_CH;

    ciot_s_write_bytes(&header, sizeof(header));
    ciot_s_write_bytes(data, size);
    ciot_s_write_bytes(&end, 1);

    return CIOT_OK;
}

ciot_err_t ciot_s_process_byte(ciot_s_t self, char byte)
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
                    if(self->cfg.base.on_message_cb != NULL)
                    {
                        self->cfg.base.on_message_cb(&self->buf[CIOT_S_HEADER_SIZE], self->len);
                    }
                    self->status = CIOT_S_STATUS_WAIT_START_DATA;
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

ciot_err_t ciot_s_get_handler(ciot_s_t s, void *handler)
{
    CIOT_NULL_CHECK(self);
    handler = s->handler;
    return CIOT_OK;
}

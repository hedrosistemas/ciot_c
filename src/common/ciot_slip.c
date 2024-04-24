/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#include "ciot_slip.h"
#include "ciot_err.h"

#define SLIP_BYTE_END             0xc0    /* indicates end of packet */
#define SLIP_BYTE_ESC             0xdb    /* indicates byte stuffing */
#define SLIP_BYTE_ESC_END         0xdc    /* ESC ESC_END means END data byte */
#define SLIP_BYTE_ESC_ESC         0xdd    /* ESC ESC_ESC means ESC data byte */

int ciot_slip_encode(uint8_t * p_output,  uint8_t * p_input, uint32_t input_length, uint32_t * p_output_buffer_length)
{
    if (p_output == NULL || p_input == NULL || p_output_buffer_length == NULL)
    {
        return CIOT_ERR_NULL_ARG;
    }

    *p_output_buffer_length = 0;
    uint32_t input_index;

    for (input_index = 0; input_index < input_length; input_index++)
    {
        switch (p_input[input_index])
        {
            case SLIP_BYTE_END:
                p_output[(*p_output_buffer_length)++] = SLIP_BYTE_ESC;
                p_output[(*p_output_buffer_length)++] = SLIP_BYTE_ESC_END;
                break;

            case SLIP_BYTE_ESC:
                p_output[(*p_output_buffer_length)++] = SLIP_BYTE_ESC;
                p_output[(*p_output_buffer_length)++] = SLIP_BYTE_ESC_ESC;
                break;

            default:
                p_output[(*p_output_buffer_length)++] = p_input[input_index];
        }
    }
    p_output[(*p_output_buffer_length)++] = SLIP_BYTE_END;

    return CIOT_OK;
}

int ciot_slip_decode_add_byte(ciot_slip_t * p_slip, uint8_t c)
{
    if (p_slip == NULL)
    {
        return CIOT_ERR_NULL_ARG;
    }

    if (p_slip->current_index == p_slip->buffer_len)
    {
        return CIOT_ERR_NO_MEMORY;
    }

    switch (p_slip->state)
    {
        case CIOT_SLIP_STATE_DECODING:
            switch (c)
            {
                case SLIP_BYTE_END:
                    // finished reading packet
                    return CIOT_OK;

                case SLIP_BYTE_ESC:
                    // wait for
                    p_slip->state = CIOT_SLIP_STATE_ESC_RECEIVED;
                    break;

                default:
                    // add byte to buffer
                    p_slip->p_buffer[p_slip->current_index++] = c;
                    break;
            }
            break;

        case CIOT_SLIP_STATE_ESC_RECEIVED:
            switch (c)
            {
                case SLIP_BYTE_ESC_END:
                    p_slip->p_buffer[p_slip->current_index++] = SLIP_BYTE_END;
                    p_slip->state = CIOT_SLIP_STATE_DECODING;
                    break;

                case SLIP_BYTE_ESC_ESC:
                    p_slip->p_buffer[p_slip->current_index++] = SLIP_BYTE_ESC;
                    p_slip->state = CIOT_SLIP_STATE_DECODING;
                    break;

                default:
                    // protocol violation
                    p_slip->state = CIOT_SLIP_STATE_CLEARING_INVALID_PACKET;
                    return CIOT_ERR_INVALID_STATE;
            }
            break;

        case CIOT_SLIP_STATE_CLEARING_INVALID_PACKET:
            if (c == SLIP_BYTE_END)
            {
                p_slip->state = CIOT_SLIP_STATE_DECODING;
                p_slip->current_index = 0;
            }
            break;
    }

    return CIOT_ERR_BUSY;
}
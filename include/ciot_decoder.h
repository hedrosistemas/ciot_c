/**
 * @file ciot_decoder.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_decoder__H__
#define __CIOT_decoder__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include "ciot_err.h"
#include "ciot_iface.h"

typedef enum ciot_decoder_state
{
    CIOT_DECODER_STATE_ERROR=-1,
    CIOT_DECODER_STATE_IDLE,
    CIOT_DECODER_STATE_DECODING,
    CIOT_DECODER_STATE_DONE,
} ciot_decoder_state_t;

typedef struct ciot_decoder *ciot_decoder_t;
typedef ciot_err_t (ciot_decoder_decode_fn)(ciot_decoder_t self, uint8_t byte);
typedef ciot_err_t (ciot_decoder_send_fn)(ciot_decoder_t self, uint8_t *data, int size);

struct ciot_decoder
{
    ciot_decoder_decode_fn *decode;
    ciot_decoder_send_fn *send;
    ciot_iface_t *iface;
    ciot_decoder_state_t state;
};

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_decoder__H__

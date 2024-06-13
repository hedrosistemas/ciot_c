/**
 * @file ciot_decoder_slip.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_DECODER_SLIP__H__
#define __CIOT_DECODER_SLIP__H__

#include <inttypes.h>
#include "ciot_decoder.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CIOT_DECODER_SLIP_START_CH '{'
#define CIOT_DECODER_SLIP_END_CH '}'

ciot_decoder_t ciot_decoder_slip_new(uint8_t *buf, int size);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_decoder_Slip__H__
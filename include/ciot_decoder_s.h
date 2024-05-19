/**
 * @file ciot_decoder_s.h
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief Header file for the S-type CIOT (Custom IoT) Decoder library.
 * @version 0.1
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_DECODER_S__H__
#define __CIOT_DECODER_S__H__

#include "ciot_decoder.h"

/**
 * @brief Creates a new S-type CIOT decoder object based on the provided configuration.
 *
 * @param cfg Pointer to the configuration for the S-type decoder.
 * @return ciot_decoder_t The newly created S-type CIOT decoder object.
 */
ciot_decoder_t ciot_decoder_s_new(ciot_decoder_cfg_t *cfg);

/**
 * @brief Decodes a byte of data using the specified S-type CIOT decoder object.
 *
 * @param base The base S-type CIOT decoder object.
 * @param byte The byte to decode.
 * @return ciot_err_t The decoding error code.
 */
ciot_err_t ciot_decoder_s_decode(ciot_decoder_t base, uint8_t byte);

/**
 * @brief Encodes data using the specified S-type CIOT decoder object.
 *
 * @param base The base S-type CIOT decoder object.
 * @param data The data to encode.
 * @param size The size of the data to encode.
 * @return ciot_err_t The encoding error code.
 */
ciot_err_t ciot_decoder_s_encode(ciot_decoder_t base, uint8_t *data, int size);

#endif  //!__CIOT_DECODER_S__H__

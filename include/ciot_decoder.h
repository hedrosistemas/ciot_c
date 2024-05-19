/**
 * @file ciot_decoder.h
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief Header file for CIOT (Custom IoT) Decoder library.
 * @version 0.1
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_DECODER__H__
#define __CIOT_DECODER__H__

#include <inttypes.h>

#include "ciot_err.h"

/**
 * @brief Pointer to a CIOT decoder object.
 */
typedef struct ciot_decoder *ciot_decoder_t;

/**
 * @brief Function pointer type for decoding data.
 *
 * @param base The base CIOT decoder object.
 * @param byte The byte to decode.
 * @return ciot_err_t The decoding error code.
 */
typedef ciot_err_t (ciot_decoder_decode_fn)(ciot_decoder_t base, uint8_t byte);

/**
 * @brief Function pointer type for encoding data.
 *
 * @param base The base CIOT decoder object.
 * @param data The data to encode.
 * @param size The size of the data to encode.
 * @return ciot_err_t The encoding error code.
 */
typedef ciot_err_t (ciot_decoder_encode_fn)(ciot_decoder_t base, uint8_t *data, int size);

/**
 * @brief Enumeration for CIOT decoder types.
 */
typedef enum ciot_decoder_type
{
    CIOT_DECODER_TYPE_NONE, /**< No specific decoder type. */
    CIOT_DECODER_TYPE_SLIP, /**< SLIP decoder type. */
    CIOT_DECODER_TYPE_S,    /**< S decoder type. */
    CIOT_DECODER_TYPE_CUSTOM /**< Custom decoder type. */
} ciot_decoder_type_t;

/**
 * @brief Enumeration for CIOT decoder states.
 */
typedef enum ciot_decoder_state
{
    CIOT_DECODER_STATE_ERROR = -1, /**< Error state. */
    CIOT_DECODER_STATE_IDLE,       /**< Idle state. */
    CIOT_DECODER_STATE_DECODING,   /**< Decoding state. */
    CIOT_DECODER_STATE_DONE        /**< Decoding done state. */
} ciot_decoder_state_t;

/**
 * @brief Structure for CIOT decoder buffer.
 */
typedef struct ciot_decoder_buffer
{
    uint8_t *buf; /**< Buffer pointer. */
    int size;     /**< Buffer size. */
} ciot_decoder_buffer_t;

/**
 * @brief Structure for CIOT decoder configuration.
 */
typedef struct ciot_decoder_cfg
{
    ciot_decoder_buffer_t decoder; /**< Decoder buffer. */
    ciot_decoder_buffer_t encoder; /**< Encoder buffer. */
} ciot_decoder_cfg_t;

/**
 * @brief Main CIOT decoder structure.
 */
struct ciot_decoder
{
    ciot_decoder_type_t type;         /**< Decoder type. */
    ciot_decoder_state_t state;       /**< Decoder state. */
    ciot_decoder_buffer_t decoder;    /**< Decoder buffer. */
    ciot_decoder_buffer_t encoder;    /**< Encoder buffer. */
    ciot_decoder_decode_fn *decode;   /**< Decode function pointer. */
    ciot_decoder_encode_fn *encode;   /**< Encode function pointer. */
    void *self;                       /**< Pointer to self. */
};

/**
 * @brief Creates a new CIOT decoder object based on the provided configuration.
 *
 * @param cfg Pointer to the configuration for the decoder.
 * @return ciot_decoder_t The newly created CIOT decoder object.
 */
ciot_decoder_t ciot_decoder_new(ciot_decoder_cfg_t *cfg);

/**
 * @brief Decodes a byte of data using the specified CIOT decoder object.
 *
 * @param base The base CIOT decoder object.
 * @param byte The byte to decode.
 * @return ciot_err_t The decoding error code.
 */
ciot_err_t ciot_decoder_decode(ciot_decoder_t base, uint8_t byte);

/**
 * @brief Encodes data using the specified CIOT decoder object.
 *
 * @param base The base CIOT decoder object.
 * @param data The data to encode.
 * @param size The size of the data to encode.
 * @return ciot_err_t The encoding error code.
 */
ciot_err_t ciot_decoder_encode(ciot_decoder_t base, uint8_t *data, int size);

#endif  //!__CIOT_DECODER__H__

/**
 * @file ciot_storage.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_STORAGE__H__
#define __CIOT_STORAGE__H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include "ciot_err.h"
#include "ciot_msg.h"
#include "ciot_serializer.h"

typedef enum ciot_storage_type
{
    CIOT_STORAGE_TYPE_FS,
    CIOT_STORAGE_TYPE_NVS,
} ciot_storage_type_t;

typedef struct ciot_storage *ciot_storage_t;
typedef ciot_err_t ciot_storage_write_bytes_fn(char *path, uint8_t *bytes, int size);
typedef ciot_err_t ciot_storage_read_bytes_fn(char *path, uint8_t *bytes, int *size);

struct ciot_storage
{
    ciot_storage_type_t type;
    ciot_serializer_t serializer;
    ciot_storage_write_bytes_fn *write_bytes;
    ciot_storage_read_bytes_fn *read_bytes;
};

ciot_err_t ciot_storage_set_data(ciot_storage_t self, char *path, ciot_msg_data_t *data);
ciot_msg_data_t *ciot_storage_get_data(ciot_storage_t self, char *path);

#ifdef __cplusplus
}
#endif

#endif  //!__CIOT_STORAGE__H__

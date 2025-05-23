/**
 * @file ciot_storage.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "ciot_storage.h"
#include "ciot_config.h"
#include "ciot_err.h"

ciot_err_t ciot_storage_save_obj(ciot_storage_t self, char *path, void *obj, const void *obj_type, int size)
{
    CIOT_ERR_NULL_CHECK(self);
    uint8_t bytes[size];
    memset(bytes, 0, size);
    size = ciot_serializer_to_bytes(bytes, sizeof(bytes), obj, obj_type);
    return self->write_bytes(self, path, bytes, size);
}

ciot_err_t ciot_storage_load_obj(ciot_storage_t self, char *path, void *obj, const void *obj_type)
{
    CIOT_ERR_NULL_CHECK(self);
    int size = 0;
    CIOT_ERR_RETURN(self->read_bytes(self, path, NULL, &size));
    uint8_t bytes[size];
    memset(bytes, 0, size);
    CIOT_ERR_RETURN(self->read_bytes(self, path, bytes, &size));
    ciot_serializer_from_bytes(bytes, size, obj, obj_type);
    return CIOT_ERR_OK;
}

ciot_err_t ciot_storage_save_data(ciot_storage_t self, char *path, ciot_msg_data_t *data)
{
    return ciot_storage_save_obj(self, path, data, CIOT_MSG_DATA_FIELDS, CIOT_CONFIG_MSG_SIZE);
}

ciot_err_t ciot_storage_load_data(ciot_storage_t self, char *path, ciot_msg_data_t *data)
{
    return ciot_storage_load_obj(self, path, data, CIOT_MSG_DATA_FIELDS);
}
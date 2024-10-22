/**
 * @file ciot_storage.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "ciot_storage.h"
#include "ciot_err.h"

static ciot_msg_t *msg = NULL;

static const char *TAG = "ciot_storage";

ciot_err_t ciot_storage_set_data(ciot_storage_t self, char *path, ciot_msg_data_t *data)
{
    CIOT_ERR_NULL_CHECK(self);

    ciot_msg_t msg = CIOT__MSG__INIT;
    msg.data = data;

    CIOT_LOGI(TAG, "saving data:");
    ciot_msg_print(&data->base);

    int size = ciot__msg__get_packed_size(&msg);
    uint8_t buf[size];

    if(self->serializer)
    {
        size = self->serializer->to_bytes(buf, &msg);
    }
    else
    {
        size = ciot__msg__pack(&msg, buf);
    }

    return self->write_bytes(path, buf, size);
}

ciot_msg_data_t *ciot_storage_get_data(ciot_storage_t self, char *path)
{
    if(self == NULL) return NULL;

    CIOT_LOGI(TAG, "Get data from %s", path);

    int size = 0;
    self->read_bytes(path, NULL, &size);

    if(size > 0)
    {
        uint8_t buf[size];
        self->read_bytes(path, buf, &size);

        ciot__msg__free_unpacked(msg, NULL);
        if(self->serializer)
        {
            msg = self->serializer->from_bytes(buf, size);
        }
        else
        {
            msg = ciot__msg__unpack(NULL, size, buf);
        }

        if(msg == NULL)
        {
            CIOT_LOGE(TAG, "Deserialization error.");
            return NULL;
        }

        return msg->data;
    }
    return NULL;
}

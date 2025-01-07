/**
 * @file ciot_wifi_base.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-12-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ciot_wifi.h"
#include "ciot_types.h"

static ciot_err_t ciot_wifi_process_data(ciot_iface_t *iface, ciot_msg_data_t *data);
static ciot_err_t ciot_wifi_get_data(ciot_iface_t *iface, ciot_msg_data_t *data);
static ciot_err_t ciot_wifi_send_data(ciot_iface_t *iface, uint8_t *data, int size);

ciot_err_t ciot_wifi_init(ciot_wifi_t self)
{
    ciot_wifi_base_t *base = (ciot_wifi_base_t *)self;

    base->iface.ptr = self;
    base->iface.process_data = ciot_wifi_process_data;
    base->iface.get_data = ciot_wifi_get_data;
    base->iface.send_data = ciot_wifi_send_data;
    base->iface.info.type = CIOT_IFACE_TYPE_WIFI;
    
    return CIOT_ERR_OK;
}

ciot_err_t ciot_wifi_process_req(ciot_wifi_t self, ciot_wifi_req_t *req)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(req);
    return CIOT_ERR_NOT_SUPPORTED;    
}

static ciot_err_t ciot_wifi_process_data(ciot_iface_t *iface, ciot_msg_data_t *data)
{
    CIOT_ERR_TYPE_CHECK(data->which_type, CIOT_MSG_DATA_WIFI_TAG);

    ciot_wifi_t self = iface->ptr;
    ciot_wifi_data_t *wifi = &data->wifi;

    switch (wifi->which_type)
    {
    case CIOT_WIFI_DATA_STOP_TAG:
        return ciot_wifi_stop(self);
    case CIOT_WIFI_DATA_CONFIG_TAG:
        return ciot_wifi_start(self, &wifi->config);
    case CIOT_WIFI_DATA_REQUEST_TAG:
        return ciot_wifi_process_req(self, &wifi->request);
    default:
        return CIOT_ERR_INVALID_TYPE;
    }

    return CIOT_ERR_NOT_IMPLEMENTED;
}

static ciot_err_t ciot_wifi_get_data(ciot_iface_t *iface, ciot_msg_data_t *data)
{
    CIOT_ERR_TYPE_CHECK(data->which_type, CIOT_MSG_DATA_GET_DATA_TAG);

    ciot_wifi_base_t *self = iface->ptr;
    ciot_data_type_t data_type = data->get_data.type;
    data->which_type = CIOT_MSG_DATA_WIFI_TAG;

    switch (data_type)
    {
    case CIOT_DATA_TYPE_CONFIG:
        data->wifi.which_type = CIOT_WIFI_DATA_CONFIG_TAG;
        data->wifi.config = self->cfg;
        break;
    case CIOT_DATA_TYPE_STATUS:
        data->wifi.which_type = CIOT_WIFI_DATA_STATUS_TAG;
        data->wifi.status = self->status;
        break;
    case CIOT_DATA_TYPE_INFO:
        return CIOT_ERR_NOT_FOUND;
    default:
    }

    return CIOT_ERR_OK;
}

static ciot_err_t ciot_wifi_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    CIOT_ERR_NULL_CHECK(iface);
    CIOT_ERR_NULL_CHECK(data);
    return CIOT_ERR_NOT_SUPPORTED;
}

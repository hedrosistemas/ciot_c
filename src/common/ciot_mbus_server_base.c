/**
 * @file ciot_mbus_server_base.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-12-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ciot_mbus_server.h"
#include "ciot_types.h"

static ciot_err_t ciot_mbus_server_process_data(ciot_iface_t *iface, ciot_msg_data_t *data);
static ciot_err_t ciot_mbus_server_get_data(ciot_iface_t *iface, ciot_msg_data_t *data);
static ciot_err_t ciot_mbus_server_send_data(ciot_iface_t *iface, uint8_t *data, int size);

ciot_err_t ciot_mbus_server_init(ciot_mbus_server_t self)
{
    ciot_mbus_server_base_t *base = (ciot_mbus_server_base_t *)self;

    base->iface.ptr = self;
    base->iface.process_data = ciot_mbus_server_process_data;
    base->iface.get_data = ciot_mbus_server_get_data;
    base->iface.send_data = ciot_mbus_server_send_data;
    base->iface.info.type = CIOT_IFACE_TYPE_MBUS_SERVER;
    return CIOT_ERR_OK;
}

ciot_err_t ciot_mbus_server_process_req(ciot_mbus_server_t self, ciot_mbus_server_req_t *req)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(req);
    return CIOT_ERR_NOT_SUPPORTED;    
}

static ciot_err_t ciot_mbus_server_process_data(ciot_iface_t *iface, ciot_msg_data_t *data)
{
    CIOT_ERR_TYPE_CHECK(data->which_type, CIOT_MSG_DATA_MBUS_SERVER_TAG);

    ciot_mbus_server_t self = iface->ptr;
    ciot_mbus_server_data_t *mbus_server = &data->mbus_server;

    switch (mbus_server->which_type)
    {
    case CIOT_MBUS_SERVER_DATA_STOP_TAG:
        return ciot_mbus_server_stop(self);
    case CIOT_MBUS_SERVER_DATA_CONFIG_TAG:
        return ciot_mbus_server_start(self, &mbus_server->config);
    case CIOT_MBUS_SERVER_DATA_REQUEST_TAG:
        return ciot_mbus_server_process_req(self, &mbus_server->request);
    default:
        return CIOT_ERR_INVALID_TYPE;
    }

    return CIOT_ERR_NOT_IMPLEMENTED;
}

static ciot_err_t ciot_mbus_server_get_data(ciot_iface_t *iface, ciot_msg_data_t *data)
{
    CIOT_ERR_TYPE_CHECK(data->which_type, CIOT_MSG_DATA_GET_DATA_TAG);

    ciot_mbus_server_base_t *self = iface->ptr;
    ciot_data_type_t data_type = data->get_data.type;
    data->which_type = CIOT_MSG_DATA_MBUS_SERVER_TAG;

    switch (data_type)
    {
    case CIOT_DATA_TYPE_CONFIG:
        data->mbus_server.which_type = CIOT_MBUS_SERVER_DATA_CONFIG_TAG;
        data->mbus_server.config = self->cfg;
        break;
    case CIOT_DATA_TYPE_STATUS:
        data->mbus_server.which_type = CIOT_MBUS_SERVER_DATA_STATUS_TAG;
        data->mbus_server.status = self->status;
        break;
    default:
        return CIOT_ERR_NOT_FOUND;
    }

    return CIOT_ERR_OK;
}

static ciot_err_t ciot_mbus_server_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    CIOT_ERR_NULL_CHECK(iface);
    CIOT_ERR_NULL_CHECK(data);
    return CIOT_ERR_NOT_SUPPORTED;
}

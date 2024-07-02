/**
 * @file ciot_ble_scn_base.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "ciot_ble_scn.h"
#include "ciot_config.h"

// static const char *TAG = "ciot_ble_scn";

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req);
static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg);
static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size);

#ifdef CIOT_CONFIG_BLE_SCN_ADV_FIFO_SIZE
static ciot_err_t ciot_ble_scn_base_init_fifo(ciot_ble_scn_adv_fifo_t *adv_fifo);
#endif

ciot_err_t ciot_ble_scn_init(ciot_ble_scn_t self)
{
    ciot_ble_scn_base_t *base = (ciot_ble_scn_base_t*)self;

    ciot_iface_init(&base->iface);
    ciot__ble_scn_data__init(&base->data);
    ciot__ble_scn_cfg__init(&base->cfg);
    ciot__ble_scn_status__init(&base->status);
    ciot__ble_scn_adv__init(&base->recv);
    ciot__ble_scn_adv_info__init(&base->recv_info);

    base->iface.ptr = self;
    base->iface.process_req = ciot_iface_process_req;
    base->iface.get_data = ciot_iface_get_data;
    base->iface.send_data = ciot_iface_send_data;
    base->iface.info.type = CIOT__IFACE_TYPE__IFACE_TYPE_BLE_SCN;

    base->recv.info = &base->recv_info;

#if CIOT_CONFIG_BLE_SCN_ADV_FIFO_SIZE
    ciot_ble_scn_base_init_fifo(&base->adv_fifo);
#endif

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_process_req(ciot_iface_t *iface, ciot_msg_t *req)
{
    ciot_ble_scn_t self = iface->ptr;

    switch (req->type)
    {
        case CIOT__MSG_TYPE__MSG_TYPE_START:
            return ciot_ble_scn_start(self, req->data->ble_scn->config);
        case CIOT__MSG_TYPE__MSG_TYPE_STOP:
            return ciot_ble_scn_stop(self);
        case CIOT__MSG_TYPE__MSG_TYPE_REQUEST:
            return ciot_ble_scn_process_req(self, req->data->ble_scn->request);
    default:
        break;
    }

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_get_data(ciot_iface_t *iface, ciot_msg_t *msg)
{
    ciot_ble_scn_base_t *self = iface->ptr;

    self->data.config = NULL;
    self->data.status = NULL;
    self->data.request = NULL;

    switch (msg->type)
    {
    case CIOT__MSG_TYPE__MSG_TYPE_CONFIG:
        self->data.config = &self->cfg;
        break;
    case CIOT__MSG_TYPE__MSG_TYPE_STATUS:
        self->data.status = &self->status;
        break;
    case CIOT__MSG_TYPE__MSG_TYPE_INFO:
        break;
    default:
        break;
    }

    self->iface.data.ble_scn = &self->data;
    msg->data = &self->iface.data;

    return CIOT_ERR__OK;
}

static ciot_err_t ciot_iface_send_data(ciot_iface_t *iface, uint8_t *data, int size)
{
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_ble_scn_process_req(ciot_ble_scn_t self, ciot_ble_scn_req_t *req)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(req);
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_ble_scn_get_cfg(ciot_ble_scn_t self, ciot_ble_scn_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    ciot_ble_scn_base_t *base = (ciot_ble_scn_base_t*)self;
    *cfg = base->cfg;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_ble_scn_get_status(ciot_ble_scn_t self, ciot_ble_scn_status_t *status)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(status);
    ciot_ble_scn_base_t *base = (ciot_ble_scn_base_t*)self;
    *status = base->status;
    return CIOT_ERR__OK;
}

ciot_err_t ciot_ble_scn_base_task(ciot_ble_scn_t self)
{
    #if CIOT_CONFIG_BLE_SCN_ADV_FIFO_SIZE
    CIOT_ERR_NULL_CHECK(self);
    ciot_ble_scn_base_t *base = (ciot_ble_scn_base_t*)self;
    ciot_ble_scn_adv_fifo_t *adv_fifo = &base->adv_fifo;
	if(base->status.fifo_len > 0)
	{
		if(adv_fifo->list[adv_fifo->rp].info->rssi != 0)
		{
			ciot_iface_event_t iface_event = {0};
            iface_event.type = CIOT_IFACE_EVENT_DATA;
            iface_event.data = (uint8_t*)&adv_fifo->list[adv_fifo->rp];
            ciot_iface_send_event(&base->iface, &iface_event);
			adv_fifo->list[adv_fifo->rp].info->rssi = 0;
			adv_fifo->rp++;
			base->status.fifo_len--;
			if(adv_fifo->rp >= CIOT_CONFIG_BLE_SCN_ADV_FIFO_SIZE)
			{
				adv_fifo->rp = 0;
			}
		}
	}
#endif
    return CIOT_ERR__OK;
}

ciot_err_t ciot_ble_scn_set_filter(ciot_ble_scn_t self, ciot_ble_scn_filter_fn *filter, void *args)
{
    CIOT_ERR_NULL_CHECK(self);
	CIOT_ERR_NULL_CHECK(filter);
    ciot_ble_scn_base_t *base = (ciot_ble_scn_base_t*)self;
    base->filter.handler = filter;
    base->filter.args = args;
    return CIOT_ERR__OK;
}

#if CIOT_CONFIG_BLE_SCN_ADV_FIFO_SIZE
static ciot_err_t ciot_ble_scn_base_init_fifo(ciot_ble_scn_adv_fifo_t *adv_fifo)
{
    for (size_t i = 0; i < CIOT_CONFIG_BLE_SCN_ADV_FIFO_SIZE; i++)
    {
        ciot__ble_scn_adv__init(&adv_fifo->list[i]);
        ciot__ble_scn_adv_info__init(&adv_fifo->data.infos[i]);
        adv_fifo->list[i].info = &adv_fifo->data.infos[i];
        adv_fifo->list[i].info->mac.data = adv_fifo->data.macs[i];
        adv_fifo->list[i].payload.data = adv_fifo->data.advs[i];
    }
    return CIOT_ERR__OK;
}
#endif
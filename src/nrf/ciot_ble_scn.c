/**
 * @file ciot_ble_scn.c
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "ciot_config.h"

#if CIOT_CONFIG_FEATURE_BLE_SCN && defined(CIOT_TARGET_NRF)

#if (NRF_SD_BLE_API_VERSION == 2 || NRF_SD_BLE_API_VERSION == 3)
#include "softdevice_handler.h"
#define BLE_GAP_ADV_SET_DATA_SIZE_MAX BLE_GAP_ADV_MAX_SIZE
#else
#include "nrf_sdh.h"
#include "nrf_sdh_soc.h"
#include "nrf_sdh_ble.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_log_default_backends.h"
#endif

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "app_error.h"
#include "app_error_weak.h"

#include <stdlib.h>

#include "ciot_ble_scn.h"

struct ciot_ble_scn
{
	ciot_iface_t iface;
	ciot_ble_scn_cfg_t cfg;
	ciot_ble_scn_status_t status;
#if NRF_SD_BLE_API_VERSION != 2 && NRF_SD_BLE_API_VERSION != 3
	uint8_t buffer[BLE_GAP_SCAN_BUFFER_MIN];
	ble_data_t scan_buffer;
#endif
	ble_gap_scan_params_t scan_params;
};

static void ciot_ble_scn_copy_mac(uint8_t dst[6], uint8_t src[6], bool reverse);

ciot_ble_scn_t ciot_ble_scn_new(void *handle)
{
	ciot_ble_scn_t self = calloc(1, sizeof(struct ciot_ble_scn));
	self->iface.base.ptr = self;
	self->iface.base.start = (ciot_iface_start_fn *)ciot_ble_scn_start;
	self->iface.base.stop = (ciot_iface_stop_fn *)ciot_ble_scn_stop;
	self->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_ble_scn_process_req;
	self->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_ble_scn_send_data;
	self->iface.base.cfg.ptr = &self->cfg;
	self->iface.base.cfg.size = sizeof(self->cfg);
	self->iface.base.status.ptr = &self->status;
	self->iface.base.status.size = sizeof(self->status);
	self->iface.info.type = CIOT_IFACE_TYPE_BLE_SCN;
	return self;
}

ciot_err_t ciot_ble_scn_start(ciot_ble_scn_t self, ciot_ble_scn_cfg_t *cfg)
{
	CIOT_NULL_CHECK(self);

	uint32_t error;

	if(cfg != NULL)
	{
		self->cfg = *cfg;
	}

	if (self->cfg.active && self->status.state == CIOT_BLE_SCN_STATE_ACTIVE)
	{
		return CIOT_OK;
	}

	if (!self->cfg.active && self->status.state == CIOT_BLE_SCN_STATE_PASSIVE)
	{
		return CIOT_OK;
	}

	error = sd_ble_gap_scan_stop();

	self->scan_params.interval = self->cfg.interval,
	self->scan_params.window = self->cfg.window,
	self->scan_params.active = self->cfg.active,
	self->scan_params.timeout = self->cfg.timeout;

#if NRF_SD_BLE_API_VERSION == 2 || NRF_SD_BLE_API_VERSION == 3
	error = sd_ble_gap_scan_start(&self->scan_params);
#else
	self->scan_buffer.p_data = self->buffer;
	self->scan_buffer.len = BLE_GAP_SCAN_BUFFER_MIN;
	error = sd_ble_gap_scan_start(&self->scan_params, &self->scan_buffer);
#endif

	if (error == NRF_SUCCESS)
	{
		self->status.state = self->cfg.active
								 ? CIOT_BLE_SCN_STATE_ACTIVE
								 : CIOT_BLE_SCN_STATE_PASSIVE;
	}

	return error;
}

ciot_err_t ciot_ble_scn_stop(ciot_ble_scn_t self)
{
	CIOT_NULL_CHECK(self);
	int err_code = sd_ble_gap_scan_stop();
	if(err_code == NRF_SUCCESS)
	{
		self->status.state = CIOT_BLE_SCN_STATE_IDLE;
	}
	return err_code;
}

ciot_err_t ciot_ble_scn_process_req(ciot_ble_scn_t self, ciot_ble_scn_req_t *req)
{
	return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_ble_scn_send_data(ciot_ble_scn_t self, uint8_t *data, int size)
{
	return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_ble_scn_handle_event(ciot_ble_scn_t self, void *event, void *event_args)
{
	const ble_evt_t *ev = event;

	ciot_iface_event_t iface_event = {0};
    ciot_ble_scn_status_t iface_status = self->status;

	switch (ev->header.evt_id)
	{
	case BLE_GAP_EVT_ADV_REPORT:
		ciot_ble_scn_copy_mac(iface_status.adv_info.mac, (uint8_t*)ev->evt.gap_evt.params.adv_report.peer_addr.addr, true);
		iface_status.adv_info.rssi = ev->evt.gap_evt.params.adv_report.rssi;
		iface_event.type = self->cfg.brigde_mode ? CIOT_IFACE_EVENT_DATA : CIOT_IFACE_EVENT_REQUEST;
#if NRF_SD_BLE_API_VERSION == 2 || NRF_SD_BLE_API_VERSION == 3
		iface_event.data = (ciot_iface_event_data_u*)ev->evt.gap_evt.params.adv_report.data;
		iface_event.size = ev->evt.gap_evt.params.adv_report.dlen;
#else
		iface_event.data = (ciot_iface_event_data_u*)ev->evt.gap_evt.params.adv_report.data.p_data;
		iface_event.size = ev->evt.gap_evt.params.adv_report.data.len;
		UNUSED_RETURN_VALUE(sd_ble_gap_scan_start(NULL, &self->scan_buffer));
#endif
		break;
	default:
		return CIOT_OK;
	}

	if(self->iface.event_handler != NULL)
	{
		self->status = iface_status;
		self->iface.event_handler(&self->iface, &iface_event, self->iface.event_args);
	}

	return CIOT_OK;
}

ciot_err_t ciot_ble_scn_get_adv_info(ciot_ble_scn_t self, ciot_ble_scn_adv_info_t *adv_info)
{
	CIOT_NULL_CHECK(self);
	CIOT_NULL_CHECK(adv_info);
	*adv_info = self->status.adv_info;
	return CIOT_OK;
}

static void ciot_ble_scn_copy_mac(uint8_t dst[6], uint8_t src[6], bool reverse)
{
	for (size_t i = 0; i < 6; i++)
	{
		dst[i] = reverse ? src[5-i] : src[i];
	}
}

#endif

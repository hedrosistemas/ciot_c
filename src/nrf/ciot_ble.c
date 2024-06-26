/**
 * @file ciot_ble.c
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "ciot_config.h"

#if CIOT_CONFIG_FEATURE_BLE_SCN && defined(CIOT_TARGET_NRF)

#define APP_BLE_OBSERVER_PRIO 3 /**< Application's BLE observer priority. You shouldn't need to modify this value. */
#define APP_BLE_CONN_CFG_TAG 1  /**< A tag identifying the SoftDevice BLE configuration. */

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

#include <stdlib.h>
#include <string.h>

#include "ciot_iface.h"
#include "ciot_ble.h"

struct ciot_ble
{
    ciot_iface_t iface;
    ciot_ble_cfg_t cfg;
    ciot_ble_status_t status;
    ciot_ble_ifaces_t ifaces;
    // ciot_ble_adv_t adv;
};

static void ciot_ble_power_management_init(ciot_ble_t self);
static void ciot_ble_stack_init(ciot_ble_t self);

#if (NRF_SD_BLE_API_VERSION == 2 || NRF_SD_BLE_API_VERSION == 3)
static void ciot_ble_evt_handler(ble_evt_t *p_ble_evt);
#else
static void ciot_ble_evt_handler(ble_evt_t const *p_ble_evt, void *p_context);
#endif

ciot_ble_t ble;

ciot_ble_t ciot_ble_new(void *handle)
{
    ciot_ble_t self = calloc(1, sizeof(struct ciot_ble));

    self->iface.base.ptr = self;
    self->iface.base.start = (ciot_iface_start_fn *)ciot_ble_start;
    self->iface.base.stop = (ciot_iface_stop_fn *)ciot_ble_stop;
    self->iface.base.process_req = (ciot_iface_process_req_fn *)ciot_ble_process_req;
    self->iface.base.send_data = (ciot_iface_send_data_fn *)ciot_ble_send_data;
    self->iface.base.cfg.ptr = &self->cfg;
    self->iface.base.cfg.size = sizeof(self->cfg);
    self->iface.base.status.ptr = &self->status;
    self->iface.base.status.size = sizeof(self->status);
    self->iface.info.type = CIOT_IFACE_TYPE_BLE;
    ble = self;
    return self;
}

ciot_err_t ciot_ble_start(ciot_ble_t self, ciot_ble_cfg_t *cfg)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(cfg);
    self->cfg = *cfg;

    if (self->status.state != CIOT_BLE_STATE_STARTED)
    {
        ciot_ble_power_management_init(self);
        ciot_ble_stack_init(self);
        self->status.state = CIOT_BLE_STATE_STARTED;
    }

    uint32_t error_code = ciot_ble_set_mac(self, cfg->mac);
    if (error_code == NRF_SUCCESS)
    {
        memcpy(self->status.info.sw_mac, self->cfg.mac, 6);
    }

    if(self->iface.base.req.type == CIOT_MSG_TYPE_START)
    {
        self->iface.base.req.status = CIOT_IFACE_REQ_STATUS_IDLE;
    }

    return CIOT_OK;
}

ciot_err_t ciot_ble_stop(ciot_ble_t self)
{
    return CIOT_ERR_NOT_IMPLEMENTED;
}

ciot_err_t ciot_ble_process_req(ciot_ble_t self, ciot_ble_req_t *req)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(req);
    switch (req->type)
    {
    case CIOT_BLE_REQ_UNKNOWN:
        return CIOT_ERR_INVALID_TYPE;
    case CIOT_BLE_REQ_SET_MAC:
        self->iface.base.req.response_size = CIOT_MSG_HEADER_SIZE + sizeof(req->type) + sizeof(req->data.set_mac);
        self->iface.base.req.status = CIOT_IFACE_REQ_STATUS_IDLE;
        return ciot_ble_set_mac(self, req->data.set_mac);
    }
    return CIOT_ERR_INVALID_TYPE;
}

ciot_err_t ciot_ble_send_data(ciot_ble_t self, uint8_t *data, int size)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_ble_task(ciot_ble_t self)
{
    CIOT_NULL_CHECK(self);
    // if (NRF_LOG_PROCESS() == false)
    // {
#if (NRF_SD_BLE_API_VERSION == 2 || NRF_SD_BLE_API_VERSION == 3)
    ret_code_t err_code = sd_app_evt_wait();
    APP_ERROR_CHECK(err_code);
#else
    nrf_pwr_mgmt_run();
#endif
    // }
    return CIOT_OK;
}

ciot_err_t ciot_ble_set_mac(ciot_ble_t self, uint8_t mac[6])
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(mac);

    if (ciot_ble_mac_is_valid(self, mac) == false)
    {
        return CIOT_ERR_INVALID_ARG;
    }

    ciot_err_t err = CIOT_OK;
    ble_gap_addr_t ble_addr = {0};
    memcpy(ble_addr.addr, mac, 6);

    ciot_ble_scn_stop(self->ifaces.scanner);

#if (NRF_SD_BLE_API_VERSION == 2)
    err = sd_ble_gap_address_set(BLE_GAP_ADDR_CYCLE_MODE_NONE, &ble_addr);
#else
    err = sd_ble_gap_addr_set(&ble_addr);
#endif

    if (err == CIOT_OK)
    {
        memcpy(self->cfg.mac, mac, 6);
        ciot_ble_get_mac(self, CIOT_BLE_MAC_TYPE_REAL, self->status.info.sw_mac);
        err = ciot_ble_scn_start(self->ifaces.scanner, NULL);
    }

    return err;
}

ciot_err_t ciot_ble_get_mac(ciot_ble_t self, ciot_ble_mac_type_t type, uint8_t mac[6])
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(mac);
    ciot_err_t err_code = CIOT_OK;

    switch (type)
    {
    case CIOT_BLE_MAC_TYPE_HARDWARE:
        memcpy(mac, self->status.info.hw_mac, 6);
        break;
    case CIOT_BLE_MAC_TYPE_SOFTWARE:
        memcpy(mac, self->status.info.sw_mac, 6);
        break;
    case CIOT_BLE_MAC_TYPE_REAL:
    {
        ble_gap_addr_t ble_addr;
#if (NRF_SD_BLE_API_VERSION == 2)
        err_code = sd_ble_gap_address_get(&ble_addr);
#else
        err_code = sd_ble_gap_addr_get(&ble_addr);
#endif
        memcpy(mac, ble_addr.addr, 6);
        break;
    }
    default:
        return CIOT_ERR_INVALID_TYPE;
    }

    return err_code;
}

ciot_err_t ciot_ble_set_ifaces(ciot_ble_t self, ciot_ble_ifaces_t *ifaces)
{
    CIOT_NULL_CHECK(self);
    CIOT_NULL_CHECK(ifaces);
    self->ifaces = *ifaces;
    return CIOT_OK;
}

bool ciot_ble_mac_is_valid(ciot_ble_t self, uint8_t mac[6])
{
    for (size_t i = 0; i < 6; i++)
    {
        if (mac[i] != 0)
        {
            return true;
        }
    }
    return false;
}

static void ciot_ble_power_management_init(ciot_ble_t self)
{
#if (NRF_SD_BLE_API_VERSION == 7)
    ret_code_t err_code;
    err_code = nrf_pwr_mgmt_init();
    APP_ERROR_CHECK(err_code);
#endif
}

static void ciot_ble_stack_init(ciot_ble_t self)
{
    uint32_t err_code;

#if (NRF_SD_BLE_API_VERSION == 2 || NRF_SD_BLE_API_VERSION == 3)
    nrf_clock_lf_cfg_t clock_lf_cfg = NRF_CLOCK_LFCLKSRC;

    // Initialize the SoftDevice handler module.
    SOFTDEVICE_HANDLER_INIT(&clock_lf_cfg, NULL);

    ble_enable_params_t ble_enable_params;
    err_code = softdevice_enable_get_default_config(0, 0, &ble_enable_params);
    APP_ERROR_CHECK(err_code);

    // Check the ram settings against the used number of links
    CHECK_RAM_START_ADDR(CENTRAL_LINK_COUNT, PERIPHERAL_LINK_COUNT);

    err_code = softdevice_enable(&ble_enable_params);
    APP_ERROR_CHECK(err_code);

    // Register with the SoftDevice handler module for BLE events.
    err_code = softdevice_ble_evt_handler_set(ciot_ble_evt_handler);
    APP_ERROR_CHECK(err_code);
#else

    // TODO: verificar como configurar o clock
    // nrf_clock_lf_cfg_t clock_lf_cfg = NRF_CLOCK_LFCLKSRC;

    // Initialize the SoftDevice handler module.
    err_code = nrf_sdh_enable_request();
    APP_ERROR_CHECK(err_code);

    // Configure the BLE stack using the default settings.
    // Fetch the start address of the application RAM.
    uint32_t ram_start = 0;
    err_code = nrf_sdh_ble_default_cfg_set(APP_BLE_CONN_CFG_TAG, &ram_start);
    APP_ERROR_CHECK(err_code);

    // Enable BLE stack.
    err_code = nrf_sdh_ble_enable(&ram_start);
    APP_ERROR_CHECK(err_code);

    NRF_SDH_BLE_OBSERVER(m_ble_observer, APP_BLE_OBSERVER_PRIO, ciot_ble_evt_handler, NULL);
#endif

    // Get hardware MAC
    err_code = ciot_ble_get_mac(self, CIOT_BLE_MAC_TYPE_REAL, self->status.info.hw_mac);

    APP_ERROR_CHECK(err_code);
}

#if (NRF_SD_BLE_API_VERSION == 2 || NRF_SD_BLE_API_VERSION == 3)
static void ciot_ble_evt_handler(ble_evt_t *p_ble_evt)
#else
static void ciot_ble_evt_handler(ble_evt_t const *p_ble_evt, void *p_context)
#endif
{
#if (NRF_SD_BLE_API_VERSION == 2 || NRF_SD_BLE_API_VERSION == 3)
    void *p_context = NULL;
#endif

    if (ble->ifaces.scanner != NULL)
    {
        ciot_ble_scn_handle_event(ble->ifaces.scanner, (void *)p_ble_evt, p_context);
    }

    // if (ble->ifaces.adv != NULL)
    // {
    //     ciot_ble_adv_handle_event(ble->ifaces.adv, (void *)p_ble_evt, p_context);
    // }
}

#endif

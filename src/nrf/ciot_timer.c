/**
 * @file ciot_timer.c
 * @author Wesley Santos (wesleypro37@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-01-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ciot_config.h"

#if CIOT_CONFIG_FEATURE_TIMER && defined(CIOT_TARGET_NRF)

#include <stdbool.h>
#include <stdint.h>

#include "nrf.h"
#include "nrf_drv_rtc.h"
#include "nrf_drv_clock.h"
#include "bsp.h"
#include "app_error.h"

#include "ciot_timer.h"

#define RTC_PRESCALER 4095
#define TIME_CONST (32768 / (RTC_PRESCALER + 1))
#define ONE_SECOND_TIMER (1 * TIME_CONST)
#define QUARTER_TIMER 1

typedef struct ciot_timer
{
    uint64_t now;
    ciot_timer_cfg_t cfg;
} ciot_timer_t;

static void hg_ble_rtc_event_handler(nrf_drv_rtc_int_type_t int_type);

static ciot_timer_t self;

static const nrf_drv_rtc_t rtc = NRF_DRV_RTC_INSTANCE(1);

ciot_err_t ciot_timer_start(ciot_timer_cfg_t *cfg)
{
    uint32_t err_code = NRF_SUCCESS;

    self.cfg = *cfg;

    err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);

    nrf_drv_clock_lfclk_request(NULL);

    nrf_drv_rtc_config_t config = NRF_DRV_RTC_DEFAULT_CONFIG;
    config.prescaler = RTC_PRESCALER;
    err_code = nrf_drv_rtc_init(&rtc, &config, hg_ble_rtc_event_handler);
    if (err_code)
    {
        return err_code;
    }

    err_code = nrf_drv_rtc_cc_set(&rtc, 0, ONE_SECOND_TIMER, true);
    if (err_code)
    {
        return err_code;
    }

    nrf_drv_rtc_enable(&rtc);

    return err_code;
}

uint64_t ciot_timer_get(void)
{
    return self.now;
}

bool ciot_timer_compare(uint64_t *timer, uint16_t interval)
{
    if (self.now > *timer)
    {
        *timer = self.now + interval;
        return true;
    }
    return false;
}

static void hg_ble_rtc_event_handler(nrf_drv_rtc_int_type_t int_type)
{
    switch (int_type)
    {
    case NRF_DRV_RTC_INT_COMPARE0:
        nrf_drv_rtc_counter_clear(&rtc);
        nrf_drv_rtc_cc_set(&rtc, 0, ONE_SECOND_TIMER, true); // unused error return value
        self.now++;
        if(self.cfg.event_handler != NULL)
        {
            self.cfg.event_handler(self.cfg.event_args);
        }
        break;
    default:
        break;
    }
}

#endif

/**
 * @file ciot_ota.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "ciot_ota.h"
#include "ciot_err.h"

struct ciot_ota
{
    ciot_ota_base_t base;
};

ciot_ota_t ciot_ota_new(void *handle)
{
    ciot_ota_t self = calloc(1, sizeof(struct ciot_ota));
    ciot_ota_init(self);
    return self;
}

ciot_err_t ciot_ota_start(ciot_ota_t self, ciot_ota_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_ota_stop(ciot_ota_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    return CIOT_ERR_NOT_SUPPORTED;
}

ciot_err_t ciot_ota_rollback(ciot_ota_t self)
{
    return CIOT_ERR_NOT_SUPPORTED;
}

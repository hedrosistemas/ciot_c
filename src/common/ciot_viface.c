/**
 * @file ciot_viface.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "ciot_viface.h"
#include "ciot_err.h"

// static const char *TAG = "ciot_viface";

struct ciot_viface
{
    ciot_viface_base_t base;
};

ciot_viface_t ciot_viface_new(void *handle, ciot_iface_type_t type)
{
    ciot_viface_t self = calloc(1, sizeof(struct ciot_viface));
    ciot_viface_init(self, type);
    return self;
}

ciot_err_t ciot_viface_start(ciot_viface_t self, ciot_viface_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    return CIOT__ERR__OK;
}

ciot_err_t ciot_viface_stop(ciot_viface_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    return CIOT__ERR__OK;
}

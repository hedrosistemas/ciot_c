/**
 * @file ciot_model.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "ciot_model.h"
#include "ciot_err.h"

// static const char *TAG = "ciot_model";

struct ciot_model
{
    ciot_model_base_t base;
};

ciot_model_t ciot_model_new(void *handle)
{
    ciot_model_t self = calloc(1, sizeof(struct ciot_model));
    ciot_model_init(self);
    return self;
}

ciot_err_t ciot_model_start(ciot_model_t self, ciot_model_cfg_t *cfg)
{
    CIOT_ERR_NULL_CHECK(self);
    CIOT_ERR_NULL_CHECK(cfg);
    return CIOT_ERR__NOT_IMPLEMENTED;
}

ciot_err_t ciot_model_stop(ciot_model_t self)
{
    CIOT_ERR_NULL_CHECK(self);
    return CIOT_ERR__NOT_IMPLEMENTED;
}

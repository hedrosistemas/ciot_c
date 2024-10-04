/**
 * @file ciot_err.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-06-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ciot_err.h"

#ifdef IDF_VER
#include "esp_err.h"
#endif

const char *ciot_err_to_message(ciot_err_t err)
{
    if (err >= 0 || err <= CIOT_ERR__FAIL)
    {
        return ciot_err__descriptor.values[err].name;
    }
    else
    {
#ifdef IDF_VER
        return esp_err_to_name(err);
#else
        return "UNKNOWN";
#endif
    }
}

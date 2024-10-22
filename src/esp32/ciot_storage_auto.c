/**
 * @file ciot_storage_auto.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-10-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "esp_spiffs.h"
#include "esp_partition.h"

#include "ciot_storage.h"
#include "ciot_storage_fs.h"
#include "ciot_storage_fat.h"
#include "ciot_storage_spiffs.c"

typedef struct ciot_storage_auto *ciot_storage_auto_t;

ciot_storage_t ciot_storage_auto_new(void)
{
    esp_partition_iterator_t iterator = esp_partition_find(ESP_PARTITION_TYPE_APP, ESP_PARTITION_SUBTYPE_ANY, FS_PARTITION_LABLE);
    const esp_partition_t* partition = esp_partition_get(iterator);

    switch (partition->subtype)
    {
    case ESP_PARTITION_SUBTYPE_DATA_FAT:
        return ciot_storage_fat_new();
    case ESP_PARTITION_SUBTYPE_DATA_SPIFFS:
        return ciot_storage_spiffs_new();
    default:
        return NULL;
    }
}

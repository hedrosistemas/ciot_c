/**
 * @file ciot_storage_fat.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-10-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdlib.h>
#include "ciot_storage.h"
#include "ciot_storage_fs.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "ciot_err.h"

#define FS_BASE_PATH "/fs"
#define FS_PARTITION_LABLE "storage"

#ifndef CONFIG_WL_SECTOR_SIZE
#define CONFIG_WL_SECTOR_SIZE 512
#endif //! CONFIG_WL_SECTOR_SIZE

struct ciot_storage_fat
{
    struct ciot_storage base;
    wl_handle_t handle;
};

typedef struct ciot_storage_fat *ciot_storage_fat_t;

static const char *TAG = "ciot_storage_fat";

static ciot_err_t ciot_storage_fat_init(ciot_storage_fat_t self);

ciot_storage_t ciot_storage_fat_new(void)
{
    ciot_storage_fat_t self = calloc(1, sizeof(struct ciot_storage_fat));
    ciot_storage_t base = &self->base;
    ciot_storage_fat_init(self);
    base->delete = ciot_storage_fs_delete;
    base->write_bytes = ciot_storage_fs_write_bytes;
    base->read_bytes = ciot_storage_fs_read_bytes;
    base->type = CIOT_STORAGE_TYPE_FS;
    return &self->base;
}

static ciot_err_t ciot_storage_fat_init(ciot_storage_fat_t self)
{
    esp_vfs_fat_mount_config_t cfg = {
        .max_files = 4,
        .format_if_mount_failed = true,
        .allocation_unit_size = CONFIG_WL_SECTOR_SIZE,
    };
    esp_err_t err = esp_vfs_fat_spiflash_mount_rw_wl(FS_BASE_PATH, FS_PARTITION_LABLE, &cfg, &self->handle);
    if(err)
    {
        CIOT_LOGE(TAG, "Error mounting fat: %s", esp_err_to_name(err));
        return CIOT_ERR_FAIL;
    }
    return CIOT_ERR_OK;
}

/**
 * @file ciot_storage_fs.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "ciot_storage_fs.h"

struct ciot_storage_fs
{
    struct ciot_storage base;
};

typedef struct ciot_storage_fs *ciot_storage_fs_t;

static ciot_err_t ciot_storage_fs_write_bytes(char *path, uint8_t *bytes, int size);
static ciot_err_t ciot_storage_fs_read_bytes(char *path, uint8_t *bytes, int *size);

ciot_storage_t ciot_storage_fs_new(void)
{
    ciot_storage_fs_t self = calloc(1, sizeof(struct ciot_storage_fs));
    ciot_storage_t base = &self->base;
    base->write_bytes = ciot_storage_fs_write_bytes;
    base->read_bytes = ciot_storage_fs_read_bytes;
    return &self->base;
}

static ciot_err_t ciot_storage_fs_write_bytes(char *path, uint8_t *bytes, int size)
{
    FILE *f = fopen(path, "wb");
    if(f != NULL)
    {
        fwrite(bytes, size, 1, f);
        fclose(f);
        return CIOT_ERR__OK;
    }

    return CIOT_ERR__FAIL;
}

static ciot_err_t ciot_storage_fs_read_bytes(char *path, uint8_t *bytes, int *size)
{
    FILE *f = fopen(path, "rb");
    if(f == NULL)
    {
        *size = 0;
        return CIOT_ERR__FAIL;
    }

    if(bytes == NULL)
    {
        fseek(f, 0, SEEK_END);
        *size = ftell(f);
        fclose(f);
        return CIOT_ERR__OK;
    }

    int idx = 0;
    int b;
    while ((b = fgetc(f)) != EOF) {
        bytes[idx++] = (uint8_t)b;
        if(idx == *size)
        {
            break;
        }
    }
    fclose(f);
    return CIOT_ERR__OK;
}

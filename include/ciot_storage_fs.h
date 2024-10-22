/**
 * @file ciot_storage_fs.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __CIOT_STORAGE_FS__H__
#define __CIOT_STORAGE_FS__H__

#include "ciot_storage.h"

ciot_storage_t ciot_storage_fs_new(void);
ciot_err_t ciot_storage_fs_delete(char *path);
ciot_err_t ciot_storage_fs_write_bytes(char *path, uint8_t *bytes, int size);
ciot_err_t ciot_storage_fs_read_bytes(char *path, uint8_t *bytes, int *size);

#endif  //!__CIOT_STORAGE_FS__H__

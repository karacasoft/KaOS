#ifndef __KAOS_FS_H__
#define __KAOS_FS_H__ 1

#include <kernel/sysdefs.h>
#include <fs/fs.h>

BOOL kaos_fs_guess(media_device_t device);

file_t get_file(const char *file_name, media_device_t device);

KAOS_ERR read_file(const file_t fd, uint8_t *in_data,
                   uint32_t offset, uint32_t length, media_device_t device);

KAOS_ERR write_file(const file_t fd, uint32_t *out_data,
                    uint32_t offset, uint32_t length, media_device_t device);

#endif
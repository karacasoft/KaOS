#ifndef __KAOS_FS_H__
#define __KAOS_FS_H__ 1

#include <kernel/sysdefs.h>
#include <fs/fs.h>

#define KAOS_FS_MAX_SIMULTANEOUS_OPEN_FILES 128
#define KAOS_FS_BLOCK_SIZE 4096

typedef struct __kaos_file_desc {
  char name[32];
  uint64_t created_time;
  uint64_t last_edited_time;
  uint32_t flags;
  uint64_t file_size;
  uint32_t block_ids[4];
  uint32_t allocated_blocks_pointer;
  uint8_t reserved[48];
} kaos_file_desc_t;

BOOL kaos_fs_guess(media_device_t *device);

KAOS_ERR kaos_setup_fs(media_device_t *device);

file_t kaos_open_file(char *file_name, media_device_t *device);

KAOS_ERR kaos_read_file(const file_t fd, uint8_t *in_data,
                   uint32_t offset, uint32_t length, media_device_t *device);

KAOS_ERR kaos_write_file(const file_t fd, uint32_t *out_data,
                    uint32_t offset, uint32_t length, media_device_t *device);

#endif
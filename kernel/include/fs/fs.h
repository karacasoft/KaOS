#ifndef __FS_H__
#define __FS_H__ 1

#include <kernel/sysdefs.h>
#include <media/media.h>

#include <stdint.h>
#include <stddef.h>

#define FILE_FLAG_DIRECTORY (0x00000001U)

#define MAX_SUPPORTED_FS_COUNT 5

typedef struct __file_struct {
  char *name;
  uint64_t created_time;
  uint64_t last_edited_time;
  uint32_t flags;
} file_t;

typedef struct __filesystem_def {
  char *name;
  BOOL (*guess)(media_device_t *device);
  file_t (*get_file)(const char *file_name, media_device_t *device);
  KAOS_ERR (*read_file)(const file_t fd, uint8_t *in_data, uint32_t offset, uint32_t length, media_device_t *device);
  KAOS_ERR (*write_file)(const file_t fd, uint32_t *out_data, uint32_t offset, uint32_t length, media_device_t *device);
} fs_def_t;

typedef struct __filesystem_handle {
  char *name;
  media_device_t *device;
  fs_def_t *def;
} fs_handle_t;

KAOS_ERR guess_file_system(media_device_t *device, fs_handle_t *out_fs_handle);
KAOS_ERR register_file_system(fs_def_t def);
KAOS_ERR initialize_file_system(media_device_t *device, BOOL format, fs_handle_t *out_fs_handle);


#endif
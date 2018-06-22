#ifndef __MEDIA_H__
#define __MEDIA_H__ 1

#include <kernel/sysdefs.h>

#include <stdint.h>
#include <stddef.h>

typedef struct __media_device {
  const char *name;
  KAOS_ERR (*read)(struct __media_device *dev, size_t address, uint8_t *in_data, size_t len);
  KAOS_ERR (*write)(struct __media_device *dev, size_t address, uint8_t *data, size_t len);
  KAOS_ERR (*get_total_medium_size)(struct __media_device *dev, uint32_t *total_size_in_blocks, uint32_t *block_size_in_bytes);
  void *device_info;
} media_device_t;

#endif
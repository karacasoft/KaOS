#ifndef __MEDIA_H__
#define __MEDIA_H__ 1

#include <kernel/sysdefs.h>

#include <stdint.h>
#include <stddef.h>

typedef struct __media_device {
  char *name;
  KAOS_ERR (*read)(struct __media_device *dev, size_t address, uint8_t *in_data, size_t len);
  KAOS_ERR (*write)(struct __media_device *dev, size_t address, uint8_t *data, size_t len);
  void *device_info;
} media_device_t;

#endif
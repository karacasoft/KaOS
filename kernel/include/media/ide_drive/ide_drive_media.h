#ifndef __PCI_DRIVE_MEDIA_H__
#define __PCI_DRIVE_MEDIA_H__ 1

#include <kernel/ide.h>
#include <kernel/sysdefs.h>
#include <media/media.h>

#include <stdint.h>
#include <stddef.h>

typedef struct __ide_drive_device_info {
  
} ide_drive_device_info_t;

KAOS_ERR media_ide_drive_read(size_t address, uint8_t *in_data, size_t len);
KAOS_ERR media_ide_drive_write(size_t address, uint8_t *data, size_t len);

#endif
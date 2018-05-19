#ifndef __PCI_DRIVE_MEDIA_H__
#define __PCI_DRIVE_MEDIA_H__ 1

#include <kernel/ide.h>
#include <kernel/sysdefs.h>
#include <media/media.h>

#include <stdint.h>
#include <stddef.h>

typedef struct __ide_drive_device_info {
  uint8_t drive_index;
  
} ide_drive_device_info_t;

KAOS_ERR media_ide_drive_read(media_device_t *dev, size_t address, uint8_t *in_data, size_t len);
KAOS_ERR media_ide_drive_write(media_device_t *dev, size_t address, uint8_t *data, size_t len);

KAOS_ERR media_ide_scan_ide_drives();

#endif
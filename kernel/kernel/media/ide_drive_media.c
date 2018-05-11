#include <kernel/ide.h>
#include <media/ide_drive/ide_drive_media.h>

KAOS_ERR media_ide_drive_read(media_device_t *dev, size_t address, uint8_t *in_data, size_t len) {
  uint8_t drive = ((ide_drive_device_info_t *)dev->device_info)->drive_index;

  
  
}

KAOS_ERR media_ide_drive_write(media_device_t *dev, size_t address, uint8_t *data, size_t len) {

}

KAOS_ERR media_ide_scan_ide_drives() {
  ide_initialize(0x1F0, 0x3F6, 0x170, 0x376, 0x000);
}
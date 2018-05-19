#include <kernel/ide.h>
#include <stdio.h>
#include <media/ide_drive/ide_drive_media.h>

extern struct ide_device ide_devices[4];

uint8_t drive_byte_buffer[4096] = {'t', 'e', 's', 't', };

media_device_t media_ide_devices[4];
ide_drive_device_info_t ide_device_infos[4];


static const char *media_ide_device_name = "IDE device";

void media_ide_print_buffer() {
  for (int i = 0; i < 128; ++i)
  {
    if((i % 16) == 0) printf("\n");
    printf("%x ", drive_byte_buffer[i]);
  }
  printf("\n");
}

KAOS_ERR media_ide_drive_read(media_device_t *dev, size_t address, uint8_t *in_data, size_t len) {
  KAOS_ERR err = KAOS_ERR_NO_ERROR;
  uint8_t drive = ((ide_drive_device_info_t *)dev->device_info)->drive_index;

  size_t i;
  size_t relative_address = address % 512;

  size_t read_len = 0;

  size_t sector_count = (len / 512) + ((relative_address + len) / 512);
  sector_count = (sector_count) ? sector_count : 1;
  while(sector_count > 8) {
    
    if((err = ide_ata_read_sector(drive, address / 512, 8, (uint32_t) drive_byte_buffer))) {
      printf("Read error code : %d", err);
    }
    for(i = 0; i < 512 * 8; i++) {
      in_data[read_len++] = drive_byte_buffer[relative_address + i];
    }
    relative_address = 0;
    len -= 512 * 8;
    address += 512 * 8;
    sector_count -= 8;
  }
  
  if((err = ide_ata_read_sector(drive, address / 512, sector_count, (uint32_t) drive_byte_buffer))) {
    printf("Read error code : %d", err);
  }
  for(i = 0; i < len; i++) {
    in_data[read_len++] = drive_byte_buffer[i];
  }

  return err;
}

KAOS_ERR media_ide_drive_write(media_device_t *dev, size_t address, uint8_t *data, size_t len) {
  KAOS_ERR err = KAOS_ERR_NO_ERROR;
  uint8_t drive = ((ide_drive_device_info_t *)dev->device_info)->drive_index;

  size_t i = 0;
  size_t relative_address;
  size_t start_sector_increment = 0;
  if(address % 512) {
    if((err = ide_ata_read_sector(drive, address / 512, 1, (uint32_t) drive_byte_buffer))) {
      printf("Read error code : %d", err);
    }
    relative_address = address % 512;
    for(i = 0; i < 512 - relative_address; i++) {
      drive_byte_buffer[relative_address + i] = data[i];
    }
    if((err = ide_ata_write_sector(drive, address / 512, 1, (uint32_t) drive_byte_buffer))) {
      printf("Write error code : %d", err);
    }
    start_sector_increment = 1;
  }

  len -= i;
  if(len == 0) return KAOS_ERR_NO_ERROR;

  uint8_t sector_count = ((len / 512) ? len / 512 : 1) - ((len % 512) ? 1 : 0);
  if(sector_count != 0) {
    if((err = ide_ata_write_sector(drive, (address / 512) + start_sector_increment, sector_count, (uint32_t)(data + i)))) {
      printf("Write error code : %d", err);
    }
  }

  size_t leftover_len = len % 512;
  

  if(leftover_len) {
    len += i;
    if((err = ide_ata_read_sector(drive, (address / 512) + start_sector_increment + sector_count,
                                  1, (uint32_t) drive_byte_buffer))) {
      printf("Read error code : %d", err);
    }
    for(i = 0; i < leftover_len; i++) {
      drive_byte_buffer[i] = data[len - leftover_len + i];
    }
    if((err = ide_ata_write_sector(drive, (address / 512) + start_sector_increment + sector_count,
                                   1, (uint32_t) drive_byte_buffer))) {
      printf("Write error code : %d", err);
    }
  }


  return err;
}

media_device_t *media_ide_get_device(uint8_t drive) {
  if(ide_devices[drive].reserved) {
    media_ide_devices[drive].name = media_ide_devices;
    media_ide_devices[drive].read = media_ide_drive_read;
    media_ide_devices[drive].write = media_ide_drive_write;

    ide_device_infos[drive].drive_index = drive;

    media_ide_devices[drive].device_info = &ide_device_infos[drive];
    return &media_ide_devices[drive];
  }
  return 0;
}

KAOS_ERR media_ide_scan_ide_drives() {
  ide_initialize(0x1F0, 0x3F6, 0x170, 0x376, 0x000);
  return KAOS_ERR_NO_ERROR;
}
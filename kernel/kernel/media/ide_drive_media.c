#include <kernel/ide.h>
#include <stdio.h>
#include <media/ide_drive/ide_drive_media.h>

extern struct ide_device ide_devices[4];

uint8_t drive_byte_buffer[4096] = {0};

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

  uint32_t sector_size = ((ide_drive_device_info_t *)dev->device_info)->sector_size_in_bytes;

  size_t i;
  size_t relative_address = address % sector_size;

  size_t read_len = 0;

  size_t sector_count = (len / sector_size) - ((relative_address + len % sector_size) / sector_size) + 2;
  sector_count = (sector_count) ? sector_count : 1;

  printf("Reading %d sectors, from address 0x%x\n", sector_count, address);

  while(sector_count > 8) {
    
    if((err = ide_ata_read_sector(drive, address / sector_size, 8, (uint32_t) drive_byte_buffer))) {
      printf("Read error code : %d\n", err);
    }
    for(i = 0; i < sector_size * 8; i++) {
      in_data[read_len++] = drive_byte_buffer[relative_address + i];
    }
    relative_address = 0;
    len -= sector_size * 8;
    address += sector_size * 8;
    sector_count -= 8;
  }
  
  if((err = ide_ata_read_sector(drive, address / sector_size, sector_count, (uint32_t) drive_byte_buffer))) {
    printf("Read error code : %d\n", err);
  }
  for(i = 0; i < len; i++) {
    in_data[read_len++] = drive_byte_buffer[i];
  }

  return err;
}

KAOS_ERR media_ide_drive_write(media_device_t *dev, size_t address, uint8_t *data, size_t len) {
  KAOS_ERR err = KAOS_ERR_NO_ERROR;

  uint32_t sector_size = ((ide_drive_device_info_t *)dev->device_info)->sector_size_in_bytes;

  uint8_t drive = ((ide_drive_device_info_t *)dev->device_info)->drive_index;

  size_t i = 0;
  size_t relative_address;
  size_t start_sector_increment = 0;
  // if address is not on a sector boundary,
  // read the sector, write the data on buffer, then write back the sector
  if(address % sector_size) {
    if((err = ide_ata_read_sector(drive, address / sector_size, 1, (uint32_t) drive_byte_buffer))) {
      printf("Read error code : %d\n", err);
    }
    relative_address = address % sector_size;
    for(i = 0; i < sector_size - relative_address && i < len; i++) {
      drive_byte_buffer[relative_address + i] = data[i];
    }
    if((err = ide_ata_write_sector(drive, address / sector_size, 1, (uint32_t) drive_byte_buffer))) {
      printf("Write error code : %d\n", err);
    }
    start_sector_increment = 1;
    len -= i;
  }

  if(len == 0) return KAOS_ERR_NO_ERROR;

  uint32_t sector_count = len / sector_size;

  printf("Writing %d sectors, from address 0x%x, leftover_len=%d\n", sector_count, address, len);

  if(sector_count != 0) {
    if((err = ide_ata_write_sector(drive, (address / sector_size) + start_sector_increment,
                                   sector_count, (uint32_t)(data + i)))) {
      printf("Write error code : %d\n", err);
    }
  }

  size_t leftover_len = len % sector_size;

  if(leftover_len) {
    len += i;
    printf("Reading sector %d\n", (address / sector_size) + start_sector_increment + sector_count);
    if((err = ide_ata_read_sector(drive, (address / sector_size) + start_sector_increment + sector_count,
                                  1, (uint32_t) drive_byte_buffer))) {
      printf("Read error code : %d\n", err);
    }
    for(i = 0; i < leftover_len; i++) {
      drive_byte_buffer[i] = data[len - leftover_len + i];
    }

    if((err = ide_ata_write_sector(drive, (address / sector_size) + start_sector_increment + sector_count,
                                   1, (uint32_t) drive_byte_buffer))) {
      printf("Write error code : %d\n", err);
    }
  }

  // Flush cache
  ide_ata_flush_cache(drive);

  return err;
}

media_device_t *media_ide_get_device(uint8_t drive) {
  if(ide_devices[drive].reserved) {
    media_ide_devices[drive].name = media_ide_device_name;
    media_ide_devices[drive].read = media_ide_drive_read;
    media_ide_devices[drive].write = media_ide_drive_write;
    media_ide_devices[drive].get_total_medium_size = media_ide_get_total_medium_size;

    ide_device_infos[drive].drive_index = drive;
    ide_device_infos[drive].sector_size_in_bytes = ide_devices[drive].bytes_per_sector;
    ide_device_infos[drive].total_size_in_sectors = ide_devices[drive].size;

    media_ide_devices[drive].device_info = &ide_device_infos[drive];
    return &media_ide_devices[drive];
  }
  return 0;
}

KAOS_ERR media_ide_get_total_medium_size(struct __media_device *dev,
                                         uint32_t *total_size_in_blocks,
                                         uint32_t *block_size_in_bytes) {
  ide_drive_device_info_t *ide_dev_info = (ide_drive_device_info_t *) dev->device_info;

  *block_size_in_bytes = ide_dev_info->sector_size_in_bytes;
  *total_size_in_blocks = ide_dev_info->total_size_in_sectors;

  printf("Block size: %d, Total block count: %d\n", *block_size_in_bytes, *total_size_in_blocks);

  return KAOS_ERR_NO_ERROR;
}

KAOS_ERR media_ide_scan_ide_drives() {
  ide_initialize(0x1F0, 0x3F6, 0x170, 0x376, 0x000);
  return KAOS_ERR_NO_ERROR;
}
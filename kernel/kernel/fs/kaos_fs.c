#include <stdio.h>
#include <fs/kaos/kaos_fs.h>

static const char kaos_fs_name[] = "KaOS File System";

fs_def_t kaos_fs_def;

// This file supports only KaOS File System v1.0.0

uint8_t kaos_fs_buffer[4096] = {0};

uint8_t kaos_fs_open_files_bitmap[KAOS_FS_MAX_SIMULTANEOUS_OPEN_FILES / 8];
kaos_file_desc_t kaos_fs_open_files[KAOS_FS_MAX_SIMULTANEOUS_OPEN_FILES];

uint32_t kaos_fs_get_next_empty_file_pointer();
uint32_t kaos_fs_find_file(media_device_t *device, const char *file_path, kaos_file_desc_t *out_file_desc);
uint32_t kaos_fs_read_fs_header(media_device_t *device, char *out_header);
uint32_t kaos_fs_read_block(media_device_t *device, uint32_t block);

uint32_t kaos_fs_get_next_empty_file_pointer() {
  int i = 0;
  int j = 0;
  while(kaos_fs_open_files_bitmap[i++] == 0xFF);
  while((kaos_fs_open_files_bitmap[i] << j++) & 0x80);
  return i * 8 + j;
}

KAOS_ERR kaos_fs_init() {
  kaos_fs_def.name = kaos_fs_name;
  kaos_fs_def.guess = kaos_fs_guess;
  kaos_fs_def.open_file = kaos_open_file;
  kaos_fs_def.read_file = kaos_read_file;
  kaos_fs_def.write_file = kaos_write_file;

  return KAOS_ERR_NO_ERROR;
}

BOOL kaos_fs_guess(media_device_t *device) {
  char data[10];
  device->read(device, 10 * 1024, data, 10);

  /*
  int i;
  for(i = 0; i < 10; i++) {
    printf("%x ", data[i]);
  }
  printf("\n");
  */
  

  if(data[0] == 'K'  && data[1] == 'a'  && data[2] == 'O'  && data[3] == 'S' &&
     data[4] == '\n' && data[5] == '\r' && data[6] == '\0' && data[7] == 0 &&
     data[8] == 0    && data[9] == 1) {
    return TRUE;
  }
  return FALSE;
}

KAOS_ERR kaos_setup_fs(media_device_t *device) {
  int i;
  memset(kaos_fs_buffer, 0, 512);

  for(i = 0; i < 10 * 1024; i += 512) {
    device->write(device, i, kaos_fs_buffer, 512);
  }

  char header[40] = {
    'K', 'a', 'O', 'S', '\n', '\r', 0, 0, 0, 1,
  };

  memcpy(&header[10], "MyKaOSVolume", 13);

  uint32_t total_size_in_blocks;
  uint32_t block_size;

  device->get_total_medium_size(device, &total_size_in_blocks, &block_size);

  uint32_t block_size_conversion = KAOS_FS_BLOCK_SIZE / block_size;
  uint32_t nr_kaos_blocks = (total_size_in_blocks - (10 * 1024 + KAOS_FS_BLOCK_SIZE) / block_size) / block_size_conversion;
  uint32_t required_bitmap_blocks = (nr_kaos_blocks / (KAOS_FS_BLOCK_SIZE * 8)) + 1;

  uint32_t start_of_blocks = (1024 * 10) / block_size + block_size_conversion
                             + required_bitmap_blocks * block_size_conversion;

  *((uint32_t *)&header[24]) = start_of_blocks;

  *((uint32_t *)&header[28]) = total_size_in_blocks;

  device->write(device, 10 * 1024, header, 40);

  nr_kaos_blocks -= required_bitmap_blocks;

  printf("KaOS block count : %d\n", nr_kaos_blocks);

  memset(kaos_fs_buffer, 0, 4096);

  kaos_fs_buffer[0] = 0x80;

  uint32_t bitmap_written = 0;
  while(nr_kaos_blocks > 4096 * 8) {
    device->write(device, 10 * 1024 + 4096 + bitmap_written++ * 4096, kaos_fs_buffer, 4096);
    kaos_fs_buffer[0] = 0x00;
    nr_kaos_blocks -= 4096 * 8;
  }

  if(nr_kaos_blocks > 0) {
    uint8_t passing_byte = 0xFF >> (nr_kaos_blocks % 8);

    kaos_fs_buffer[nr_kaos_blocks / 8] = passing_byte;
    //printf("DEBUG Bytes to write : %d\n", 4096 - (nr_kaos_blocks / 8 + 1));
    memset(&kaos_fs_buffer[nr_kaos_blocks / 8 + 1], 0xFF, 4096 - (nr_kaos_blocks / 8 + 1));
    
    device->write(device, 10 * 1024 + 4096 + bitmap_written++ * 4096, kaos_fs_buffer, 4096);
  }

  kaos_file_desc_t file_desc;
  memcpy(file_desc.name, "root", 5);
  file_desc.created_time = 0;
  file_desc.last_edited_time = 0;
  file_desc.flags = 1;
  file_desc.file_size = 0;
  memset(file_desc.block_ids, 0, 4 * sizeof(uint32_t));
  file_desc.allocated_blocks_pointer = 0;

  device->write(device, start_of_blocks * block_size, &file_desc, sizeof(kaos_file_desc_t));

  printf("Format done\n");

  return KAOS_ERR_NO_ERROR;
}

uint32_t kaos_fs_read_fs_header(media_device_t *device, char *out_header) {
  device->read(device, 10 * 1024, out_header, 40);
  return 0;
}

uint32_t kaos_fs_find_file(media_device_t *device, const char *file_path, kaos_file_desc_t *out_file_desc) {
  uint32_t path_pos = 0;
  uint32_t i;

  if(file_path[path_pos] == '/') path_pos++;
  while(file_path[path_pos + i++] != '/');


  return 0;
}

uint32_t kaos_fs_read_block(media_device_t *device, uint32_t block_id) {
  uint32_t total_size_in_blocks;
  uint32_t block_size;
  device->get_total_medium_size(device, &total_size_in_blocks, &block_size);

  char header[40];
  kaos_fs_read_fs_header(device, header);

  uint32_t start_of_blocks = *((uint32_t *)&header[24]);
  device->read(device, (start_of_blocks + block_id) * block_size, kaos_fs_buffer, KAOS_FS_BLOCK_SIZE);

  return 0;
}

file_t kaos_open_file(char *file_name, media_device_t *device) {
  file_t ret_file;
  uint32_t empty_file_pointer = kaos_fs_get_next_empty_file_pointer();

  kaos_file_desc_t *empty_file = &kaos_fs_open_files[empty_file_pointer];

  kaos_fs_read_block(device, 0);

  // get root directory
  *empty_file = *((kaos_file_desc_t *) kaos_fs_buffer);
  
  // start searching
  kaos_fs_find_file(device, file_name, empty_file);


  return ret_file;
}

KAOS_ERR kaos_read_file(const file_t fd, uint8_t *in_data,
                   uint32_t offset, uint32_t length, media_device_t *device) {
  UNUSED(fd);
  UNUSED(in_data);
  UNUSED(offset);
  UNUSED(length);
  UNUSED(device);
  return KAOS_ERR_NO_ERROR;
}

KAOS_ERR kaos_write_file(const file_t fd, uint32_t *out_data,
                    uint32_t offset, uint32_t length, media_device_t *device) {
  UNUSED(fd);
  UNUSED(out_data);
  UNUSED(offset);
  UNUSED(length);
  UNUSED(device);
  return KAOS_ERR_NO_ERROR;
}
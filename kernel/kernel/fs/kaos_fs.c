#include <stdio.h>
#include <fs/kaos/kaos_fs.h>

static const char kaos_fs_name[] = "KaOS File System";

fs_def_t kaos_fs_def;

// This file supports only KaOS File System v1.0.0

uint8_t kaos_fs_buffer[512] = {0};

KAOS_ERR kaos_fs_init() {
  kaos_fs_def.name = kaos_fs_name;
  kaos_fs_def.guess = kaos_fs_guess;
  kaos_fs_def.get_file = kaos_get_file;
  kaos_fs_def.read_file = kaos_read_file;
  kaos_fs_def.write_file = kaos_write_file;

  return KAOS_ERR_NO_ERROR;
}

BOOL kaos_fs_guess(media_device_t *device) {
  char data[10];
  device->read(device, 10 * 1024, data, 10);

  if(data[0] == 'K'  && data[1] == 'a'  && data[2] == 'O'  && data[3] == 'S' &&
     data[4] == '\n' && data[5] == '\r' && data[6] == '\0' && data[7] == 1 &&
     data[8] == 0    && data[9] == 0) {
    return TRUE;
  }
  return FALSE;
}

KAOS_ERR kaos_setup_fs(media_device_t *device) {
  int i;
  for(i = 0; i < 512; i++) kaos_fs_buffer[i] = 0;

  printf("Writing 10MB 0s...\n");

  for(i = 0; i < 10 * 1024; i += 512) {
    device->write(device, i, kaos_fs_buffer, 512);
  }

  printf("Writing signature...\n");

  const char fs_sig[10] = {
    'K', 'a', 'O', 'S', '\n', '\r', 0, 1, 0, 0,
  };

  device->write(device, 10 * 1024, fs_sig, 10);

  printf("Format done\n");

  return KAOS_ERR_NO_ERROR;
}

file_t kaos_get_file(const char *file_name, media_device_t *device) {
  // TODO get file
}

KAOS_ERR kaos_read_file(const file_t fd, uint8_t *in_data,
                   uint32_t offset, uint32_t length, media_device_t *device) {

}

KAOS_ERR kaos_write_file(const file_t fd, uint32_t *out_data,
                    uint32_t offset, uint32_t length, media_device_t *device) {

}
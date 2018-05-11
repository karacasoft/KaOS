#include <fs/kaos/kaos_fs.h>

static char kaos_fs_name[] = "KaOS File System";

// This file supports only KaOS File System v1.0.0

BOOL kaos_fs_guess(media_device_t device) {
  char data[10];
  device.read(&device, 0, data, 10);

  if(data[0] == 'K'  && data[1] == 'a'  && data[2] == 'O'  && data[3] == 'S' &&
     data[4] == '\n' && data[5] == '\r' && data[6] == '\0' && data[7] == 1 &&
     data[8] == 0    && data[9] == 0) {
    return TRUE;
  }
  return FALSE;
}

file_t get_file(const char *file_name, media_device_t device) {
  // TODO get file
}

KAOS_ERR read_file(const file_t fd, uint8_t *in_data,
                   uint32_t offset, uint32_t length, media_device_t device) {

}

KAOS_ERR write_file(const file_t fd, uint32_t *out_data,
                    uint32_t offset, uint32_t length, media_device_t device) {

}
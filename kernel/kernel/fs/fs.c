#include <fs/fs.h>
#include <stdio.h>

fs_def_t fs_defs[MAX_SUPPORTED_FS_COUNT];
static uint8_t fs_supported_fs_count = 0;

KAOS_ERR guess_file_system(media_device_t *device, fs_handle_t *out_fs_handle) {
  int i;
  for(i = 0; i < fs_supported_fs_count; i++) {
    if(fs_defs[i].guess(device)) {
      out_fs_handle->name = fs_defs[i].name;
      out_fs_handle->device = device;
      out_fs_handle->def = &fs_defs[i];
      return KAOS_ERR_NO_ERROR;
    }
  }
  return KAOS_ERR_NO_FS_DETECTED;
}

KAOS_ERR register_file_system(fs_def_t def) {
  if(MAX_SUPPORTED_FS_COUNT == fs_supported_fs_count) {
    return KAOS_ERR_OVERFLOW;
  }
  fs_defs[fs_supported_fs_count++] = def;
  return KAOS_ERR_NO_ERROR;
}

KAOS_ERR initialize_file_system(media_device_t *device, BOOL format, fs_handle_t *out_handle_ptr) {
  KAOS_ERR err = guess_file_system(device, out_handle_ptr);

  if(format && err == KAOS_ERR_NO_FS_DETECTED) {
    printf("No KaOS filesystem detected, formatting drive\n");
    if((err = kaos_setup_fs(device))) {
      return err;
    }
    if((err = guess_file_system(device, out_handle_ptr))) {
      return err;
    }
  } else {
    printf("KaOS filesystem detected\n");
  }

  return KAOS_ERR_NO_ERROR;
}
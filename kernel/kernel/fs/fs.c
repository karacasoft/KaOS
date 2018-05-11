#include <fs/fs.h>

fs_def_t kaos_fs_fs_defs[MAX_SUPPORTED_FS_COUNT];
static uint8_t kaos_fs_supported_fs_count = 0;

fs_handle_t guess_file_system(media_device_t device) {

}

KAOS_ERR register_file_system(fs_def_t def) {
  if(MAX_SUPPORTED_FS_COUNT == kaos_fs_supported_fs_count) {
    return KAOS_ERR_OVERFLOW;
  }
  kaos_fs_fs_defs[kaos_fs_supported_fs_count++] = def;
  return KAOS_ERR_NO_ERROR;
}
#ifndef __FS_H__
#define __FS_H__ 1

#include <kernel/sysdefs.h>

#include <stdint.h>
#include <stddef.h>

typedef struct __filesystem_def {
  char *name;
  KAOS_ERR (*write)(size_t address, uint8_t *data, size_t len);
  KAOS_ERR (*read)(size_t address, uint8_t *in_data, size_t len);
} fs_def_t;

fs_def_t guess_file_system();

#endif
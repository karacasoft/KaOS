#ifndef __PROC_H__
#define __PROC_H__ 1

#include <kernel/config.h>

#define PROCESS_FLAG_IS_USER 0x01
#define PROCESS_FLAG_

typedef struct proc_info {
  uint16_t cs;
  uint16_t ds;
} proc_info_t;

typedef struct proc {
  uint32_t *parent;
  uint32_t *previous;
  uint32_t *next;
  
  uint16_t id;
  uint8_t is_user : 1;
  uint8_t unused : 7;
  
  proc_info_t info;
  
} proc_t;

#endif
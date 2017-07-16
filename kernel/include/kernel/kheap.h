#ifndef __K_HEAP_H__
#define __K_HEAP_H__ 1

#include <stdint.h>

uint32_t kmalloc_a(uint32_t size);
uint32_t kmalloc_p(uint32_t size, uint32_t *phys);
uint32_t kmalloc_ap(uint32_t size, uint32_t *phys);
uint32_t kmalloc(uint32_t size);


#endif
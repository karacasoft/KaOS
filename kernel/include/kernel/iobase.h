#ifndef __IOBASE_H__
#define __IOBASE_H__ 1

#include <stddef.h>

void outb(uint16_t addr, uint8_t val);
uint8_t inb(uint16_t addr);

void outw(uint16_t addr, uint16_t val);
uint16_t inw(uint16_t addr);

void outl(uint16_t addr, uint32_t val);
uint32_t inl(uint16_t addr);

void insl(uint16_t addr, uint32_t *buffer, size_t len);

#endif
#ifndef __IOBASE_H__
#define __IOBASE_H__ 1

static void outb(uint16_t addr, uint8_t val);
static uint8_t inb(uint16_t addr);

static void outw(uint16_t addr, uint16_t val);
static uint16_t inw(uint16_t addr);

static void outl(uint16_t addr, uint32_t val);
static uint32_t inl(uint16_t addr);

#endif
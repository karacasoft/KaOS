#include <kernel/keyboard.h>
#include <kernel/iobase.h>

#include <stdint.h>

inline void enable_keyboard_interrupts() {
  outb(0x21, 0xfd);
}

uint8_t read_scan_code() {
  return inb(0x60);
}

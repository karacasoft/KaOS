#include <kernel/keyboard.h>
#include <kernel/iobase.h>

#include <stdint.h>

inline void enable_keyboard_interrupts() {
  outb(0x21, 0xfd);
}

uint8_t read_key_code() {
  uint8_t status = inb(0x64);
  
  if(status & 0x01) {
    return inb(0x60);
  }
  return 0;
}

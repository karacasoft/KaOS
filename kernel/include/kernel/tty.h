#ifndef __KAOS_VENG_TTY_H__
#define __KAOS_VENG_TTY_H__ 1

#include <stddef.h>
#include <stdint.h>

extern void tty_init(void);
extern void tty_putch(char ch);
extern void tty_write(const char *str, size_t size);
extern void tty_puts(const char *str);

extern void tty_enable_cursor();
extern void tty_disable_cursor();

extern void tty_update_cursor(size_t row, size_t col);
extern void tty_set_auto_update_cursor(uint8_t auto_update);

extern void tty_set_vga_mem_start(uint16_t address);

#endif
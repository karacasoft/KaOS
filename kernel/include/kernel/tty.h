#ifndef __KAOS_VENG_TTY_H__
#define __KAOS_VENG_TTY_H__ 1

#include <stddef.h>

extern void tty_init(void);
extern void tty_putch(char ch);
extern void tty_write(const char *str, size_t size);
extern void tty_puts(const char *str);

#endif
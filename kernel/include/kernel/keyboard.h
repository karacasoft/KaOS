#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__ 1

#include <stdint.h>



void enable_keyboard_interrupts();
uint8_t read_key_code();

#endif
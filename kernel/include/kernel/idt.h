#ifndef __KERNEL_IDT_H__
#define __KERNEL_IDT_H__ 1

#include <stddef.h>
#include <stdint.h>

void init_idt();
void set_interrupt_gate(size_t index, uint32_t offset, uint16_t selector, uint8_t type);

void lidt_all();

#endif
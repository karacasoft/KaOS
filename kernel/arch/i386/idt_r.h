#ifndef __IDT_H__
#define __IDT_H__ 1

#include <stdint.h>
#include <stddef.h>

extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();

struct regs
{
    uint16_t gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */
};

struct IDTDesc {
	uint16_t offset1;	// offset 0..15
	uint16_t selector;	// GDT segment selector
	uint8_t zero; 		// always zero
	uint8_t type_attr;	// type attributes
	uint16_t offset2;	// offset 16..31
};

void init_idt_table();

extern void _fault_handler(struct regs *r);
void lidt(void *base, uint16_t limit);

#endif
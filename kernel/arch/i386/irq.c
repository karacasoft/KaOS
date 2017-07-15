#include <stdio.h>
#include <kernel/idt.h>
#include <kernel/irq.h>
#include <kernel/iobase.h>

#include "irq_r.h"

void *irq_hooks[15] = {0};

void init_irq()
{
	setup_pic(32, 40);
	
	set_interrupt_gate(32, (unsigned)_irq0, 0x10, 0x8E);
	set_interrupt_gate(33, (unsigned)_irq1, 0x10, 0x8E);
	set_interrupt_gate(34, (unsigned)_irq2, 0x10, 0x8E);
	set_interrupt_gate(35, (unsigned)_irq3, 0x10, 0x8E);
	set_interrupt_gate(36, (unsigned)_irq4, 0x10, 0x8E);
	set_interrupt_gate(37, (unsigned)_irq5, 0x10, 0x8E);
	set_interrupt_gate(38, (unsigned)_irq6, 0x10, 0x8E);
	set_interrupt_gate(39, (unsigned)_irq7, 0x10, 0x8E);
	
	set_interrupt_gate(40, (unsigned)_irq8, 0x10, 0x8E);
	set_interrupt_gate(41, (unsigned)_irq9, 0x10, 0x8E);
	set_interrupt_gate(42, (unsigned)_irq10, 0x10, 0x8E);
	set_interrupt_gate(43, (unsigned)_irq11, 0x10, 0x8E);
	set_interrupt_gate(44, (unsigned)_irq12, 0x10, 0x8E);
	set_interrupt_gate(45, (unsigned)_irq13, 0x10, 0x8E);
	set_interrupt_gate(46, (unsigned)_irq14, 0x10, 0x8E);
	set_interrupt_gate(47, (unsigned)_irq15, 0x10, 0x8E);
}

void hook_irq_handler(int index, void *handler)
{
	irq_hooks[index] = handler;
}

void setup_pic(int offset1, int offset2) {
	unsigned char m1, m2;
	
	m1 = 0x01;
	m2 = 0xff;
	
	outb(PIC1_COMMAND, 0x11);
	outb(PIC2_COMMAND, 0x11);
	
	outb(PIC1_DATA, offset1);
	outb(PIC2_DATA, offset2);
	
	outb(PIC1_DATA, 4);
	outb(PIC2_DATA, 2);
	
	outb(PIC1_DATA, 0x01);
	outb(PIC2_DATA, 0x01);
	
	outb(PIC1_DATA, m1);
	outb(PIC2_DATA, m2);
	
} 

inline void enable_interrupts() {
	asm volatile("sti");
}

inline void disable_interrupts() {
	asm volatile("cli");
}



#ifdef __cplusplus
extern "C" {
#endif

void _irq_handler(struct regs *r)
{
	printf("Interrupt:  %d\n", r->int_no);
	if(r->int_no > 31 && r->int_no < 48)
	{
		//printf("Interrupt:  %d\n", r->int_no);
		void (*handle)(void);
		if(irq_hooks[r->int_no - 32]) {
			handle = irq_hooks[r->int_no - 32];
			handle();
		}
		
		// Send end of interrupt to PIC chips
		if(r->int_no >= 40) {
			// 0x20 = PIC end of interrupt command
			outb(PIC2_COMMAND, 0x20);
		}
		outb(PIC1_COMMAND, 0x20);
	}
}


#ifdef __cplusplus
}
#endif

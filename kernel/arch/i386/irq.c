#include <kernel/idt.h>
#include <kernel/irq.h>

#include "irq_r.h"

void *irq_hooks[15];

void init_irq()
{
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

#ifdef __cplusplus
extern "C" {
#endif

void _irq_handler(struct regs *r)
{
	if(r->int_no > 31 && r->int_no < 48)
	{
		void (*handle)(void);
		handle = irq_hooks[r->int_no - 32];
		handle();
	}
}


#ifdef __cplusplus
}
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <kernel/idt.h>

#include "idt_r.h"

struct IDTDesc idt_entries[256];
//TODO: delet dis
/* fields */
/* uint16 offset1 */
/* uint16 selector */
/* uint8 zero */
/* uint8 type_attr */
/* uint16 offset2 */

const char *error_messages[] = {
	"Divison by Zero Exception",
	"Debug",
	"Non-maskable Interrupt",
	"Breakpoint",
	"Overflow Exception",
	"Bound Range Exceeded Exception",
	"Invalid Opcode Exception",
	"Device Not Available Exception",
	"Double Fault",
	"Coprocessor Fault Exception", // Not used after 486
	"Invalid TSS Exception",
	"Segment Not Present",
	"Stack Segment Fault",
	"General Protection Fault",
	"Page Fault Exception",
	"r", // Reserved Exception Slot,
	"Floating Point Exception",
	"Alignment Check",
	"Machine Check",
	"SIMD Floating Exception",
	"Virtualization Exception",
	"r", //21
	"r", //22
	"r", //23
	"r", //24
	"r", //25
	"r", //26
	"r", //27
	"r", //28
	"r", //29
	"Security Exception",
	"r", //31
};

void init_idt_table()
{
	for(size_t i = 0; i < 256; ++i)
	{
		idt_entries[i].offset1 = 0;
		idt_entries[i].selector = 0;
		idt_entries[i].zero = 0;
		idt_entries[i].type_attr = 0;
		idt_entries[i].offset2 = 0;
	}
}

void set_interrupt_gate(size_t index, unsigned long offset, uint16_t selector, uint8_t type)
{
	uint16_t offset_l = (uint16_t)(offset & 0xffff);
	uint16_t offset_h = (uint16_t)((offset >> 16));

	idt_entries[index].offset1 = offset_l;
	idt_entries[index].offset2 = offset_h;
	idt_entries[index].selector = selector;
	idt_entries[index].type_attr = type;
}

void lidt(void *base, uint16_t limit)
{
	struct {
		uint16_t limit;
		void *base;
	} __attribute__((packed)) idt_table_pointer = { limit, base };

	asm volatile ( "lidt %0" :  : "m"(idt_table_pointer) );
}

void init_idt()
{
	init_idt_table();

	set_interrupt_gate(0, (unsigned)_isr0, 0x10, 0x8E);
	set_interrupt_gate(1, (unsigned)_isr1, 0x10, 0x8E);
	set_interrupt_gate(2, (unsigned)_isr2, 0x10, 0x8E);
	set_interrupt_gate(3, (unsigned)_isr3, 0x10, 0x8E);
	set_interrupt_gate(4, (unsigned)_isr4, 0x10, 0x8E);
	set_interrupt_gate(5, (unsigned)_isr5, 0x10, 0x8E);
	set_interrupt_gate(6, (unsigned)_isr6, 0x10, 0x8E);
	set_interrupt_gate(7, (unsigned)_isr7, 0x10, 0x8E);
	set_interrupt_gate(8, (unsigned)_isr8, 0x10, 0x8E);
	set_interrupt_gate(9, (unsigned)_isr9, 0x10, 0x8E);
	set_interrupt_gate(10, (unsigned)_isr10, 0x10, 0x8E);
	set_interrupt_gate(11, (unsigned)_isr11, 0x10, 0x8E);
	set_interrupt_gate(12, (unsigned)_isr12, 0x10, 0x8E);
	set_interrupt_gate(13, (unsigned)_isr13, 0x10, 0x8E);
	set_interrupt_gate(14, (unsigned)_isr14, 0x10, 0x8E);
	set_interrupt_gate(15, (unsigned)_isr15, 0x10, 0x8E);

	set_interrupt_gate(16, (unsigned)_isr16, 0x10, 0x8E);
	set_interrupt_gate(17, (unsigned)_isr17, 0x10, 0x8E);
	set_interrupt_gate(18, (unsigned)_isr18, 0x10, 0x8E);
	set_interrupt_gate(19, (unsigned)_isr19, 0x10, 0x8E);
	set_interrupt_gate(20, (unsigned)_isr20, 0x10, 0x8E);
	set_interrupt_gate(21, (unsigned)_isr21, 0x10, 0x8E);
	set_interrupt_gate(22, (unsigned)_isr22, 0x10, 0x8E);
	set_interrupt_gate(23, (unsigned)_isr23, 0x10, 0x8E);
	set_interrupt_gate(24, (unsigned)_isr24, 0x10, 0x8E);
	set_interrupt_gate(25, (unsigned)_isr25, 0x10, 0x8E);
	set_interrupt_gate(26, (unsigned)_isr26, 0x10, 0x8E);
	set_interrupt_gate(27, (unsigned)_isr27, 0x10, 0x8E);
	set_interrupt_gate(28, (unsigned)_isr28, 0x10, 0x8E);
	set_interrupt_gate(29, (unsigned)_isr29, 0x10, 0x8E);
	set_interrupt_gate(30, (unsigned)_isr30, 0x10, 0x8E);
	set_interrupt_gate(31, (unsigned)_isr31, 0x10, 0x8E);

	lidt(&idt_entries, 256 * (sizeof(struct IDTDesc)) - 1);
}

#ifdef __cplusplus
extern "C" {
#endif

void _fault_handler(struct regs *r) {
	if (r->int_no < 32) {
		printf("%s\n", error_messages[r->int_no]);
		printf("System Halted\n");
		while(1); // never escape
	}
}


#ifdef __cplusplus
}
#endif

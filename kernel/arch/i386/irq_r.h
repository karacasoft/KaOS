#ifndef __IRQ_R_H__
#define __IRQ_R_H__ 1

#include "idt_r.h"

#define IRQ_TIMER 		0x00
#define IRQ_KEYBOARD		0x01
#define IRQ_CASCADE		0x02 // Cascaded into chip 2 (never raised)
#define IRQ_SERIAL_PORT_2	0x03 // Shared with serial port 4, if present
#define IRQ_SERIAL_PORT		0x04 // Shared with serial port 3, if present
#define IRQ_PARALLEL_PORT_2	0x05
#define IRQ_FLOPPY		0x06
#define IRQ_PARALLEL_PORT	0x07

#define IRQ_CLOCK		0x08
#define IRQ_ACPI		0x09

#define IRQ_MOUSE		0x12
#define IRQ_COPROCESSOR		0x13
#define IRQ_PRIMARY_ATA_CH	0x14
#define IRQ_SECONDARY_ATA_CH	0x15



#define PIC1 0x20
#define PIC2 0xA0

#define PIC1_COMMAND PIC1
#define PIC2_COMMAND PIC2

#define PIC1_DATA (PIC1+1)
#define PIC2_DATA (PIC2+1)

extern void _irq0();
extern void _irq1();
extern void _irq2();
extern void _irq3();
extern void _irq4();
extern void _irq5();
extern void _irq6();
extern void _irq7();
extern void _irq8();
extern void _irq9();
extern void _irq10();
extern void _irq11();
extern void _irq12();
extern void _irq13();
extern void _irq14();
extern void _irq15();

extern void _irq_handler(struct regs *r);

extern void setup_pic(int offset1, int offset2);

#endif
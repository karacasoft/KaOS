#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/irq.h>
#include <kernel/idt.h>

#include <kernel/config.h>

void keyboardHandler(void) {
	printf("wowowowKeyboard\n");
}

int kmain(void)
{
	/* Initialize tty */
	tty_init();
	init_idt();
	init_irq();

	hook_irq_handler(1, keyboardHandler);

	lidt_all();
	
	enable_interrupts();

	printf("KaOS Operating System \n");
	printf("Version %s\n", FULL_VERSION_NAME);

	//asm volatile("int $0x21");

	/* Do nothing! Forever. */
	while(1);
	return 0;
}

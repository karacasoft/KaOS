#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/irq.h>
#include <kernel/idt.h>
#include <kernel/paging.h>
#include <kernel/ide.h>

#include <kernel/scancodes.h>

#include <kernel/config.h>

void keyboardHandler(void) {
	char key_code = get_char();
	if(key_code != 0x00) {
		putchar(key_code);
	}
}

void ide_int_test(void) {
	printf("ide interrupt wow");
}

int kmain(void)
{
	/* Initialize tty */
	tty_init();
	init_idt();
	init_irq();

	hook_irq_handler(1, keyboardHandler);
	hook_irq_handler(14, ide_int_test);

	lidt_all();
	
	enable_interrupts();
	
	initialize_paging();
	printf("KaOS Operating System \n");
	printf("Version %s\n", FULL_VERSION_NAME);

	tty_enable_cursor();
	tty_set_auto_update_cursor(1);
	
	//ide_initialize(0x1F0, 0x3F6, 0x170, 0x376, 0x000);
	
	printf("$ ");

	//asm volatile("int $0x21");

	/* Do nothing! Forever. */
	while(1);
	return 0;
}

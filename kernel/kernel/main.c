#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/irq.h>
#include <kernel/idt.h>
#include <kernel/paging.h>

#include <kernel/scancodes.h>

#include <kernel/config.h>

void keyboardHandler(void) {
	char key_code = get_char();
	if(key_code != 0x00) {
		putchar(key_code);
	}
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
	
	initialize_paging();
	printf("KaOS Operating System \n");
	printf("Version %s\n", FULL_VERSION_NAME);

	tty_enable_cursor();
	tty_set_auto_update_cursor(1);
	printf("$ ");

	//asm volatile("int $0x21");

	/* Do nothing! Forever. */
	while(1);
	return 0;
}

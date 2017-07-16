#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/irq.h>
#include <kernel/idt.h>
#include <kernel/paging.h>

#include <kernel/keyboard.h>

#include <kernel/config.h>

void keyboardHandler(void) {
	uint8_t keyCode = read_key_code();
	
	printf("KeyCode: %d\n", keyCode);
	
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

	int a = 20;
	printf("wow %d\n", a);
	printf("address of a: %d\n", (uint32_t) &a);

	uint32_t *ptr = (uint32_t*)0x0C000000;
	uint32_t do_page_fault = *ptr;

	printf("%d", do_page_fault);

	//asm volatile("int $0x21");

	/* Do nothing! Forever. */
	while(1);
	return 0;
}

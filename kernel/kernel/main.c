#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/irq.h>
#include <kernel/idt.h>

#include <kernel/config.h>

int kmain(void)
{
	/* Initialize tty */
	tty_init();
	init_idt();
	init_irq();

	printf("KaOS Operating System \n");
	printf("Version %s\n", FULL_VERSION_NAME);

	/* Do nothing! Forever. */
	while(1);
	return 0;
}

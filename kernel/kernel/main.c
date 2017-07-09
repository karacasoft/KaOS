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

	int a = 1 / 0;
	
	printf("%d", a);

	/* Do nothing! Forever. */
	while(1);
	return 0;
}
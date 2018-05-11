#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/irq.h>
#include <kernel/idt.h>
#include <media/ide_drive/ide_drive_media.h>
#include <kernel/paging.h>
#include <kernel/timer.h>

#include <kernel/scancodes.h>

#include <kernel/config.h>

void scanHardwareChanges();

unsigned char buffer[2048] = {0};

void keyboardHandler(void) {
	char key_code = get_char();
	if(key_code != 0x00) {
		putchar(key_code);
	}
}

void scanHardwareChanges() {
	printf("Searching for IDE drives...\n");
	media_ide_scan_ide_drives();

}

int kmain(void)
{
	tty_init();
	init_idt();
	init_irq();
	init_timer();

	hook_irq_handler(1, keyboardHandler);

	lidt_all();

	enable_interrupts();

	initialize_paging();
	printf("KaOS Operating System \n");
	printf("Version %s\n", FULL_VERSION_NAME);

	tty_enable_cursor();
	tty_set_auto_update_cursor(1);

	scanHardwareChanges();

	// Reads disk drive 1
	//ide_atapi_read_sector(1, 0, 1, (uint32_t)buffer);

	// printf("Read complete!\n");
	// int i, j;
	// for(j = 0; j < 16; j++) {
	// 	for(i = 0; i < 16; i++) {
	// 		printf("%x ", buffer[j * 16 + i]);
	// 	}
	// 	printf("\n");
	// }

	printf("$ ");



	//asm volatile("int $0x21");

	/* Do nothing! Forever. */
	while(1);
	return 0;
}

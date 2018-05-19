#include <stdio.h>
#include <fs/fs.h>
#include <fs/kaos/kaos_fs.h>
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

const char my_write_buffer[512] = "test buffer karacasoft deneme lol";

media_device_t *main_media_device;

extern fs_def_t kaos_fs_def;

void keyboardHandler(void) {
	char key_code = get_char();
	if(key_code != 0x00) {
		putchar(key_code);
	}
}

void scanHardwareChanges() {
	printf("Searching for IDE drives...\n");
	media_ide_scan_ide_drives();
	int i;
	for(i = 0; i < 4; i++) {
		media_device_t *device = media_ide_get_device(i);
		if(device != 0) {
			main_media_device = device;
			break;
		}
	}
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

	kaos_fs_init();
	register_file_system(kaos_fs_def);

	if(main_media_device) {
		fs_handle_t handle;
		initialize_file_system(main_media_device, 1, &handle);
	}

	printf("$ ");



	//asm volatile("int $0x21");

	/* Do nothing! Forever. */
	while(1);
	return 0;
}

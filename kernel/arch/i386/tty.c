#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t cursorX;
static size_t cursorY;
static uint8_t tty_color;
static uint16_t* tty_buffer;

void tty_init(void) {
	cursorX = 0;
	cursorY = 0;
	tty_color = vga_color_entry(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	tty_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; ++y)
	{
		for (size_t x = 0; x < VGA_WIDTH; ++x)
		{
			const size_t index = y * VGA_WIDTH + x;
			tty_buffer[index] = vga_entry(' ', tty_color);
		}
	}
}

void tty_putch(char ch) {
	const size_t index = cursorY * VGA_WIDTH + cursorX;
	if(ch == '\n')
	{
		cursorX = 0;
		cursorY++;
	} else {
		tty_buffer[index] = vga_entry(ch, tty_color);
	
		if(++cursorX >= VGA_WIDTH) {
			cursorX = 0;
			if(++cursorY >= VGA_HEIGHT) {
				// terminal scroll
				cursorY = 0;
			}
		}
	}
}

void tty_write(const char *str, size_t size)
{
	for(size_t i = 0; i < size; i++) 
	{
		tty_putch(str[i]);
	}
}

void tty_puts(const char *str) {
	for (size_t i = 0; i < strlen(str); ++i)
	{
		tty_putch(str[i]);
	}
}

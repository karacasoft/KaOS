#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <kernel/tty.h>
#include <stdio.h>

#include "vga.h"
#include "iobase.h"

#define VGA_FLAG_CURSOR_VISIBLE (1 << 0)
#define VGA_FLAG_AUTO_UPDATE_CURSOR (1 << 1)

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t cursorX;
static size_t cursorY;
static uint8_t tty_color;
static uint16_t* tty_buffer;

static uint8_t vga_flags = 0x01;

static uint16_t video_io_port;

void tty_scroll() {
	for (size_t i = 0; i < VGA_HEIGHT - 1; i++) {
		memcpy(tty_buffer + (i * VGA_WIDTH), 
			tty_buffer + ((i + 1) * VGA_WIDTH), VGA_WIDTH * 2);
	}
	for (size_t i = 0; i < VGA_WIDTH; i++) {
		tty_buffer[24*VGA_WIDTH + i] = vga_entry(' ', tty_color);
	}
}

void tty_update_cursor(size_t row, size_t col) {
	if(vga_flags & VGA_FLAG_CURSOR_VISIBLE) {
		size_t position = (row * VGA_WIDTH) + col;
		
		outb(video_io_port, 0x0F);
		outb(video_io_port + 1, (uint8_t) (position & 0xFF));
		
		outb(video_io_port, 0x0E);
		outb(video_io_port + 1, (uint8_t) ((position >> 8) & 0xFF));
	}
}

void tty_disable_cursor() {
	vga_flags &= (~VGA_FLAG_CURSOR_VISIBLE);
	
	outb(video_io_port, 0x0A);
	outb(video_io_port + 1, 0x2D);
}

void tty_enable_cursor() {
	vga_flags |= VGA_FLAG_CURSOR_VISIBLE;
	
	outb(video_io_port, 0x0A);
	outb(video_io_port + 1, 0x0D);
}

void tty_set_auto_update_cursor(uint8_t auto_update) {
	if(auto_update) {
		vga_flags |= VGA_FLAG_AUTO_UPDATE_CURSOR;
	} else {
		vga_flags &= (~VGA_FLAG_AUTO_UPDATE_CURSOR);
	}
}

void tty_init(void) {
	video_io_port = *((uint16_t*) 0x0463);
	
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
	
	tty_disable_cursor();
}

void tty_putch(char ch) {
	const size_t index = cursorY * VGA_WIDTH + cursorX;
	if(ch == '\n')
	{
		cursorX = 0;
		if(++cursorY >= VGA_HEIGHT) {
			tty_scroll();
			cursorY--;
		}
	} else if(ch == '\t') {
		cursorX += TAB_SIZE - (cursorX % TAB_SIZE);
		if(cursorX >= VGA_WIDTH) {
			cursorX = 0;
			if(++cursorY >= VGA_HEIGHT) {
				tty_scroll();
				cursorY--;
			}
		}
	} else if(ch == '\b') {
		if(--cursorX < 0) {
			cursorX = VGA_WIDTH - 1;
			if(--cursorY < 0) {
				cursorY = 0;
			}
		}
		tty_buffer[cursorY * VGA_WIDTH + cursorX] = vga_entry(' ', tty_color);
	} else if(ch == '\r') {
		cursorX = 0;
	} else {
		tty_buffer[index] = vga_entry(ch, tty_color);
		
		if(++cursorX >= VGA_WIDTH) {
			cursorX = 0;
			if(++cursorY >= VGA_HEIGHT) {
				tty_scroll();
				cursorY--;
			}
		}
	}
	if(vga_flags & VGA_FLAG_AUTO_UPDATE_CURSOR) {
		tty_update_cursor(cursorY, cursorX);
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

#include <stdint.h>
#include <stddef.h>
#include "iobase.h"

void outb(uint16_t addr, uint8_t val)
{
	asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(addr) );
}

uint8_t inb(uint16_t addr)
{
	uint8_t ret;
	asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(addr) );
	return ret;
}

void outw(uint16_t addr, uint16_t val)
{
	asm volatile ( "outw %0, %1" : : "a"(val), "Nd"(addr) );
}

uint16_t inw(uint16_t addr)
{
	uint16_t ret;
	asm volatile ( "inw %1, %0" : "=a"(ret) : "Nd"(addr) );
	return ret;
}

void outl(uint16_t addr, uint32_t val)
{
	asm volatile ( "outl %0, %1" : : "a"(val), "Nd"(addr) );
}

uint32_t inl(uint16_t addr)
{
	uint32_t ret;
	asm volatile ( "inl %1, %0" : "=a"(ret) : "Nd"(addr) );
	return ret;
}

void insl(uint16_t addr, uint32_t *buffer, size_t len) {
	asm volatile ( "mov %0, %%edi\n\t"
								 "mov %1, %%edx\n\t"
								 "mov %2, %%ecx\n\t"
								 "rep insl\n\t"
							 : 
							 : "g"(buffer), "g"(addr), "g"(len)
							 : "%edi", "%edx", "%ecx", "memory"
							 );
}


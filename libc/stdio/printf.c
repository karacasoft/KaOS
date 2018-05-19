#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool print(const char *data, size_t length)
{
	const unsigned char *bytes = (const unsigned char *) data;
	for(size_t i = 0; i < length; i++)
	{
		if(putchar(bytes[i]) == EOF)
		{
			return false;
		}
	}
	return true;
}

int printf(const char * restrict format, ...)
{
	va_list params;
	va_start(params, format);

	int written = 0;

	while(*format != '\0')
	{
		size_t maxrem = INT_MAX - written;
		if (format[0] != '%' || format[1] == '%')
		{
			if(format[0] == '%')
				format++;
			size_t amount = 1;
			while(format[amount] && format[amount] != '%')
				amount++;
				
			if(maxrem < amount) {
				// EOVERFLOW
				return -1;
			}
			if(!print(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}

		const char *format_begun_at = format++;

		if(*format == 'c')
		{
			format++;
			char c = (char) va_arg(params, int/* char promotes to int */);
			if(!maxrem) {
				// EOVERFLOW
				return -1;
			}
			if(!print(&c, sizeof(c)))
				return -1;
			written++;
		} else if(*format == 's') {
			format++;
			const char *str = va_arg(params, const char *);
			size_t len = strlen(str);
			if(maxrem < len) {
				// EOVERFLOW
				return -1;
			}
			if(!print(str, len))
				return -1;
			written += len;
		} else if(*format == 'd') {
			format++;
			int d = va_arg(params, int);
			if(!maxrem) {
				// EOVERFLOW
				return -1;
			}
			char str[100];
			itoa(d, str, 10);
			size_t len = strlen(str);
			if(!print(str, len)) {
				return -1;
			}
			
			written += len;
		} else if(*format == 'x') {
			format++;
			unsigned int d = va_arg(params, unsigned int);
			if(!maxrem) {
				return -1;
			}
			char str[100];
			itoa(d, str, 16);
			size_t len = strlen(str);
			if(!print(str, len)) {
				return -1;
			}
			
			written += len;
		} else {
			format = format_begun_at;
			size_t len = strlen(format);
			if(maxrem < len) {
				// EOVERFLOW
				return -1;
			}
			if(!print(format, len))
				return -1;
			written += len;
			format += len;
		}

	}

	va_end(params);
	return written;
}
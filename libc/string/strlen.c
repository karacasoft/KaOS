#include <stddef.h>
#include <string.h>

size_t strlen(const char *str)
{
	size_t i = 0;
	while(str[i++] != '\0');
	return i - 1;
}
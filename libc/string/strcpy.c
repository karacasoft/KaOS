#include <stddef.h>
#include <string.h>

void strcpy(const char *src, char *dst)
{
	size_t i = 0;
	while(src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
}
#include <stdlib.h>

int atoi(const char *str)
{
	int ret = 0;
	while (str != '\0')
	{
		ret = ret * 10 + (*str - '0');
		str++;
	}
	return ret;
}
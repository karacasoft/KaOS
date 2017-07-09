#include <stdbool.h>
#include <stdlib.h>

char *itoa(int num, char *str, int base)
{
	bool isNegative = false;
	int i = 0;

	if(num == 0) 
	{
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	if(num < 0 && base == 10)
	{
		isNegative = true;
		num = -num;
	}

	while(num != 0) 
	{
		int rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}

	if(isNegative)
	{
		str[i++] = '-';
	}

	str[i] = '\0';

	for (int j = 0; j < i / 2; ++j)
	{
		char tmp = str[j];
		str[j] = str[i - j - 1];
		str[i - j - 1] = tmp;
	}

	return str;
}
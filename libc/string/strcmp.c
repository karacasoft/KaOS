#include <string.h>

int strcmp(const char *str1, const char *str2)
{
  char *str1ptr = str1;
  char *str2ptr = str2;
  if(*str1ptr == 0 || *str2ptr == 0) {
    return (*str1ptr - *str2ptr);
  }
  while(*(str1ptr++) == *(str2ptr++) && (*str1ptr != 0 && *str2ptr != 0));
  return (*(str1ptr - 1)) - (*(str2ptr - 1));
}
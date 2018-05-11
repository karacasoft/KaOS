#ifndef __KAOS_VENG_STRING_H__
#define __KAOS_VENG_STRING_H__ 1

#include <stddef.h>

size_t strlen(const char *str);
void strcpy(const char *src, char *dst);
int strcmp(const char *str1, const char *str2);
void *memset(void *s, int c, size_t n);
void *memcpy(void *d, void *s, size_t n);

#endif
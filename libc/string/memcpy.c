#include <string.h>

#include <stddef.h>

void *memcpy(void *d, void *s, size_t n) {
  char *source = (char *)s;
  char *dest = (char *)d;
  
  for (size_t i = 0; i < n; i++) {
    dest[i] = source[i];
  }
  return d;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>

#ifndef WIN32
#endif

char *copy_name (char *name)
{
  size_t len = strlen(name) + 1;
  char *out = malloc(sizeof(char) * len);
  strncpy(out, name, len);
  return out;
}
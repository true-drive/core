#include <stdio.h>
#include <stdarg.h>
#include "debug.h"

void debug(const char *format, ...)
{
#if DEBUG

  va_list args;
  va_start(args, format);

  printf("[True Drive] ");
  vprintf(format, args);
  printf("\n");

  va_end(args);
#else
  (void)format;
#endif
}
#include "internal/bimalloc_message.h"

#include <stdarg.h>
#include <stdio.h>

static void bi_vfprintf(const char* fmt, va_list args) {
  char buffer[512];
  if (!fmt) {
    return;
  }
  vsnprintf(buffer, sizeof(buffer) - 1, fmt, args);
  printf("%s", buffer);
}

void bi_show_message_log(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  bi_vfprintf(fmt, args);
  va_end(args);
}

#ifndef BIMALLOC_BIMALLOC_ASSERT_H
#define BIMALLOC_BIMALLOC_ASSERT_H

#include <stdbool.h>
#include <stdlib.h>

#include "internal/bimalloc_message.h"

#define BIMALLOC_DEBUG 1

static void bi_assert_raise(const char* assert, const char* file_name, int line,
                            const char* func_name) {
  bi_show_message_log(
      "[BIMALLOC MSG]: assertion failed at %s, %s, line %d. Assert: %s\n",
      file_name, func_name, line, assert);
  abort();
}

#if BIMALLOC_DEBUG
#define bi_assert(assert) \
  ((assert) ? (void)0 : bi_assert_raise(#assert, __FILE__, __LINE__, __func__))
#else
#define bi_assert(assert)
#endif

#endif  // BIMALLOC_BIMALLOC_ASSERT_H

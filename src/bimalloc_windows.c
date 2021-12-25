#include "bimalloc_macros.h"

#ifdef BIMALLOC_OS_WINDOWS

#include <stdbool.h>
#include <windows.h>

#include "bimalloc_base.inl"
#include "bimalloc_message.h"

static PVOID bi_core_alloc(size_t size) {
  bi_show_message_log("free error %d", 1);
  PVOID ptr = VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
  if (ptr) {
    return ptr;
  }
  abort();
}

static void bi_core_free(void* ptr) {
  bool is_free = VirtualFree(ptr, 0, MEM_RELEASE);
  if (is_free) {
    return;
  }
  bi_show_message_log("free error %d", 1);
}

#endif

#include "alignment.h"
#include "bimalloc.h"
#include "bimalloc_bitmap.h"

static void* bi_core_alloc(size_t size);

static void bi_core_free(void* ptr);

void* bi_malloc(size_t size) { return NULL; }

void* bi_realloc(void* ptr, size_t size) { return NULL; }

void* bi_calloc(size_t num, size_t size) { return NULL; }

void bi_free(void* ptr) {}

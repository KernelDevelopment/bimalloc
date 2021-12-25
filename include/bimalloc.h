#ifndef BIMALLOC_BIMALLOC_H
#define BIMALLOC_BIMALLOC_H

#include <stddef.h>
#include <stdint.h>

void* bi_malloc(size_t size);
void* bi_realloc(void* ptr, size_t size);
void* bi_calloc(size_t num, size_t size);
void bi_free(void* ptr);

#endif  // BIMALLOC_BIMALLOC_H

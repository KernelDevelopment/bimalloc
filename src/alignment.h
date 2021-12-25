#ifndef BIMALLOC_ALIGNMENT_H
#define BIMALLOC_ALIGNMENT_H

#include "stdalign.h"

#define ALIGN (alignof(max_align_t))
#define ALIGN_UP(s) (((s) + (ALIGN - 1)) & ~(ALIGN - 1))

#endif  // BIMALLOC_ALIGNMENT_H

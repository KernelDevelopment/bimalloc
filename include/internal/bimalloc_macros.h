#ifndef BIMALLOC_BIMALLOC_MACROS_H
#define BIMALLOC_BIMALLOC_MACROS_H

#if (defined(_WIN64) || defined(_WIN32))
#define BIMALLOC_OS_WINDOWS
#endif

#if defined(__cplusplus)
#define BIMALLOC_START_CPP_NAMESPACE \
  namespace bimalloc {               \
  extern "C" {
#define BIMALLOC_END_CPP_NAMESPACE   \
  }                                  \
  }
#else
#define BIMALLOC_START_CPP_NAMESPACE
#define BIMALLOC_END_CPP_NAMESPACE
#endif

#endif  // BIMALLOC_BIMALLOC_MACROS_H

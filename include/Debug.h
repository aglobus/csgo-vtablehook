#ifndef __debug_h__
#define __debug_h__

#include <stdio.h>
#include <errno.h>
/* #include <string.> */

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#endif

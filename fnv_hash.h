#ifndef _FNV_HASH
#define _FNV_HASH

#include <stddef.h>
#include <stdint.h>

uint64_t fnv1a64(void *buf, size_t len);

#endif
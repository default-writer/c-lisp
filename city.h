#ifndef _CITY_H_
#define _CITY_H_

#include <stdlib.h>  // for size_t.
#include <stdint.h>

typedef uint32_t uint32;

// Hash function for a byte array.  Most useful in 32-bit binaries.
uint32 CityHash32(const char *buf, size_t len);

#endif  // _CITY_H_
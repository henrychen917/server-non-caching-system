#ifndef hash_h
#define hash_h


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>




uint32_t murmurhash (const char *, uint32_t, uint32_t);
int str_length(char str[]);

#endif
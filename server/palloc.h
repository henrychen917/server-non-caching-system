#ifndef palloc_h
#define palloc_h

#include <stdio.h>
#include <stdlib.h>

#define default_size 4000

typedef struct pool_s pool_t;
typedef struct data_s data_t;


struct data_s {
    size_t size;
    data_t *next;
};




struct pool_s {
    size_t size;
    pool_t *current;
    pool_t *next;
    data_t d;
    u_char *last;
    u_char *end;
};


pool_t* pool_init(size_t size);
void* pool_alloc(size_t size, pool_t *pool);
void* pool_free();
pool_t* pool_destroy(pool_t *pool, pool_t *target);

#endif
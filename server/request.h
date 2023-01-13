#ifndef request_h
#define request_h

#include <bst.h>
#include <palloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>
#include <unistd.h>

char *processRequest(char *request, node_t *root, pool_t *pool);



#endif
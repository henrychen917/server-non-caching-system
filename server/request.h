#ifndef request_h
#define request_h

#include <cJSON.h>
#include <palloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>
#include <unistd.h>
#include <disk.h>

char *processRequest(char *request, pool_t *pool);



#endif
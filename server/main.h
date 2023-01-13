#ifndef main_h
#define main_h

#include <bst.h>
#include <hash.h>
#include <palloc.h>
#include <cJSON.h>
#include <request.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

typedef struct threadArgs_s threadArgs_t;

#define DEFAULT_PORT "88888"
#define DEFAULT_ADDR "192.168.50.80"

struct threadArgs_s {
	int new_sockfd;
	node_t *root;
	pool_t *pool;
	struct sockaddr_in clnt;
};




#endif
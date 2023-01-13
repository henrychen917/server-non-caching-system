#ifndef disk_h
#define disk_h
#include <bst.h>
#include <cJSON.h>
#include <palloc.h>
#include <hash.h>

void diskSaveAll(node_t *root);

node_t* diskInit(pool_t *pool);

cJSON* diskPreorder(cJSON *json_root, node_t *root);




#endif

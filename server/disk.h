#ifndef disk_h
#define disk_h

#include <cJSON.h>
#include <palloc.h>


void diskSaveAll(cJSON *json_root);

cJSON* diskInit();

//cJSON* diskPreorder(cJSON *json_root, node_t *root);




#endif

#include <request.h>

char *processRequest(char *request, pool_t *pool){
	//printf("%s", request);

    cJSON *json_root = diskInit();
    cJSON *json_item = cJSON_GetObjectItemCaseSensitive(json_root, "aaa");
    printf("%s %s\n", json_item->string, json_item->valuestring);



    //cJSON *json_root = diskInit();
    //cJSON *json_item;
    // printf("1");
    // char *requestType = strtok(request, " ");
    // char key[32], val[64];
    //char *response = pool_alloc(sizeof(char)*200, pool);
    // char *tempkey = strtok(NULL, " ");
    // if (tempkey == NULL){
    //     sprintf(response, "ERROR: No key specified");
    //     goto end;
    // }
    // strcpy(key, tempkey);
    //printf("%s", key);
    //json_item = cJSON_GetObjectItemCaseSensitive(json_root, "aaa");
    // if (strcmp(requestType, "GET") == 0) {
    //     if (json_item != NULL) {
    //         sprintf(response, "Node found with key: %s val: %s\n", json_item->string, json_item->valuestring);
    //         goto end;
    //     } else {
    //     	sprintf(response, "Node not found with key: %s\n", key);
    //         goto end;
    //     }
    // } else if (strcmp(requestType, "SET") == 0) {

    //     char *tempval = strtok(NULL, " ");
    //     if (tempval == NULL){
    //         sprintf(response, "ERROR: No value specified");
    //         goto end;
    //     }

    //     strcpy(val, tempval);
    //     if (json_item != NULL){
    //                 cJSON_DeleteItemFromObject(json_root, key);
    //     }

    //     cJSON_AddItemToObject(json_root, key, cJSON_CreateString(val));
    // 	sprintf(response, "Error adding node with key: %s and value: %s\n", key, val);
    //     goto end;

    // } else if (strcmp(requestType, "DEL") == 0) {
    //     cJSON_DeleteItemFromObject(json_root, key);
    // 	sprintf(response, "Node deleted with key: %s\n", key);
    //     goto end;

    // } else {
    // 	sprintf(response, "Invalid request type: %s\n", requestType);
	// 	goto end;
    // }
    //end:
    //diskSaveAll(json_root);
    //sprintf(response, "%s %s\n", json_item->string, json_item->valuestring);
    //return response;
    return NULL;
}
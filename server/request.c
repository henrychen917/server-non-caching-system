#include <request.h>

char *processRequest(char *request, pool_t *pool){
	//printf("%s", request);


    cJSON *json_root = diskInit();
    cJSON *json_item;
    char *requestType = strtok(request, " ");
    char key[32], val[64];
    char *response = pool_alloc(sizeof(char)*200, pool);
    char *tempkey = strtok(NULL, " ");

    do {

        if (tempkey == NULL){
            sprintf(response, "ERROR: No key specified");
            break;
        }
        strcpy(key, tempkey);
        //printf("%s", key);
        json_item = cJSON_GetObjectItemCaseSensitive(json_root, key);
        if (strcmp(requestType, "GET") == 0) {
            if (json_item != NULL) {
                sprintf(response, "Node found with key: %s val: %s\n", json_item->string, json_item->valuestring);
                break;
            } else {
            	sprintf(response, "Node not found with key: %s\n", key);
                break;
            }
        } else if (strcmp(requestType, "SET") == 0) {

            char *tempval = strtok(NULL, " ");
            if (tempval == NULL){
                sprintf(response, "ERROR: No value specified");
                break;
            }

            strcpy(val, tempval);
            if (json_item != NULL){
                cJSON_DeleteItemFromObject(json_root, key);
            }

            cJSON_AddItemToObject(json_root, key, cJSON_CreateString(val));
            sprintf(response, "Node added with key: %s and value: %s\n", key, val);
            break;

        } else if (strcmp(requestType, "DEL") == 0) {
            cJSON_DeleteItemFromObject(json_root, key);
        	sprintf(response, "Node deleted with key: %s\n", key);
            break;

        } else {
        	sprintf(response, "Invalid request type: %s\n", requestType);
    		break;
        }

    } while (0);


    diskSaveAll(json_root);

    fprintf(stderr, "%p\n", response);

    return response;

}
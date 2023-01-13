#include <request.h>

char *processRequest(char *request, node_t *root, pool_t *pool){
	//printf("%s", request);
    char *requestType = strtok(request, " ");
    char key[32], val[64];
    char *response = pool_alloc(sizeof(char)*200, pool);
    char *tempkey = strtok(NULL, " ");
    if (tempkey == NULL){
        sprintf(response, "ERROR: No key specified");
        return response;
    }
    strcpy(key, tempkey);

    if (strcmp(requestType, "GET") == 0) {
        node_t* result = searchNode(root, key);
        if (result != NULL) {
        	sprintf(response, "Node found with key: %s val: %s\n", result->key, result->val);
            return response;
        } else {
        	sprintf(response, "Node not found with key: %s\n", key);
            return response;
        }
    } else if (strcmp(requestType, "SET") == 0) {
        char *tempval = strtok(NULL, " ");
        if (tempval == NULL){
            sprintf(response, "ERROR: No value specified");
            return response;
        }
        strcpy(val, tempval);
        node_t* result = insertNode(root, key, val, pool);
        if (result != NULL) {
        	sprintf(response, "Node added with key: %s and value: %s\n", key, val);
            return response;
        } else {
        	sprintf(response, "Error adding node with key: %s and value: %s\n", key, val);
            return response;
        }
    } else if (strcmp(requestType, "DEL") == 0) {
       	node_t *result = deleteNode(root, key);
        if (result != NULL) {
        	sprintf(response, "Node deleted with key: %s\n", key);
            return response;
        } else {
        	sprintf(response, "Error deleting node with key: %s\n", key);
            return response;
        }
    } else {
    	sprintf(response, "Invalid request type: %s\n", requestType);
		return response;
    }
}
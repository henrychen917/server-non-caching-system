#include <disk.h>



void diskSaveAll(node_t *root){
    FILE *fptr;
    fptr = fopen("data.json","w");
    char *temp ="{\n}";
    char *out = NULL;
    cJSON *json_root = cJSON_Parse(temp);
    if (root!=NULL){
        json_root = diskPreorder(json_root, root);
        out = cJSON_Print(json_root);
        fprintf(fptr,"%s",out);
        printf("%s\n",out);
    }
    cJSON_Delete(json_root);
    free(out);
    fclose(fptr);
}

cJSON* diskPreorder(cJSON *json_root, node_t *root){
    if(root!= NULL){
        cJSON_AddItemToObject(json_root, root->key, cJSON_CreateString(root->val));
        diskPreorder(json_root, root->left);
        diskPreorder(json_root, root->right);
    }
    return json_root;
}

node_t* diskInit(pool_t *pool){


    //JSON file to char text data
    FILE *f = NULL;
    long len = 0;
    char *data = NULL;
    f = fopen("data.json","rb");
    fseek(f, 0, SEEK_END);
    len = ftell(f);
    fseek(f, 0, SEEK_SET);
    data = (char*)malloc(len + 1);
    fread(data, 1, len, f);
    data[len] = '\0';
    fclose(f);


    //parse text to cJSON data structure
    node_t *root = NULL;
    cJSON *json_root = NULL;
    json_root = cJSON_Parse(data);
    cJSON * json_ptr = NULL;
    //root = insert(root,json_root->child->string, json_root->child->valuestring, pool);
    cJSON_ArrayForEach(json_ptr, json_root) {
        printf("%s: %s\n", json_ptr->string, json_ptr->valuestring);
        root = insertNode(root, json_ptr->string, json_ptr->valuestring, pool);
    }
    cJSON_Delete(json_root);
    cJSON_Delete(json_ptr);
    //inorder(root);
    return root;

    


}



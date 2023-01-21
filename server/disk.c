#include <disk.h>



void diskSaveAll(cJSON *json_root){
    FILE *fptr;
    fptr = fopen("data.json","w");
    //char *temp ="{\n}";
    char *out = NULL;
    //cJSON *json_root = cJSON_Parse(temp);
    if (json_root!=NULL){
        out = cJSON_Print(json_root);
        fprintf(fptr,"%s",out);
        //printf("%s\n",out);
    }
    cJSON_Delete(json_root);
    free(out);
    fclose(fptr);
}

// cJSON* diskPreorder(cJSON *json_root, node_t *root){
//     if(root!= NULL){
//         cJSON_AddItemToObject(json_root, root->key, cJSON_CreateString(root->val));
//         diskPreorder(json_root, root->left);
//         diskPreorder(json_root, root->right);
//     }
//     return json_root;
// }

cJSON* diskInit(){


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

    cJSON *json_root = NULL;

    json_root = cJSON_Parse(data);

    //inorder(root);
    return json_root;

    


}



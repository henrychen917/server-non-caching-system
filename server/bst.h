#ifndef bst_h
#define bst_h



#include <palloc.h>
#include <hash.h>




typedef struct node_s node_t;

struct node_s {
	uint32_t keyid;
    char key[32];
    char val[64];

	node_t *left;
    node_t *right;
};


node_t* newNode(uint32_t keyid, char key[32], char value[64], pool_t *pool);
void inorder(node_t* root);
node_t* insertNode_s(node_t* root, uint32_t keyid, char key[32], char value[64], pool_t *pool);
node_t* insertNode(node_t* root, char key[32], char value[64], pool_t *pool);
node_t* minValueNode(node_t* node);
node_t* deleteNode_s(node_t* root, uint32_t keyid);
node_t* deleteNode(node_t* root, char key[32]);
node_t* searchNode_s(node_t* root, uint32_t keyid);
node_t* searchNode(node_t* root, char key[32]);

#endif
#include<stdio.h>
#include<stdint.h>
#include<assert.h>
#include "include/fruits.h"

#define ARRAY_LEN(xs) (sizeof(xs)/sizeof((xs)[0]))

typedef struct Node Node;
struct Node {
    Node* children[256];    
};


#define NODE_POOL_SIZE 1024
Node node_pool[NODE_POOL_SIZE] = {0};
int node_pool_size = 0;

Node* allocate_node(void) {
    assert(node_pool_size < NODE_POOL_SIZE);
    return &node_pool[node_pool_size++]; 
}

void insert_node(const char *text, Node* root) {
   if (text == NULL || *text == '\0') {
	   return;
   }
   if (root == NULL) 
	   return;

   int16_t index = *text;
   if (root->children[index] == NULL) {
   	root->children[index] = allocate_node();
   }
   insert_node(text+1,root->children[index]);
}

void init_tree(Node* root) {
    for(int i=0;i< sizeof(fruits)/sizeof(fruits[0]);i++){
	    insert_node(fruits[i],root);
    }
}

void insert_dots(Node* root) {
    if(root == NULL) return;
    size_t index= root - node_pool;
    for (size_t i=0;i< ARRAY_LEN(root->children); ++i) {
	    if(root->children[i] != NULL) {
		    size_t child_idx = root->children[i] - node_pool; 
		    printf("    \"%zu\" -> \"%zu\"\n [label=\"%c\"]", index, child_idx,(char)i);
		    insert_dots(root->children[i]);
	     }
    }

}

int main(void) {
    Node* stuff = allocate_node();
    init_tree(stuff);
    printf("digraph trie {\n");
    insert_dots(stuff);
    printf("}\n");
    return 0;
}

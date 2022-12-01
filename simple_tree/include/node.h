#ifndef _NODE_TREE_H_
#define _NODE_TREE_H_

typedef struct tree_node node_tr;

struct tree_node
{
    void *data; //void pointer to any data
    node_tr *left;
    node_tr *right;
};

#endif
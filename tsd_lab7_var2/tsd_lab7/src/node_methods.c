#include "node_methods.h"

node_tr* create_node_tree()
{
    node_tr *new_node = malloc(sizeof(node_tr));
    if (new_node)
    {
        new_node->data = NULL;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

int init_node_tree_num(node_tr *node, void *data) //check whether i call this function
{
    int rc = OK;
    if (node)
    {
        node->data = data; // pointer to created node
        node->left = NULL;
        node->right = NULL;
    }
    else
    {
        rc = ALLOC_ERROR;
    }
    return rc;
}


void delete_node_tree(node_tr *node)
{
    free(node);
}

/// /// ////
void node_to_dot(node_tr *leaf, void *param)
{
    FILE *f = param;

    if (leaf->left)
        fprintf(f, "%s -> %s;\n", (char *)(leaf->data), (char *)(leaf->left->data));

    if (leaf->right)
        fprintf(f, "%s -> %s;\n", (char *)(leaf->data), (char *)(leaf->right->data));
}

void output_node(node_tr *leaf, void *param)
{
    printf("%s\n", (char *)leaf->data);
}
#ifndef _TREE_METHODS_H_
#define _TREE_METHODS_H_

#include "return_codes.h"
#include "tree.h"
#include "node_methods.h"
#include <string.h>
#include "stddef.h"
#include <stdio.h>

#include "string_t.h"

typedef void (*ptr_action_t)(node_tr*, void*);

int create_tree(tree_t **tree);

int init_add_strings(string_t *arr, size_t size, node_tr **root);


node_tr* btree_insert(node_tr *root, node_tr *node);

node_tr *find(node_tr *root, const char *string, int *compar);

//void delete_nodes_in_tree(node_tr *root);
void delete_tree(tree_t **tree);

node_tr* btree_delete(node_tr *tree, const char *string);
node_tr* find_max_left(node_tr *root);

node_tr* free_nodes(node_tr *root);

void btree_export_to_dot_only_vertex(FILE *f, node_tr *tree);


void btree_apply_pre(node_tr *tree, ptr_action_t f, void *arg);
void btree_apply_post(node_tr *tree, ptr_action_t f, void *arg);


// //

void btree_export_to_dot(FILE *f, const char *tree_name, node_tr *tree);

#endif
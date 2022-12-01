#ifndef _NODE_METHODS_H_
#define _NODE_METHODS_H_

#include <stdlib.h>
#include "node.h"
#include "return_codes.h"

#include <stdio.h>

node_tr* create_node_tree();

int init_node_tree_num(node_tr *node, void *data);

void delete_node(node_tr *node);


void node_to_dot(node_tr *leaf, void *param);

#endif
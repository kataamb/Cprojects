#ifndef _BALANCE_TREE_H_
#define _BALANCE_TREE_H_

#include "node.h"
#include "tree.h"
#include "node_methods.h"
#include "tree_methods.h"

#include "return_codes.h"


//-----------
#include <stdio.h>

#include "string_t.h"

node_tr *balance(node_tr *root);

node_tr* ll_rotation(node_tr *root);
node_tr* rr_rotation(node_tr *root);
node_tr* lr_rotation(node_tr *root);
node_tr* rl_rotation(node_tr* apNode);

int diff(node_tr* apNode);
int height(node_tr *apNode);

node_tr *insert_balance(node_tr *root, node_tr *node);

node_tr* delete_balance(node_tr *root, const char *string);
#endif
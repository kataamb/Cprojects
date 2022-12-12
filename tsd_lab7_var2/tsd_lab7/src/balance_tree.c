#include "balance_tree.h"

node_tr *insert_balance(node_tr *root, node_tr *node)
{
    if (root == NULL)
        return node;
    
    int cmp = strcmp((char*)node->data, (char*)root->data);
    if (cmp <= 0)
    {
        root->left = insert_balance(root->left, node);
        root = balance(root);
    }
    else
    {
        root->right = insert_balance(root->right, node);
        root = balance(root);
    }

    return root;

}

node_tr *balance(node_tr *root)
{
    if (diff(root) > 1)
    {
        if (diff(root->left) > 0)
        {
            root = ll_rotation(root);
        }
        else
        {
            root = lr_rotation(root);
        }
    }
    else if (diff(root) < -1)
    {
        if (diff(root->right) > 0)
        {
            root = rl_rotation(root);
        }
        else
        {
            root = rr_rotation(root);
        }
    }
    return root;
}

node_tr* ll_rotation(node_tr *root)
{
  node_tr *temp;
  temp = root->left;
  root->left = temp->right;
  temp->right = root;
  return temp;
}
//------------------------------------------------------------------------------
node_tr* rr_rotation(node_tr *root)
{
  node_tr *temp;
  temp = root->right;
  root->right = temp->left;
  temp->left = root;
  return temp;
}
//------------------------------------------------------------------------------
node_tr* lr_rotation(node_tr *root)
{
  node_tr *temp;
  temp = root->left;
  root->left = rr_rotation(temp);
  return ll_rotation(root);
}
//------------------------------------------------------------------------------
node_tr* rl_rotation(node_tr* apNode)
{
  node_tr* temp;
  temp = apNode->right;
  apNode->right = ll_rotation(temp);
  return rr_rotation(apNode);
}

//------------------------
int diff(node_tr* apNode)
{
  int l_height = height(apNode->left);
  int r_height = height(apNode->right);
  //printf("NODE: %s,  left: %d, right: %d\n", (char*)apNode->data, l_height, r_height);
  int b_factor = l_height - r_height;
  return b_factor;
}

int height(node_tr *node)
{
  int h = 0;

  if (node != NULL)
  {
      int l_height = height(node->left);
      int r_height = height(node->right);
      int max_height = l_height > r_height ? l_height : r_height;
      h = max_height + 1;
  }
  return h;
}
//----------------------------


node_tr* delete_balance(node_tr *root, const char *string)
{
    if (root == NULL)
    {
        printf("No such data\n");
        return root;
    }

    //if values are not equal
    if (strcmp((char *)root->data, string) > 0)
    {
        root->left = delete_balance(root->left, string);
        //root = balance(root);
    }
    else if (strcmp((char *)root->data, string) < 0)
    {
        root->right = delete_balance(root->right, string);
        //root = balance(root);
    }
    //if values are equal - we found this element and have to delete it
    else
    {
        //debug
        //printf("Yes, here\n");

        //if left child is null- save right child and delete current element (left is null anyway)
        if(root->left == NULL)
        {
            node_tr *temp = root->right;
            free(root);
            //new root value
            return temp; 
        }
        //pretty same if right child is null- save left child and delete current element (right is null anyway)
        else if(root->right == NULL)
        {   
            node_tr *temp = root->left;
            free(root);
            return temp;
        }
        //if both childs are not null: find min element in right and make it (??/ what???)
        else
        {
            node_tr *temp = find_max_left(root->left); //watch videos about deleting,
            //what element we are about to find

            //free root->data before initializing if it's allocated dynamically

            //
            root->data = temp->data;
            root->left = delete_balance(root->left, (char *)temp->data);
            //root = balance(root);
        }
    }

  return balance(root);
}

/*
node_tr* btree_insert(node_tr *tree, node_tr *node)
{
    int cmp;

    if (tree == NULL)
        return node;

    cmp = strcmp((char*)node->data, (char*)tree->data);
    
    if (cmp <= 0)
    {
        tree->left = btree_insert(tree->left, node);
    }
    else
    {
        tree->right = btree_insert(tree->right, node);
    }

    return tree;
}
*/

/*
int main()
{
    int rc = 0;


    tree_t *tree;
    string_t array[100];
    FILE *src = fopen("data3.txt", "r");
    size_t size = 0;
    rc = read_string_array(array, &size, src);
    fclose(src);

    rc = create_tree(&tree);

    for (int i = 0; i < size; i++)
    {
        node_tr *curr_node = create_node_tree();
        init_node_tree_num(curr_node, (void*)(array[i].word));
        tree->root = insert_balance(tree->root, curr_node);
    }
    node_tr *node = find(tree->root, "Mary");

    if (node)
    {
        printf("Curr str is: %s\n", (char*)node->data);
    }
    else
    {
        printf("it's null\n");
    }

    //tree->root = delete_balance(tree->root, "ago");
    //tree->root = delete_balance(tree->root, "Mary");
    //tree->root = delete_balance(tree->root, "loved");

    //tree->root = btree_delete(tree->root, "Mary");

    FILE *file = fopen("tree1.gv", "w");
    if (file){
        btree_export_to_dot(file, "bin_tree", tree->root);
        fclose(file);
    }

    tree->root = free_nodes(tree->root);
    delete_tree(&tree);

    return rc;
}
*/

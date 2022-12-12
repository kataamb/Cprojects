#include "tree_methods.h"

int create_tree(tree_t **tree)
{
    int rc = OK;
    tree_t *new_tree = malloc(sizeof(tree_t));

    if (new_tree)
    {
        *tree = new_tree;
        (*tree)->root = NULL;
    }
    else
    {
        rc = ALLOC_ERROR;
    }
    return rc;
    
}

/*
    we can free all tree as well as subtree
*/
node_tr* free_nodes(node_tr *root)
{
    //if (root == NULL)
        //return root;
    //else
    if (root)
    {
        //if (root->left)
    
        free_nodes(root->left);
    
    //if (root->right)
    
        free_nodes(root->right);
    
    }
    

    free(root);
    
    
    
    root = NULL;

    return root;  

}

void delete_tree(tree_t **tree)
{
    //
    free(*tree);
}

/*
node_tr* btree_insert(node_tr *root, node_tr *node)
{
    int cmp;

    if (root == NULL)
        return node;

    cmp = strcmp((char*)(node->data), (char*)(root->data));
    //printf("Lwft: %p, right: %p\n", (void*)root->left, (void*)root->right);
    
    if (cmp < 0)
    {
        root->left = btree_insert(root->left, node);
    }
    else
    {
        root->right = btree_insert(root->right, node);
    }

    return root;
}
*/

int init_add_strings(string_t *arr, size_t size, node_tr **root)
{
    int rc = OK;
    for (size_t i = 0; i < size && rc == OK; i++)
    {
        node_tr *cur_node = create_node_tree();
        //!!!!!!NOT INITING!!!!!!!!!!!!!!!!
        if (cur_node)
        {
            //printf("Iter: %zu\n", i);
            cur_node->data = (arr + i)->word;
            //printf("Val inserting: %s\n", (char*)(arr + i)->word);
            *root = btree_insert(*root, cur_node);
            //printf("Val current root: %s\n", (char*)((*root)->data));
        }
        else
        {
            rc = ALLOC_ERROR;
        }
    }
    return rc;
}


/// ///// ////
void btree_apply_pre(node_tr *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    btree_apply_pre(tree->left, f, arg);
    btree_apply_pre(tree->right, f, arg);
}

void btree_apply_post(node_tr *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    btree_apply_post(tree->left, f, arg);
    btree_apply_post(tree->right, f, arg);
    f(tree, arg);
}


void btree_export_to_dot(FILE *f, const char *tree_name, node_tr *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);

    btree_apply_pre(tree, node_to_dot, f);

    fprintf(f, "}\n");
}

void btree_export_to_dot_only_vertex(FILE *f, node_tr *tree)
{
    btree_apply_pre(tree, node_to_dot, f);
}

/*
    find element
*/
node_tr *find(node_tr *root, const char *string, int *compar)
{
    //if null or data is that we need (current_value)
    (*compar)++;
    if (!root || strcmp((char *)root->data, string) == 0)
    {
        return root;
    }

    else if (strcmp((char *)root->data, string) > 0)
    {
        return find(root->left, string, compar);
    }
    else
    {
        return find(root->right, string, compar);
    }
}


//
// realize min_value_right_tree
//
node_tr* btree_delete(node_tr *root, const char *string)
{
    if (root == NULL)
    {
        printf("No such data\n");
        return root;
    }

    //debug
    //printf("root->data: %s, string: %s\n", (char *)root->data, string);
    //if values are not equal
    if (strcmp((char *)root->data, string) > 0)
    {
        root->left = btree_delete(root->left, string);
    }
    else if (strcmp((char *)root->data, string) < 0)
    {
        root->right = btree_delete(root->right, string);
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
            node_tr *temp = find_max_left(root); //watch videos about deleting,
            printf("Temp %p\n", (void*)temp);
            printf("Temp data %s\n", (char*)temp->data);
            //what element we are about to find

            //printf("Temp %p\n", (void*)temp->left);
            //printf("Temp %p\n", (void*)temp);
            //free root->data before initializing if it's allocated dynamically

            //
            root->data = temp->data;
            root->left = btree_delete(root->left, (char *)temp->data);
        }
    }

  return root;
}

node_tr* find_max_left(node_tr *root)
{
    node_tr *curr = root->left;
    node_tr *prev = root->left;

    while (curr)
    {
        prev = curr;
        curr = curr->right;
    }

    return prev;
}


/*
    (recursive) insert in tree
*/
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

/*
void delete_element(tree_t *tree, node_tr *node)
{
    tree->root = free_nodes(tree->root);
}*/

/*
move 
int find_and_delete(const char *string, node_tr *root)
{
    // 1 find this element
    node_tr *del_node = find(root, string);
    //2 move back
    //if 
    //else if right == NULL -> swap values with Null, so we have now pointer to that element, free it
    //else

}*/


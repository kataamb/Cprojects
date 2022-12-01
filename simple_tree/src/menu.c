#include "menu.h"

void act_output_tree(tree_t *tree)
{
    FILE *file = fopen("tree_out.gv", "w");
    if (file){
        btree_export_to_dot(file, "bin_tree", tree->root);
        fclose(file);
    }

    system ("/home/katamba/'Рабочий стол'/github_c_try/Cprojects/tsd_lab_61/transform_to_image.sh");
    system ("xdg-open tree_out.png &");
}

void act_find_and_output_tree(tree_t *tree, char letter)
{
    FILE *file = fopen("tree_with_letters_out.gv", "w");
    if (file){
        string_t res[100];
        int res_size = 0;
        act_find_letter_tree(tree, letter, res, &res_size);
        fprintf(file, "digraph %s {\n", "bin_tree");

        for (int i = 0; i < res_size; i++)
        {
            fprintf(file, "%s [color=\"red\"];\n", res[i].word);
        }
        btree_export_to_dot_only_vertex(file, tree->root);
        //btree_apply_pre(tree->root, node_to_dot, file);
        fprintf(file, "}\n");

        //btree_export_to_dot(file, "bin_tree", tree->root);
        fclose(file);
    }

    system ("/home/katamba/'Рабочий стол'/github_c_try/Cprojects/tsd_lab_61/draw_found.sh");
    system ("xdg-open tree_with_letters_out.png &");
}

void act_insert_node(tree_t *tree, const char *string)
{
    node_tr *node_insert = create_node_tree();
    init_node_tree_num(node_insert, (void*)string);
    tree->root = btree_insert(tree->root, node_insert);
}

void act_delete_node(tree_t *tree, const char *string)
{
    tree->root = btree_delete(tree->root, string);
}


//////
void btree_apply_post(node_tr *root, char letter, string_t *res, int *size)
{
    if (root == NULL)
        return;

    btree_apply_post(root->left, letter, res, size);
    btree_apply_post(root->right, letter, res, size);
    
    char *data = (char*)root->data;
    if (data[0] == letter)
    {
        res[*size].word = data;
        (*size)++;
    }
}

void act_find_letter_tree(tree_t *tree, char letter, string_t *res, int *size)
{
    btree_apply_post(tree->root, letter, res, size);
}

/*
void act_compare_words(tree_t *tree, string_t *array, int size, char letter)
{

}
*/

void act_find_letter_array(string_t *arr, int arsize, char letter, string_t *res, int *size)
{
    for (int i = 0; i < arsize; i++)
    {
        if (arr[i].word[0] == letter)
        {
            res[*size].word = arr[i].word; // just a pointer to that 
            (*size)++;
        }
    }
}

int act_open_file(FILE **src)//, const char *filename)
{
    int rc = OK;
    char *filename = NULL;
    size_t buf = 0;
    int len = 0;

    printf("FILE:\n");
    int read = getline(&filename, &buf, stdin);
    if (read != -1)
    {
        len = strlen(filename);
        filename[len - 1] = '\0';
        *src = fopen(filename, "r");
        if (!(*src))
        {
            printf("Cannot open file\n");
            rc = READ_ERROR;
        }

        free(filename);
    }
    else
    {
        printf("READ ERROR\n");
        rc = READ_ERROR;
    }

    return rc;
    
}

int act_input_string(char **string)
{
    int rc = OK;
    size_t buf = 0;
    int len = 0;

    printf("Input string:\n");
    int read = getline(string, &buf, stdin);
    if (read != -1)
    {
        len = strlen(*string);
        (*string)[len - 1] = '\0';
    }
    else
    {
        printf("READ ERROR\n");
        rc = READ_ERROR;
    }

    return rc;
} 

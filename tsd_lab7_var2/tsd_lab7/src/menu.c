#include "menu.h"

#define REPEAT 1000


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


void act_pre_tree(tree_t *tree, void *param)
{
    btree_apply_pre(tree->root, output_node, param);
}

void act_post_tree(tree_t *tree, void *param)
{
    btree_apply_post(tree->root, output_node, param);
}

node_tr *act_find_word(node_tr *root, char *word, int *comparsions)
{
    //printf("Input string:\n");
    //char *word = read_command();

    int compar = 0;
    
    node_tr * found = find(root, word, &compar);
    *comparsions = compar;
    return found;
}


// /// ////
node_str *act_find_word_hash(hash_t *hash_table, int *comparsions)
{
    printf("Input string:\n");
    char *string = read_command();

    //printf("String read :%s\n", string);
    
    return find_hash(hash_table, string, comparsions);
}


/*
    flush input

void flush_input(void)
{
    char c;
    while((scanf("%c", &c) == 1) && (c != '\n'))
        ;
}
*/

/*
void act_rehash(hash_t *hash_table)
{
    int num = 0;
    printf("Input size of hash or nothing to find optimal:\n");
    if (scanf("%d", &num) == 1)
    {
        if (num > 0)
        {

        }
        else
        {
            printf("Incorrect size of hash table\n");
        }
    }
    else
    {

    }
    flush_input();
    
}
*/


/// ////////

//////
/*
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
*/

void btree_find_all(node_tr *root, char letter, string_t *res, int *size)
{
    if (root == NULL)
        return;
    char *data = (char*)root->data;
    if (data[0] == letter)
    {
        res[*size].word = data;
        (*size)++;
        btree_find_all(root->left, letter, res, size);
        btree_find_all(root->right, letter, res, size);
    }

    else if (data[0] > letter)
    {
        //printf("CURR L: %s\n", data);
        btree_find_all(root->left, letter, res, size);
        //btree_find_all(root->right, letter, res, size);
    }
    else if (data[0] < letter)
    {
        //printf("CURR R: %s\n", data);
        btree_find_all(root->right, letter, res, size);
        //btree_find_all(root->left, letter, res, size);
    }

}

void act_find_letter_tree(tree_t *tree, char letter, string_t *res, int *size)
{
    //btree_apply_post(tree->root, letter, res, size);
    btree_find_all(tree->root, letter, res, size);

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


void act_compare(char *filename, double *treeT, double *arrT, int *memT, int *memA)
{
    //1. open file
    FILE *src;
    src = fopen(filename, "r");
    int rc = OK;

    tree_t *tree = NULL;

    size_t size = 0;
    string_t array[1000];

    string_t res[1000];
    int res_size = 0;

    string_t resf[1000];
    int resf_size = 0;

    if (src)
    {
        rc = read_string_array(array, &size, src);
        fclose(src);
        src = NULL;
        
        //output_string_array(array, size);
    }
    else
        //rc = -1;
        return ;


    if (rc == OK)
    {
        rc = create_tree(&tree);    

        if (rc == OK)
        {
            rc = init_add_strings(array, size, &(tree->root));
        }
    }

    if (rc == OK)
    {
        double time1 = 0;
        for (size_t i = 0; i < REPEAT; i++)
        {
            int beg = clock();
            act_find_letter_tree(tree, 'a', res, &res_size);
            int end = clock();
            time1 += get_ps(beg, end);
            res_size = 0;
        }
    //
        time1 = time1 / REPEAT;
        delete_tree(&tree);

        ///compare reading from file
        src = fopen(filename, "r");
        double time2 = 0;
        for (size_t i = 0; i < REPEAT; i++)
        {
            int beg = clock();
            //act_find_letter_tree(tree, 'a', res, &res_size);
            //printf("HERE\n");
            //act_find_letter_array(array, size, 'a', res, &res_size);
            //printf("HERE\n");
            find_letter_words_file(resf, &resf_size, 'a', src);
            int end = clock();
            time2 += get_ps(beg, end);
            res_size = 0;
            //resf_size = 0;
        }
        fclose(src);
        time2 = time2 / REPEAT;

        (*treeT) = time1;
        (*arrT) = time2;

        (*memT) = sizeof(tree) + sizeof(node_tr *) * size;
        (*memA) = sizeof(array[0]);
        
    }

}


void btree_apply_mem(node_tr *tree, int *mem)
{
    if (tree == NULL)
        return;

    
    
    (*mem) += sizeof(tree) + sizeof((char *)tree->data) + strlen((char *)tree->data) * sizeof(char);
    btree_apply_mem(tree->left, mem);
    btree_apply_mem(tree->right, mem);
    
}


void efficiency_tree(tree_t *tree, char *word, double *timeT, int *memT, int *comT)
{
    *timeT = 0;
    for (int i = 0; i < REPEAT; i++)
    {
        int beg = clock();
        act_find_word(tree->root, word, comT);
        int end = clock();

        *timeT += get_ps(beg, end);
    }
    
    *timeT = *timeT / REPEAT;
    *memT = sizeof(tree_t);
    btree_apply_mem(tree->root, memT);
}




void efficiency_hash(hash_t *hash_table, char *word, double *timeH, int *memH, int *comH)
{
    *timeH = 0;
    for (int i = 0; i < REPEAT; i++)
    {
        int beg = clock();
        find_hash(hash_table, word, comH);
        int end = clock();

        *timeH += get_ps(beg, end);
    }
    
    *timeH = *timeH / REPEAT;
    //int beg = clock();
    //find_hash(hash_table, word, comH);
    //int end = clock();

    //*timeH = get_ps(beg, end);
    //deb
    printf("Hash table size: %d\n", hash_table->size);
    *memH = sizeof(hash_t) + sizeof(hash_table->array[0]) * hash_table->size;
    
    for (int i  = 0; i < hash_table->size; i++)
    {
        node_str *cur = hash_table->array[i];
        if (cur)
        {
            while (cur)
            {
                if (cur->data)
                {
                    //printf("Str: %s, len: %zu\n", (char *)cur->data, strlen((char *)cur->data));
                    (*memH) += strlen((char *)cur->data) * sizeof(char);
                }
                (*memH) += sizeof(cur);
                cur = cur->next;
                
            }
        }
    }
}

void effic_all_tree(tree_t *tree, string_t *array, int size_arr, double *timeT, int *memT, int *comT)
{
    double cur_time = 0;
    int comp = 0;
    for (int i = 0; i < size_arr; i++)
    {
        char *word = array[i].word;
        *timeT = 0;
        *comT = 0;
        efficiency_tree(tree, word, timeT, memT, comT);
        cur_time += *timeT;
        comp += *comT;
    }
    (*timeT) = cur_time / size_arr;
    (*comT) = comp / size_arr;
}

void effic_all_hash(hash_t *hash_table, string_t *array, int size_arr, double *timeT, int *memT, int *comT)
{
    double cur_time = 0;
    int comp = 0;
    for (int i = 0; i < size_arr; i++)
    {
        char *word = array[i].word;
        *timeT = 0;
        *comT = 0;
        efficiency_hash(hash_table, word, timeT, memT, comT);
        cur_time += *timeT;
        comp += *comT;
    }
    (*timeT) = cur_time / size_arr;
    (*comT) = comp / size_arr;
}
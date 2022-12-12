#include <stdio.h>
#include "return_codes.h"

#include "tree.h"
#include "tree_methods.h"

#include "string_t.h"

#include "menu.h"

#include "preprocess.h"

#include "balance_tree.h"

#include "hash.h"

int main(void)
{
    int rc = OK;
    
    tree_t *tree = NULL;
    tree_t *balanced = NULL;
    hash_t hash_table;


    size_t size = 0;
    string_t array[1000];

    int COMPARSIONS = 3;

    //string_t res[1000];
    //int res_size = 0;

    
    //1. open file
    FILE *src;
    act_open_file(&src);

    if (src)
    {
        rc = read_string_array(array, &size, src);
        fclose(src);
        src = NULL;
        //output_string_array(array, size);
        //printf("RC: %d", rc);
        if (rc == OK)
        {
            printf("Sucessfully read\n");
        }
        else
        {
            printf("Incorrect data in file\n");
        }
    }
    else
    {
        rc = -1;
    }
    //create tree
    if (rc == OK)
    {
        rc = create_tree(&tree);    

        if (rc == OK)
        {
            rc = init_add_strings(array, size, &(tree->root));
        }
        else
        {
            printf("Incorrect data in file, can't create tree\n");
        }
    }

    //create balanced tree
    if (rc == OK)
    {
        rc = create_tree(&balanced);    

        if (rc == OK)
        {
            //rc = init_add_strings(array, size, &(balanced->root));
            if (rc == OK)
            {
                for (int i = 0; i < size; i++)
                {
                    node_tr *elem = create_node_tree();
                    elem->data = (void*)((array[i]).word);
                    balanced->root = insert_balance(balanced->root, elem);
                }
            }
        }
        else
        {
            printf("Incorrect data in file, can't create tree\n");
        }
    }

    //create hash table
    if (rc == OK)
    {
        printf("Read strings: %zu\nInput size of hash table to create.\n"
        "Input 0 to make default size:\n", size);
        int hash_size = 0;
        int read = scanf("%d", &hash_size);
        flush_input();

        int min_prime;

        if (read == 1)
        {
            if (hash_size == 0)
            {
                min_prime = near_prime(size);
                //rc = fill_hash_table(&hash_table, array, (int)size, min_prime);
            }
            else if (hash_size >= 0)
            {
                min_prime =  hash_size;
                //rc = fill_hash_table(&hash_table, array, (int)size, hash_size);
            }
            else
            {
                min_prime = near_prime(size);
                printf("Incorrect range size\n");
            }
            
        }
        else
        {
            min_prime = near_prime(size);
            printf("Incorrect size: NAN\n");
        }

        rc = fill_hash_table(&hash_table, array, (int)size, min_prime);

        
    }
    else
    {
        printf("Incorrect data in file, can't create hash table\n");
    }



    
    print_menu_actions();
    char *command = read_command();

    while (strcmp(command, "exit") != 0)
    {
        if (strcmp(command, "comp num") == 0)
        {
            printf("Input number of comparsions:\n");
            int comp = 0;
            int read = scanf("%d", &comp);
            flush_input();
            if (read == 1)
            {
                if (comp > 0)
                {
                    COMPARSIONS = comp;
                }
                else
                {
                    printf("Incorrect range comprsions\n");
                }
            }
            else
            {
                printf("NAN comparsions input\n");
            }
        }
        //REHASH
        if (strcmp(command, "rehash") == 0)
        {
        printf("Read strings: %zu\nInput size of hash table to recreate.\n"
        "Input 0 to make default size:\n", size);
        int hash_size = 0;
        int read = scanf("%d", &hash_size);
        flush_input();

        int min_prime;

        if (read == 1)
        {
            if (hash_size == 0)
            {
                min_prime = near_prime(size);
                rc = rehash(&hash_table, min_prime);
            }
            else if (hash_size >= 0)
            {
                min_prime =  hash_size;
                rc = rehash(&hash_table, min_prime);
            }
            else
            {
                //min_prime = near_prime(size);
                printf("Incorrect range size\n");
            }
            
        }
        else
        {
            //min_prime = near_prime(size);
            printf("Incorrect size: NAN\n");
        }

        //rc = fill_hash_table(&hash_table, array, (int)size, min_prime);
        }

        // OUT OPTIONS
        if (strcmp(command, "out tree") == 0)
        {
            if (tree && tree->root)
            {
                
                if (tree->root->left == NULL && tree->root->right == NULL)
                {
                    printf("\nTree root: %s\n", (char*)tree->root->data);
                }
                //printf("\nTree:\n");
                else
                {
                    act_output_tree(tree);
                }
            }
            else if (tree && !(tree->root))
            {
                printf("Tree is empty\n");
            }
            else
            {
                printf("No tree, please open file using command\n");
            }
            //flush_input();            
        }

        if (strcmp(command, "out bal") == 0)
        {
            if (balanced && balanced->root)
            {
                
                if (balanced->root->left == NULL && balanced->root->right == NULL)
                {
                    printf("\nTree root: %s\n", (char*)balanced->root->data);
                }
                //printf("\nTree:\n");
                else
                {
                    act_output_tree(balanced);
                }
            }
            else if (balanced && !(balanced->root))
            {
                printf("Tree is empty\n");
            }
            else
            {
                printf("No tree, please open file using command\n");
            }
            //flush_input();
        }

        if (strcmp(command, "out hash") == 0)
        {
            if (size != 0)
            {
                print_hash_table(&hash_table);
            }
            else
            {
                printf("No hash table, please open file using command\n");
            }
        }

        //ADD OPTIONS
        else if (strcmp(command, "add tree") == 0)
        {
            if (tree)
            {
                char *string = NULL;
                int read = act_input_string(&string);
                if (read == OK)
                {
                    //deb
                    //printf("String input: %s\n", string);
                    int c = 0;
                    node_tr *curr = find(tree->root, string, &c);
                    if (!curr)
                    {
                        act_insert_node(tree, string);
                    }
                    else
                    {
                        printf("Can't insert dublicate string\n");
                    }
                    //free(string);
                }
                else
                {
                    printf("READ ERROR\n");
                }
            }
            else
            {
                printf("No tree, please open file using command\n");
            }
        }

        else if (strcmp(command, "add bal") == 0)
        {
            if (balanced)
            {
                char *string = NULL;
                int read = act_input_string(&string);
                if (read == OK)
                {
                    //deb
                    //printf("String input: %s\n", string);
                    int c;
                    node_tr *curr = find(balanced->root, string, &c);
                    if (!curr)
                    {
                        //act_insert_node(balanced, string);
                        node_tr *elem = create_node_tree();
                        elem->data = (void*)(string);
                        balanced->root = insert_balance(balanced->root, elem);
                        //balanced->root = balance(balanced->root);
                        
                    }
                    else
                    {
                        printf("Can't insert dublicate string\n");
                    }
                    //free(string);
                }
                else
                {
                    printf("READ ERROR\n");
                }
            }
            else
            {
                printf("No tree, please open file using command\n");
            }
        }

        else if (strcmp(command, "add hash") == 0)
        {
            if (hash_table.array && hash_table.real_size != 0)
            {
                char *string = NULL;
                int read = act_input_string(&string);
                if (read == OK)
                {
                    //deb
                    //printf("String input: %s\n", string);
                    int c = 0;
                    node_str *curr = find_hash(&hash_table, string, &c);
                    if (!curr)
                    {
                        if (c > COMPARSIONS)
                        {
                            rc = rehash(&hash_table, near_prime(hash_table.size * 2));
                        }

                        add_hash(&hash_table, (void*)string);
                    }
                    else
                    {
                        if (c > COMPARSIONS)
                        {
                            rc = rehash(&hash_table, near_prime(hash_table.size * 2));
                        }
                        printf("Can't insert dublicate string\n");
                    }
                    //free(string);
                }
                else
                {
                    printf("READ ERROR\n");
                }
            }
            else
            {
                printf("No hash, please open file using command\n");
            }
        }

        //DELETE OPTIONS
        else if (strcmp(command, "delete tree") == 0)
        {
            if (tree)
            {
                char *string = NULL;
                if (tree->root == NULL)
                {
                    printf("Tree is empty, nothing to delete\n");
                }
                else
                {
                int read = act_input_string(&string);
                if (read == OK)
                {
                    act_delete_node(tree, string);
                    free(string);
                }
                else
                {
                    printf("READ ERROR\n");
                } 
                }
            }
            else
            {
                printf("No tree, please open file using command\n");
            }
        }

        else if (strcmp(command, "delete bal") == 0)
        {
            if (balanced)
            {
                char *string = NULL;
                if (balanced->root == NULL)
                {
                    printf("Tree is empty, nothing to delete\n");
                }
                else
                {
                int read = act_input_string(&string);
                if (read == OK)
                {
                    //act_delete_node(tree, string);
                    balanced->root = delete_balance(balanced->root, string);
                    free(string);
                }
                else
                {
                    printf("READ ERROR\n");
                } 
                }
            }
            else
            {
                printf("No tree, please open file using command\n");
            }
        }

        else if (strcmp(command, "delete hash") == 0)
        {
            if (hash_table.array && hash_table.real_size != 0)
            {
                char *string = NULL;
                if (hash_table.real_size == 0)
                {
                    printf("Hash is empty, nothing to delete\n");
                }
                else
                {
                int read = act_input_string(&string);
                if (read == OK)
                {
                    //act_delete_node(tree, string);
                    //balanced->root = delete_balance(balanced->root, string);
                    delete_hash(&hash_table, string);
                    free(string);
                }
                else
                {
                    printf("READ ERROR\n");
                } 
                }
            }
            else
            {
                printf("No hash, please open file using command\n");
            }
        }

        //FIND OPTIONS
        else if (strcmp(command, "find tree") == 0)
        {
            if (tree && tree->root)
            {
                int comp = 0;
                char *word = NULL;
                act_input_string(&word);
                node_tr *found = act_find_word(tree->root, word, &comp);
                if (found)
                {
                    printf("Found: %s\n", (char*)found->data);
                } 
                else
                {
                    printf("No such value in tree\n");
                }
                //  
                printf("Comparsions: %d\n", comp);             
            }
            else if (tree && !(tree->root))
            {
                printf("Tree is empty\n");
            }
            else
            {
                printf("No tree, please open file using command\n");
            }
        }

        else if (strcmp(command, "find bal") == 0)
        {
            if (balanced && tree->root)
            {
                int comp = 0;
                char *word = NULL;
                act_input_string(&word);
                node_tr *found = act_find_word(balanced->root, word, &comp);
                if (found)
                {
                    printf("Found: %s\n", (char*)found->data);
                } 
                else
                {
                    printf("No such value in tree\n");
                } 
                //
                printf("Comparsions: %d\n", comp);             
            }
            else if (balanced && !(balanced->root))
            {
                printf("Tree is empty\n");
            }
            else
            {
                printf("No tree, please open file using command\n");
            }
        }

        else if (strcmp(command, "find hash") == 0)
        {
            //act_find_hash - to 

            if (hash_table.real_size != 0)
            {
                    int comp = 0;
                    node_str *found = act_find_word_hash(&hash_table, &comp);
                    if (found)
                    {
                        printf("Found: %s\n", (char*)found->data);
                    } 
                    else
                    {
                        printf("No such value in hash table\n");
                    } 
                    //
                    printf("Comparsions: %d\n", comp); 

                    if (comp > COMPARSIONS)
                    {
                        printf("Have to rehash\n");
                        rc = rehash(&hash_table, near_prime(hash_table.size * 2));
                    }      
                
         
            }
            else
            {
                printf("No data, please open file using command\n");
            }
        }

        //Open file
        else if (strcmp(command, "open") == 0)
        {
            if (src)
            {
                fclose(src); 
            }
            act_open_file(&src);

            rc = read_string_array(array, &size, src);
            fclose(src);
            src = NULL;
            //output_string_array(array, size);
            if (rc == OK)
            {
                printf("Sucessfully read\n");
            }
            else
            {
                printf("Incorrect data in file\n");
            }

            rc = create_tree(&tree);    

            if (rc == OK)
            {   
                rc = init_add_strings(array, size, &(tree->root));
            }
            else
            {
                printf("Incorrect data in file, can't create tree\n");
            }
        }

        //Compare
        else if (strcmp(command, "compare") == 0)
        {
            
            char *word = NULL;
            //
            act_input_string(&word);

            double timeT = 0, timeB = 0, timeH = 0;
            int memT = 0, memB = 0, memH = 0;
            int comT = 0, comB = 0, comH = 0;
            
            efficiency_tree(tree, word, &timeT, &memT, &comT);
            printf("Time tree: %lf ps, memory: %d bytes, comparsions: %d \n", timeT, memT, comT);
            efficiency_tree(balanced, word, &timeB, &memB, &comB);
            printf("Time balanced tree: %lf ps, memory: %d bytes, comparsions: %d \n", timeB, memB, comB);
            efficiency_hash(&hash_table, word, &timeH, &memH, &comH);
            printf("Time hash: %lf ps, memory: %d bytes, comparsions: %d \n", timeH, memH, comH);
        }

        else if (strcmp(command, "compare all") == 0)
        {
            double timeT = 0, timeB = 0, timeH = 0;
            int memT = 0, memB = 0, memH = 0;
            int comT = 0, comB = 0, comH = 0;
            effic_all_tree(tree, array, size, &timeT, &memT, &comT);
            printf("Time tree: %lf ps, memory: %d bytes, comparsions: %d \n", timeT, memT, comT);
            effic_all_tree(balanced, array, size, &timeB, &memB, &comB);
            printf("Time balanced tree: %lf ps, memory: %d bytes, comparsions: %d \n", timeB, memB, comB);
            effic_all_hash(&hash_table, array, size, &timeH, &memH, &comH);
            printf("Time hash: %lf ps, memory: %d bytes, comparsions: %d \n", timeH, memH, comH);
        }
         
        else
        {
            rc = UNKNOWN_COMMAND;
            if(! ((int)command[0] < 99))
            {
                //printf("UNKNOWN COMMAND\n");
            }
            
        }
        
        free(command);
        print_menu_actions();
        command = read_command();

    }


    //free_hash_table(&hash_table);

    free(command);

}
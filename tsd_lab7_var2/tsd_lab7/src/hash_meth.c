#include "hash.h"


int key_hash(char *string, int size)
{
    int value = 0;

    char *c = string;

    while (*c != '\0')
    {
        value += (int)(*c);
        c++;
    }
    //printf("%s : %d\n", string, value % size);
    return value % size;
    //return abs(num) % size;
}


/*
int find_next_empty_ind(hash_t *hash_table, int ind, int *count)
{
    for (int i = ind; i < hash_table->size; i++)
    {
        (*count)++;

        if (hash_table->key[i] == 0)
        {
            return i;
        }
    }

    for (int i = 0; i < ind; i++)
    {
        (*count)++;

        if (hash_table->key[i] == 0)
        {
            return i;
        }
    }

    printf("!!!!!!!!! -1 !!!!!!!!!");

    return -1;
}
*/

node_str * create_node_string()
{
    node_str *new_element = malloc(sizeof(node_str));

    if (new_element)
    {
        new_element->next = NULL;
        new_element->data = NULL;

    }
    return new_element;
}

int add_hash(hash_t *hash_table, void *data)
{
    int ind = key_hash((char *)data, hash_table->size);

    node_str *new_element = create_node_string();

    if (new_element)
    {
        //hash_table->array[ind] = new_element;
        node_str *cur = hash_table->array[ind];
        //node_str **prev = hash_table->array + ind;
        new_element->data = data;

        if (cur)
        {
            while (cur->next)
            {
                cur = cur->next;
            }
            cur->next = new_element;
        }
        else
        {
            hash_table->array[ind] = new_element;
        }
        hash_table->real_size++;

        return OK_HASH;
    }
    else
    {
        return -1; //alloc error
    }

}


int fill_hash_table(hash_t *hash_table, string_t *arr, int arr_size, int size)
{
    hash_table->real_size = 0;//arr->len;
    hash_table->size = size;

    //create hash table
    hash_table->array = malloc(hash_table->size * sizeof(node_str *));

    for (int i = 0; i < hash_table->size; i++)
    {
        hash_table->array[i] = NULL;
    }


    if (!hash_table->array)
    {
        return ERR_ALLOCATE_MEMORY;
    }

    for (int i = 0; i < arr_size; i++)
    {
        //int count = 1;
        //printf("Cur word is: %s\n", (arr + i)->word);
        int rc = add_hash(hash_table, (void *)(arr + i)->word);

        if (rc)
        {
            return ERR_OWERFLOW_TABLE;
        }
    }

    return OK_HASH;
}


int rehash(hash_t *hash_table, int size)
{
    node_str **arr = malloc(hash_table->real_size * sizeof(node_str *));
    int arr_size = hash_table->real_size;
    int index = 0;

    //all elements add to arr
    for (int i = 0; i < hash_table->size; i++)
    {
        node_str *cur = hash_table->array[i];
        node_str *next = NULL;
        if (cur)
        {
            while (cur)
            {
                next = cur->next;
                arr[index] = cur;
                index++; 
                cur = next;
            }
        }
    }
    //added, now delete hash_table array
    free(hash_table->array);
    
    hash_table->size = size;
    hash_table->real_size = 0;//arr->len;
    hash_table->size = size;

    //now create new hash_table array
    hash_table->array = malloc(hash_table->size * sizeof(node_str *));



    for (int i = 0; i < hash_table->size; i++)
    {
        hash_table->array[i] = NULL;
    }


    if (!hash_table->array)
    {
        return ERR_ALLOCATE_MEMORY;
    }

    for (int i = 0; i < arr_size; i++)
    {
        //int count = 1;
        //printf("Cur word is: %s\n", (arr + i)->word);
        int rc = add_hash(hash_table, (void *)(arr[i])->data);

        if (rc)
        {
            return ERR_OWERFLOW_TABLE;
        }
    }
    
    //now free previous elements and array
    for (int i = 0; i < arr_size; i++)
    {
        free(arr[i]);
    }
    free(arr);

    return OK_HASH;
}



int check_prime(int num)
{
    for (int i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }

    return 1;
}


int near_prime(int num)
{
    while (1)
    {
        num++;

        if (check_prime(num))
        {
            return num;
        }
    }
}

node_str* find_hash(hash_t *hash_table, char *string, int *comparsions)
{
    *comparsions = 0;
    int ind_to = key_hash(string, hash_table->size);
    node_str *cur = hash_table->array[ind_to];
    //node_str *prev = hash_table->array[ind_to];
    if (cur)
    {
        //int move = 0;
        
        while(cur && strcmp((char *)cur->data, string) != 0)
        {
            //move++;
            //prev = cur;
            (*comparsions)++;
            //printf("CUR: %s\n", (char *)cur->data);
            cur = cur->next;
        }
        (*comparsions)++;
    }
    //move++;
    return cur;
    
}

void delete_hash(hash_t *hash_table, char *string)
{
    //int ind_to = key_hash(string, hash_table->size);
    int c = 0;
    node_str *deleting = find_hash(hash_table, string, &c);
    if (deleting)
    {
        int index = key_hash((char *)deleting->data, hash_table->size);
        if (hash_table->array[index] == deleting)
        {
            node_str *next = deleting->next;
            free(deleting);
            
            hash_table->array[index] = next; // //nullify pointer to that value 

        }
        else
        {
            node_str *cur = hash_table->array[index];
            node_str *prev = hash_table->array[index];
            while (cur != deleting)
            {
                prev = cur;
                cur = cur->next;
            }
            node_str *next = cur->next;
            free(cur);
            prev->next = next;

        }
        (hash_table->real_size)--;
    }
    else
    {
        printf("Nothing to delete, no such data\n");
    }
}


void free_hash_table(hash_t *hash_table)
{
    for (int i  = 0; i < hash_table->size; i++)
    {
        node_str *cur = hash_table->array[i];
        node_str *next = NULL;
        if (cur)
        {
            while (cur)
            {
                next = cur->next;
                free(cur);
                cur = next;
            }
        }
    }
    free(hash_table->array); // free the "container" table
}


void print_hash_table(hash_t *hash_table)
{
    for (int i  = 0; i < hash_table->size; i++)
    {
        node_str *cur = hash_table->array[i];
        if (cur)
        {
            printf("%d | ", key_hash((char*)cur->data, hash_table->size));
            while (cur)
            {
                if (cur->data)
                {
                    printf("%s -> ", (char *)cur->data);
                }
                cur = cur->next;
            }
            printf("\n");
        }
    }
}

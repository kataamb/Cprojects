#include "keytable.h"

//create
int create_keys(key_t **keys, size_t size)
{
    int rc = OK;
    (*keys) = NULL; //do it to prevert leaks
    (*keys) = (key_t*)calloc(size, sizeof(key_t));
    if (*keys == NULL)
    {
        rc = ALLOC_ERROR;
    }
    return rc;
}

/*
    realloc
*/
int realloc_keys(key_t **keys, size_t size, size_t new_size)
{
    key_t *new_arr = NULL;
    int rc = create_keys(&new_arr, new_size);
    if (rc != OK)
    {
        return rc;
    }
    for (size_t i = 0; i < size; i++)
    {
        memcpy(new_arr + i, *keys + i, sizeof(key_t));
    }
    free(*keys);
    *keys = new_arr;

    return rc;
}

/*
    delete
*/
void delete_keys(key_t **keys, size_t size)
{
    free(*keys);
 
    (*keys) = NULL; //to prevert leaks and heap disasters  

}

/*
    fill with values
*/
void initialize_keys(perform *darr_perform, size_t size, key_t **keys)
{
    for (size_t i = 0; i < size; i++)
    {
        strcpy((*keys + i)->perform_name, (darr_perform + i)->perform_name);
        (*keys + i)->index = i + 1;
    }
}


/*
  output key (one)
*/
void output_key(key_t *key)
{
    for (size_t i = 0; i < 21 * 2; i++)
        printf("_");
    printf("\n");

    char buff[MAX_STRING_LEN];
    itoa(key->index, buff);
    
    printf("|");
    printf("%-20s|", buff);
    printf("%-20s|", key->perform_name);
    

    printf("\n");
}


/*
*/
void output_keys(key_t **keys, size_t size)
{
    printf("\nKEYS:\n");

    for (size_t i = 0; i < 21 * 2; i++)
        printf("_");
    printf("\n");
    //
    //printf("");
    printf("|%-20s|%-20s|\n", "INDEX", "PERFORMANCE");
    for (size_t i = 0; i < size; i++)
    {
        output_key(*keys + i);
    }
}
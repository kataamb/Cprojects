#include "darr_perf.h"

/*
    create perform dynamic array
*/
int create_perf_darray(perform **darr_perform, size_t size)
{
    int rc = OK;
    (*darr_perform) = NULL; //do it to prevert leaks
    (*darr_perform) = (perform*)calloc(size, sizeof(perform));
    if (*darr_perform == NULL)
    {
        rc = ALLOC_ERROR;
    }
    return rc;
}

int realloc_perf_darray(perform **darr_perform, size_t size, size_t new_size)
{
    perform *new_arr = NULL;
    int rc = create_perf_darray(&new_arr, new_size);
    if (rc != OK)
    {
        return rc;
    }
    for (size_t i = 0; i < size; i++)
    {
        memcpy(new_arr + i, *darr_perform + i, sizeof(perform));
    }
    free(*darr_perform);
    *darr_perform = new_arr;

    return rc;
}

/*
    free perform dynamic array
*/
void delete_perf_darray(perform **darr_perform, size_t size)
{
    free(*darr_perform);
 
    (*darr_perform) = NULL; //to prevert leaks and heap disasters  

}

int read_darr_perf_tf(FILE *src, perform **darr_perform, size_t *real_size, size_t *size)
{
    int rc = OK;
    fseek(src, 0, SEEK_SET);
    size_t  i = 0;
    while (rc == OK)
    {
        //resize array if it's not enough    
        if (i >= *real_size && rc == OK)
        {
            rc = realloc_perf_darray(darr_perform, *real_size, *real_size + 10);
            if (rc == OK)
            {
                *real_size = *real_size + 10;
            }
            else 
            {
                return rc;
            }
        } 

        rc = input_perfomance_tf(src, *darr_perform + i);
        i++;
        if (rc == UNEXPECTED_EOF) //so we at the end of file and it's ok
        {
            rc = OK;
            break;
        }
   
    }
    *size = i - 1;
    return rc;
}

void output_darr_perf(perform **darr_perform, size_t size)
{
    if (size == 0)
    {
        printf("No data\n");
    }
    else
    {

    printf("\nTABLE\n");

    for (int i = 0; i < 21 * 10 + 22 + 7; i++)
    {
        printf("_");
    }
    printf("\n");

    printf("|%-10s|%-20s|%-20s|%-20s|%-21s|%-20s|%-20s|%-20s|%-20s|%-20s|%-20s|%-20s|\n", "index", "theatre", "performance", "director", "price range",\
        "type", "genre", "age", "time", "composer", "country", "min age");
    
    ///////////////////
    for (int i = 0; i < 10 + 21 * 10 + 22; i++)
    {
        printf("_");
    }
    printf("\n");
    //
    //printf("");
    for (size_t i = 0; i < size; i++)
    {
        char buff[255];
        itoa((int)(i + 1), buff);
        printf("|%-10s|", buff);
        output_performance(*darr_perform + i);

        for (int i = 0; i < 10 + 21 * 10 + 22; i++)
        {
            printf("_");
        }
        printf("\n");
    }

    }

}
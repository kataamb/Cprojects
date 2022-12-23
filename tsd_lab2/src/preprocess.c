#include "preprocess.h"

int add_performance(perform **darr_per, size_t *size, size_t *real_size, perform *new_perf)
{
    int rc = OK;
    if (*size <= *real_size)
    {
        memcpy(*darr_per + *size, new_perf, sizeof(perform));
        (*size)++;
    }
    else
    {
        rc = realloc_perf_darray(darr_per, *real_size, *real_size + 10);
        if (rc != OK)
        {
            return rc;
        }
        *real_size = *size + 10;

        memcpy(*darr_per + *size, new_perf, sizeof(perform));
        (*size)++;
    }
    return rc;
}

/*
    add key
*/
int add_key(key_t **keys, size_t *size, size_t *real_size, key_t *new_key)
{
    int rc = OK;
    //printf("TRRR %zu %zu\n", *size, *real_size);
    if (*size <= *real_size)
    {
        memcpy(*keys + *size - 1, new_key, sizeof(key_t));
    }
    else
    {
        rc = realloc_keys(keys, *real_size, *real_size + 10);
        if (rc != OK)
        {
            return rc;
        }
        *real_size = *size + 10;

        memcpy(*keys + *size - 1, new_key, sizeof(key_t));
    }
    return rc;
}

void univ_swap(void *pt1, void *pt2, size_t size)
{
    char buffer[255];
    memcpy(&buffer, pt1, size);
    memcpy(pt1, pt2, size);
    memcpy(pt2, &buffer, size);
}

void swap_perf(perform* perf1, perform* perf2)
{
    perform buffer;
    memcpy(&buffer, perf1, sizeof(perform));
    memcpy(perf1, perf2, sizeof(perform));
    memcpy(perf2, &buffer, sizeof(perform));
}

void swap_key(key_t* k1, key_t* k2)
{
    key_t buffer;
    memcpy(&buffer, k1, sizeof(key_t));
    memcpy(k1, k2, sizeof(key_t));
    memcpy(k2, &buffer, sizeof(key_t));
}

int delete_perform(perform **darr, size_t *size, int num)
{
    int rc = OK;
    if (num <= 0 || num > *size)
    {
        return INCORRECT_INDEX;
    }
    for (size_t i = num - 1; i < *size - 1; i++)
    {
        swap_perf(*darr + i, *darr + i + 1);
    }
    (*size)--;
    return rc;
}

int delete_key(key_t **keys, size_t *size, int num)
{
    int rc = OK;

    if (num <= 0 || num > *size)
    {
        return INCORRECT_INDEX;
    }
    for (size_t i = num - 1; i < *size - 1; i++)
    {
        swap_key(*keys + i, *keys + i + 1);
        (*keys + i)->index -= 1;
    }
    (*size)--;
    return rc;
}

void shuffle(perform *darr, size_t size)
{
    int num;
    for (size_t i = 0; i < size; i++)
    {
        srand(i);
        num = rand() % size;
        swap_perf(darr + i, darr + num);
    }
}

void shuffle_k(key_t *darr, size_t size_k)
{
    int num;
    for (size_t i = 0; i < size_k; i++)
    {
        srand(i);
        num = rand() % size_k;
        swap_key(darr + i, darr + num);
    }
}


void write_perform_tf(FILE *src, perform *act)
{
    char buf1[MAX_STRING_LEN], buf2[MAX_STRING_LEN];
    fprintf(src, "%s\n", act->theatre); //"|%-30s|"
    fprintf(src, "%s\n", act->perform_name);
    fprintf(src, "%s\n", act->director);

    itoa(act->minprice, buf1);
    itoa(act->maxprice, buf2);
    
    fprintf(src, "%s %s\n", buf1, buf2);
    fprintf(src, "%s\n", act->type);

    if (strcmp(act->type, ADULTS) == 0)
    {
        //genre, is
        fprintf(src, "%s\n", act->variable_type.adults.genre);
        
        
    }
    else if (strcmp(act->type, KIDS) == 0)
    {
        //genre, is
        fprintf(src, "%s\n", act->variable_type.kids.genre);

        // age, is
        itoa(act->variable_type.kids.age, buf1);

        fprintf(src, "%s\n", buf1); //!!!!

        //time, is
        itoa(act->variable_type.kids.time, buf1);
        fprintf(src, "%s\n", buf1);        
        
    }
    else if (strcmp(act->type, MUSICLE) == 0)
    {
        //time, is
        itoa(act->variable_type.musical.time, buf1);
        fprintf(src, "%s\n", buf1);
        //comp, is
        fprintf(src, "%s\n", act->variable_type.musical.composer);
        //country, is
        fprintf(src, "%s\n", act->variable_type.musical.country);
        //min age, is
        itoa(act->variable_type.musical.min_age, buf1);
        fprintf(src, "%s\n", buf1);      
    } 
    
}
#include "string_t.h"

//rc2 = getline(&buff2, &leng2, src);

int read_string_array(string_t *array, size_t *num, FILE *src)
{
    int rc = OK;
    rewind(src);
    *num = 0;
    size_t len;

    char *buff = NULL;

    while (!feof(src) && rc == OK)
    {
        rc = getline(&buff, &len, src);

        if (rc != -1)
        {
            rc = OK;
            (array[*num]).word = calloc(1, len);
            if ((array[*num]).word)
            {
                //remove \n
            
                len = strlen(buff);
                if (buff[len - 1] == '\n')
                {
                    buff[len - 1] = '\0';
                }
                
                //deb
                //printf("Current string is: %s\n", buff);
                strcpy((char*)(array[*num]).word, buff);
                (*num)++;
            }
            else
            {
                rc = ALLOC_ERROR;
            }
            
        }
        else
        {
            rc = READ_ERROR;
        }
        free(buff);
        buff = NULL;
    }
    return rc;
}


void output_string_array(string_t *arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%s\n", (char*)((arr[i]).word));
    }
}


void free_string_array(string_t *arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        free(arr[i].word);
    }
}

int find_letter_words_file(string_t *array, int *num, char letter, FILE *src)
{
    int rc = OK;
    rewind(src);
    *num = 0;
    size_t len;

    char *buff = NULL;

    while (!feof(src) && rc == OK)
    {
        rc = getline(&buff, &len, src);
        if (rc != 1)
        {
            rc = OK;
            if (buff[0] == letter)
            {
                (array[*num]).word = calloc(1, len);
                if ((array[*num]).word)
                {
                //remove \n
            
                    len = strlen(buff);
                    if (buff[len - 1] == '\n')
                    {
                        buff[len - 1] = '\0';
                    }
                
                //deb
                //printf("Current string is: %s\n", buff);
                    strcpy((char*)(array[*num]).word, buff);
                    (*num)++;
                }
                else
                {
                    rc = ALLOC_ERROR;
                }
            }
            
            
        }
        else
        {
            rc = READ_ERROR;
        }
        free(buff);
        buff = NULL;
    }
    return rc;
}
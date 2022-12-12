#include "hash.h"
#include "menu.h"

int main()
{
    int rc = 0;
    size_t size = 0;
    string_t array[1000];

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
        rc = -1; //alloc error
    }

    hash_t hash_table;

    rc = fill_hash_table(&hash_table, array, (int)size, 31);
    print_hash_table(&hash_table);
    printf("\n");

    //char *str = (char *)hash_table.array[0]->data;
    //node_str *nextpt = hash_table.array[0]->next;
    //printf("Pt 0 next: %p", (void *)nextpt);

    //printf("Str 0: %s\n", str);

    delete_hash(&hash_table, "Dandelion");

    rehash(&hash_table, 109);

    print_hash_table(&hash_table);

}

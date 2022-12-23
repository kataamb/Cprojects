#include "main_functions.h"


int add_f(perform **arr_perform, size_t *size, size_t *real_size)
{
    perform new_perform;
    int rc = input_perfomance_cs(&new_perform);
    if (rc == OK)
    {
        rc = add_performance(arr_perform, size, real_size, &new_perform);
    }
    return rc;
}


int add_f_keys(perform **arr_perform, size_t *size, key_t **keys,size_t *size_k, size_t *real_size_k)
{
    key_t new_key;
    int rc = OK;
    
    strcpy(new_key.perform_name, (*arr_perform + *size - 1)->perform_name);
    new_key.index = (size_t)(*size);

    //printf("new key: %s\n", new_key.perform_name);
    //printf("new key index: %zu\n", new_key.index);
    

    *size_k = *size;
    
    //printf("New size is : %zu\n", *size_k);
    
    
    rc = add_key(keys, size_k, real_size_k, &new_key);

    //printf("New size is : %zu\n", *size_k);
    
    
    return rc;
}


int delete_f(perform **arr_perform, size_t *size, key_t **keys, size_t *size_k)
{
    int rc = OK;
    //int num = 5;
    char num_par[MAX_STRING_LEN];
    printf("Input index:\n");
    rc = read_string(num_par);

    if (rc == OK)
    {
        if (is_integer(num_par))
        {
            rc = delete_perform(arr_perform, size, atoi(num_par));
            if (rc == OK)
            {
                delete_key(keys, size_k, atoi(num_par));
            }
        }
        else
        {
            rc = NAN_INPUT_INTEGER;
        }
        
    }
    else 
    {
        rc = NAN_INPUT_INTEGER;
    }
    return rc;
}

void print_f(perform **d_arr, key_t **keys, size_t size_k)
{
    if (size_k == 0)
    {
        printf("No data\n");
    }
    else
    {

    printf("\nTABLE\n");

    for (int i = 0; i < 21 * 10 + 22; i++)
    {
        printf("_");
    }
    printf("\n");

    printf("|%-10s|%-20s|%-20s|%-20s|%-21s|%-20s|%-20s|%-20s|%-20s|%-20s|%-20s|%-20s|\n", "index", "theatre", "performance", "director", "price range",\
        "type", "genre", "age", "time", "composer", "country", "min age");
    for (int i = 0; i < 21 * 10 + 22; i++)
    {
        printf("_");
    }
    printf("\n");

    //output_darr_perf(d_arr, size);
    for (size_t i = 0; i < size_k; ++i)
    {
        int curr_index = (*keys + i)->index - 1;
        char buff[255];
        itoa(curr_index + 1, buff);
        printf("|%-10s|", buff);
        output_performance((*d_arr + curr_index));
        for (int i = 0; i < 21 * 10 + 22; i++)
        {
            printf("_");
        }
        printf("\n");
    }

    /////print keys
    output_keys(keys, size_k);
    //
    for (int i = 0; i < 21 * 2; i++)
    {
        printf("_");
    }
    printf("\n");
    } ///!!!!! it's not ok it's bad codestyle
}

/*
    prints matching items:
    musicals for special age
    with time LESS than it's so
*/
int filter_f(perform **d_arr, size_t size)
{
    int rc = OK;
    int age, time;
    char buff[MAX_STRING_LEN];

    printf("Input age: \n");
    rc = read_string(buff);
    if (rc == OK)
    {
        if (is_integer(buff))
        {
            age = atoi(buff);
        }
        else
        {
            return NAN_INPUT_INTEGER;
        }
    }
    else
    {
        return NAN_INPUT_INTEGER;
    }

    printf("Input time: \n");
    rc = read_string(buff);
    if (rc == OK)
    {
        if (is_integer(buff))
        {
            time = atoi(buff);
        }
        else
        {
            return NAN_INPUT_INTEGER;
        }
    }
    else
    {
        return NAN_INPUT_INTEGER;
    }

    int number = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (strcmp((*d_arr + i)->type,  KIDS) == 0) // what if strcpy instead of strcmp
        {
            //debug
            //printf("Current %s ", (*d_arr + i)->type);
            //printf("Age: %d Time: %d \n", (*d_arr + i)->variable_type.kids.age, (*d_arr + i)->variable_type.kids.time);
            if ((*d_arr + i)->variable_type.kids.age >= age && (*d_arr + i)->variable_type.kids.time < time)
            {
                number++;
                output_performance(*d_arr + i);
            }
        }
    }
    if (number == 0)
        rc = NO_SUCH_ENTRIES;


    return rc;
}

/*
    writes structures to text file
*/
void write_tf_f(FILE *src, perform *d_arr, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        write_perform_tf(src, d_arr + i);
    }
}


void message(void)
{
    printf("\n"
    "Variant 5\n"
    "This program provides some data and keys functions with theatre performance-list.\n"
    "Firstly input filename (if use empty string - default data file)\n"
    "You can input commands below:\n"
    "   add - to add struct to the end of table\n"
    "   delete - to delete struct from table by index\n"
    "   print - to output to console all table and keys\n"
    "   sort - sort table and keys and compare times of different sort types, sort by PERFORMANCE name\n"
    "   quick sort table - to sort table (true values) with quick sort\n"
    "   slow sort table - to sort table (true values) with quick sort\n"
    "   quick sort keys - to sort table (true values) with quick sort\n"
    "   slow sort keys - to sort table (true values) with quick sort\n"
    "   filter - to output to console all structs with type KIDS, age = input age and time of perform < input time \n"
    "   save - to save changed data to text file\n"
    "   exit - end of programm.\n"
    "Text lines must be <= 20 symbols, \n"
    "price range must be two natural numbers, first <= second.\n"
    "Other number fields must be natural \n\n");
}

void compare_sort_f(perform *arr_perform, size_t size, key_t *keys, size_t size_k)
{
    int n = 100;
    shuffle(arr_perform, size); 
    double time1 = 0;
    for (int i = 0; i < n; i++)
    {
        shuffle(arr_perform, size);
        time1 += bubble_time_p(&arr_perform, size, comparator_prf);
    }
    time1 /= n;
    size_t data_size = sizeof(perform) * (size);
    printf("TIME AND SIZE UNEFFECTIVE TABLE: %lf picoseconds, MEMORY: %zu bytes\n", time1, data_size);

    shuffle(arr_perform, size);
    double time2 = 0;
    for (int i = 0; i < n; i++)
    {
        shuffle(arr_perform, size);
        time2 += qsort_time_p(&arr_perform, size, comparator_prf);
    }
    time2 /= n;
    data_size = sizeof(perform) * (size);
    printf("TIME AND SIZE EFFECTIVE TABLE: %lf picoseconds, MEMORY: %zu bytes\n", time2, data_size);

    double time3 = 0;
    shuffle_k(keys, size_k);
    for (int i = 0; i < n; i++)
    {
        shuffle_k(keys, size_k);
        time3 += bubble_time_k(&keys, size_k, comparator_key);
    }
    time3 /= n;
    data_size = sizeof(perform) * (size);
    size_t keys_size = sizeof(key_t) * (size_k);
    printf("TIME AND SIZE UNEFFECTIVE KEYS: %lf picoseconds, MEMORY: %zu + %zu bytes\n", time3, data_size, keys_size);

    double time4 = 0;
    shuffle_k(keys, size_k);
    for (int i = 0; i < n; i++)
    {
        shuffle_k(keys, size_k);
        time4 += qsort_time_k(&keys, size_k, comparator_key);
    }
    time4 /= n;
    data_size = sizeof(perform) * (size);//sizeof(arr_perform);
    keys_size = sizeof(key_t) * (size_k);
    printf("TIME AND SIZE UNEFFECTIVE KEYS: %lf picoseconds, MEMORY: %zu + %zu bytes\n", time4, data_size, keys_size);

    shuffle(arr_perform, size);
    initialize_keys(arr_perform, size, &keys);
}

void print_error_message(int rc)
{
    switch (rc)
    {
        case ALLOC_ERROR:
            printf("MEMORY ALLOCATION ERROR\n");
            break;
        case NAN_PRICE_RANGE:
            printf("PRICE RANGE IS NOT A NUMBER\n");
            break;
        case INCORRECT_PRICE_RANGE:
            printf("INCORRECT PRICE RANGE\n");
            break;
        case NAN_INTEGER_FIELD:
            printf("VALUE FOR INTEGER FIELD IS NOT INTEGER\n");
            break;
        case INCORRECT_GENRE_FIELD:
            printf("INCORRECT GENRE FIELD\n");
            break;
        case INCORRECT_TYPE:
            printf("INCORRECT TYPE OF PERFORMANCE\n");
            break;
        case UNEXPECTED_EOF:
            printf("GOT UNEXCPECTED EOF VIA READING STRING\n");
            break;
        case TOO_LONG_STRING_ERROR:
            printf("STRING IS TOO LONG (MUST BE <= 255 SYMBOLS\n");
            break;
        case INCORRECT_INDEX:
            printf("INCORRECT INDEX OF ARRAY\n");
            break;
        case NAN_INPUT_INTEGER:
            printf("INPUT VALUE MUST BE INTEGER\n");
            break;
        case UNKNOWN_COMMAND:
            printf("UNKNOWN NAME OF COMMAND, PLEASE TRY ONE MORE TIME\n");
            break;
        case NO_SUCH_ENTRIES:
            printf("No such entries in table\n");
            break;
    }
}
#include "main_functions.h"


/*
    "   quick sort table - to sort table (true values) with quick sort\n"
    "   slow sort table - to sort table (true values) with quick sort\n"
    "   quick sort keys - to sort table (true values) with quick sort\n"
    "   slow sort keys - to sort table (true values) with quick sort\n"
*/

int main(void)
{
    //Enter message
    //"   save - to save changed data to text file\n"
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
    
    "   exit - end of programm.\n"
    "Text lines must be <= 20 symbols, \n"
    "price range must be two natural numbers, first <= second.\n"
    "Other number fields must be natural \n");

    int rc = -1;
    
    perform *arr_perform = NULL;

    /* Input filename to open*/

    char filename[255];
    FILE *src = fopen("data.txt", "r");
    
    while (rc != OK)
    {     
        printf("Input filename:\n");  
        rc = read_string(filename);
        if (rc == OK)
        {
            if (strcmp("", filename) == 0)
            {
                rc = OK;
            }
            else
            {
                FILE *src1 = fopen(filename, "r");
                if (!src1)
                {
                    rc = INCORRECT_FILE;
                }
                else
                {
                    fclose(src);
                    fclose(src1);
                    src = fopen(filename, "r");
                    rc = OK;
                }
            }
        }
         
    }
    //FILE *src = fopen("data.txt", "r"); 

    size_t real_size = 2;
    size_t size = 2;

    
    rc = create_perf_darray(&arr_perform, real_size);

    if (rc != OK)
    {
        print_error_message(rc);
        return OK;
    }


    //read from file

    rc = read_darr_perf_tf(src, &arr_perform, &real_size, &size);
    if (rc != OK)
    {
        print_error_message(rc);
        return OK;
    }

    //also create keys array
    size_t real_size_k = real_size;
    size_t size_k = size;
    key_t *keys = NULL;
    rc = create_keys(&keys, real_size_k);
    if (rc != OK)
    {
        print_error_message(rc);
        return OK;
    }

    //initialize keys
    size_k = size; 
    initialize_keys(arr_perform, size_k, &keys);


    char command[30] = "trr"; // command


    printf("Input command:\n");

    rc = read_string(command);

    

    while (strcmp(command, EXIT) != 0)
    {
        if (rc == OK)
        {
            //ADD
            if (strcmp(command, ADD) == 0)
            {
                rc = add_f(&arr_perform, &size, &real_size);
                if (rc == OK)
                {
                    ///here add key to keys table
                    rc = add_f_keys(&arr_perform, &size, &keys, &size_k, &real_size_k);
                }
            }
            //DELETE
            else if (strcmp(command, DELETE) == 0)
            {
                rc = delete_f(&arr_perform, &size, &keys, &size_k);
            }
            //PRINT
            else if (strcmp(command, PRINT) == 0)
            {
                output_darr_perf(&arr_perform, size);
                output_keys(&keys, size_k);
            }
            //SORT
            else if (strcmp(command, SL_SORT_T) == 0)
            {
                //less effective
                //shuffle array 
                shuffle(arr_perform, size);

                //int time1 = 
                bubble_time_p(&arr_perform, size, comparator_prf);
                //printf("TIME UNEFFECTIVE TABLE: %d ms\n", time1);
                //and keys init
                initialize_keys(arr_perform, size_k, &keys);
            }
            else if (strcmp(command, Q_SORT_T) == 0)
            {
                //shuffle array
                shuffle(arr_perform, size);

                //int time2 = 
                qsort_time_p(&arr_perform, size, comparator_prf);
                //printf("TIME EFFECTIVE TABLE: %d ms\n", time2);
                // and keys ini
                initialize_keys(arr_perform, size_k, &keys);
            }
            //SORT KEYS
            else if (strcmp(command, SL_SORT_K) == 0)
            {
                //shuffle there array and keys initialize
                //shuffle(arr_perform, size);
                //initialize_keys(arr_perform, size_k, &keys);

                //int time3 = 
                bubble_time_k(&keys, size_k, comparator_key);
                //printf("TIME UNEFFECTIVE KEYS: %d ms\n", time3);
            }
            else if (strcmp(command, Q_SORT_K) == 0)
            {
                //shuffle there array and keys initialize
                //shuffle(arr_perform, size);
                //initialize_keys(arr_perform, size_k, &keys);

                //int time4 = 
                qsort_time_k(&keys, size_k, comparator_key);
                //printf("TIME EFFECTIVE KEYS: %d ms\n", time4);
            }
            //COMPARE SORT
            else if (strcmp(command, COMPARE_SORT) == 0)
            {
                compare_sort_f(arr_perform, size, keys, size_k);
                /*
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
                */
            }
            //PRINT BY TABLE          
            else if (strcmp(command, PRINT_BY_TABLE) == 0)
            {
                print_f(&arr_perform, &keys, size_k);
            }
            //MENU
            else if (strcmp(command, MENU) == 0)
            {
                message();
            }
            //FILTER
            else if (strcmp(command, FILTER) == 0)
            {
                rc = filter_f(&arr_perform, size);
            }
            //SAVE TO FILE
            else if (strcmp(command, SAVE) == 0)
            {
                rc = -1;
                //here realize correct input of file (as above)
                //and realize finction of writing stuctures to file
                /*
                char filename2[255];
                printf("Input filename to save to:\n");  
                rc = read_string(filename2);
                FILE *dst = fopen(filename2, "w");
    
                while (rc != OK)
                {                         
                    if (rc == OK)
                    {
                        if (strcmp("", filename2) == 0)
                        {
                            rc = OK;
                        }
                        else
                        {
                            FILE *dst = fopen(filename2, "w");
                            if (!dst)
                            {
                                rc = INCORRECT_FILE;
                            }
                            else
                            {   
                                rc = OK;
                            }
                        }
                    }
         
                }
                //write_tf_f(dst, arr_perform, size);
                //fclose(dst);
                */
            }
            else
            {
                rc = UNKNOWN_COMMAND;
            }
        }

        //debug
        //printf("Command is: %s\n", command);
        //printf("rc: %d\n", rc);


        ////////if there were mistakes
        print_error_message(rc);

        //input next command
        printf("Input command:\n");
        rc = read_string(command);

        //debug
        //printf("Command is: %s\n", command);
    }

    delete_keys(&keys, real_size);
    delete_perf_darray(&arr_perform, real_size);

    /*
    if (rc == OK)
    {
        rc = read_darr_perf_tf(src, &arr_perform, &real_size, &size);
        if (rc == OK)
        {
            printf("real size: %zu\n", real_size);
            printf("size: %zu\n", size);
            //swap_perf(arr_perform + 0, arr_perform + 1);
            perform new_perform;
            rc = input_perfomance_cs(&new_perform);
            if (rc == OK)
            {
                rc = add_performance(&arr_perform, &size, &real_size, &new_perform);
                output_darr_perf(&arr_perform, size);
            }
            
        }
        delete_perf_darray(&arr_perform, size);
    }
    */
    return rc;
}
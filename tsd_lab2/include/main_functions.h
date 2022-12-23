#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <stddef.h>
#include "return_codes.h"
#include "perfomance.h"
#include "perfomance_methods.h"
#include "strings_func.h"
#include "darr_perf.h"
#include "preprocess.h"
#include "sort.h"
#include "keytable.h"


#define ADD "add"
#define DELETE "delete"
#define PRINT "print"
#define PRINT_BY_TABLE "print by keys"

//#define SORT "sort"
#define Q_SORT_T "quick sort table"
#define SL_SORT_T "slow sort table"
#define Q_SORT_K "quick sort keys"
#define SL_SORT_K "slow sort keys"

# define COMPARE_SORT "compare sort"

#define FILTER "filter"
#define EXIT "exit"
#define SAVE "save"
#define MENU "menu"

int add_f(perform **arr_perform, size_t *size, size_t *real_size);
int add_f_keys(perform **arr_perform, size_t *size, key_t **keys, size_t *size_k, size_t *real_size_k);

int delete_f(perform **arr_perform, size_t *size, key_t **keys, size_t *size_k);

void print_f(perform **d_arr, key_t **keys, size_t size_k);

void print_error_message(int rc);

int filter_f(perform **d_arr, size_t size);

void comapre_sort_f(perform **arr_perform, size_t size, key_t **keys, size_t size_k);

void write_tf_f(FILE *src, perform *d_arr, size_t size);

void compare_sort_f(perform *arr_perform, size_t size, key_t *keys, size_t size_k);


void message(void);




#endif
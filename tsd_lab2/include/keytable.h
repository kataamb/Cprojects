#ifndef _KEY_TABLE_H_
#define _KEY_TABLE_H_

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "return_codes.h"
#include "perfomance.h"
#include "darr_perf.h"
#include "strings_func.h"

struct Keys
{
    char perform_name[MAX_STRING_LEN];
    size_t index; //index in original array
};

typedef struct Keys key_t;


int create_keys(key_t **keys, size_t size);

int realloc_keys(key_t **keys, size_t size, size_t new_size);

void delete_keys(key_t **keys, size_t size);

void initialize_keys(perform *darr_perform, size_t size, key_t **keys);



void output_key(key_t *key);

void output_keys(key_t **keys, size_t size);

#endif



//sort

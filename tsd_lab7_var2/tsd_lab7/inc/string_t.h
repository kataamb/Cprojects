#ifndef _STRING_T_H_
#define _STRING_T_H_


struct string_t
{
    char *word;
};

typedef struct string_t string_t;


#include <stdio.h>

#include "return_codes.h"

#include <string.h>

#include <stdlib.h>

int read_string_array(string_t *array, size_t *num, FILE *src);

int read_string_array(string_t *array, size_t *num, FILE *src);
void output_string_array(string_t *arr, size_t size);
int find_letter_words_file(string_t *array, int *num, char letter, FILE *src);

#endif
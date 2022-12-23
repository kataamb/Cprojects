#ifndef _PREPROCESS_H
#define _PREPROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "return_codes.h"
#include "perfomance.h"
#include "perfomance_methods.h"
#include "strings_func.h"
#include "darr_perf.h"
#include "keytable.h"


void swap_perf(perform* perf1, perform* perf2);
void swap_key(key_t* k1, key_t* k2);
void univ_swap(void *pt1, void *pt2, size_t size);

int add_performance(perform **darr_per, size_t *size, size_t *real_size, perform *new_perf);
int add_key(key_t **keys, size_t *size, size_t *real_size, key_t *new_key);

int delete_perform(perform **darr, size_t *size, int num);
int delete_key(key_t **keys, size_t *size, int num);

void shuffle(perform *darr, size_t size);
void shuffle_k(key_t *darr, size_t size_k);


void write_perform_tf(FILE *src, perform *perf);

#endif
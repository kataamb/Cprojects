#ifndef _DARR_PERF_H_
#define _DARR_PERF_H_

#include <stdio.h>
#include <stdlib.h>
#include "return_codes.h"
#include "perfomance.h"
#include "perfomance_methods.h"
#include "strings_func.h"

int create_perf_darray(perform **darr_perform, size_t real_size);

int realloc_perf_darray(perform **darr_perform, size_t size, size_t new_size);

void delete_perf_darray(perform **darr_perform, size_t size);

int read_darr_perf_tf(FILE *src, perform **darr_perform, size_t *real_size, size_t *size);

void output_darr_perf(perform **darr_perform, size_t size);

#endif
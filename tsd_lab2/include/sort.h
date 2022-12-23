#ifndef _SORT_H_
#define _SORT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include <sys/time.h>
#include "return_codes.h"
#include "perfomance.h"
#include "perfomance_methods.h"
#include "darr_perf.h"
#include "preprocess.h"
#include "keytable.h"

int comparator_prf(const void *prf1, const void *prf2);
//int sec_to_nanosec(int seconds);

int comparator_key(const void *k1, const void *k2);

double qsort_time_p(perform **darr_perf, size_t size, int (*comp)(const void *, const void *));
double bubble_time_p(perform **darr_perf, size_t size, int (*comp)(const void *, const void *));



double qsort_time_k(key_t **darr_perf, size_t size, int (*comp)(const void *, const void *));
double bubble_time_k(key_t **darr_perf, size_t size, int (*comp)(const void *, const void *));
#endif
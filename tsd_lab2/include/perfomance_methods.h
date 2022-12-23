#ifndef _PERF_METHODS_
#define _PERF_METHODS_
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "return_codes.h"
#include <string.h>
#include "perfomance.h"
#include "strings_func.h"




int input_perfomance_cs(perform *act);
int input_perfomance_tf(FILE *src, perform *act);


int input_range_tf(int *number1, int *number2, FILE *src);
int input_range_cs(int *number1, int *number2);
int input_int_tf(FILE *src, int *number1);


void output_performance(perform *act);





#endif

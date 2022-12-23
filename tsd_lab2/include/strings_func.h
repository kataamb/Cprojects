#ifndef _STR_H_
#define _STR_H_

#include <stdio.h>
#include <string.h>
#include "return_codes.h"

#define BUFFER_SIZE 10 //30
#define MAX_STRING_LEN 22 // 20 + \n + \0

int is_integer(char *st);
short read_line_text_file(char *str, FILE *text_file);
int read_string(char *st);

void itoa(int num, char *buff);


#endif
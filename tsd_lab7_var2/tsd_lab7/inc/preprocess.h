#ifndef _PREP_H_
#define _PREP_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

double get_ps(int beg, int end);
char* read_command(void);
void print_menu_actions();

void find_letter_file(FILE *src, char letter);
void flush_input(void);
#endif
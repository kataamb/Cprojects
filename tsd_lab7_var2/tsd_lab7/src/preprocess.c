#include "preprocess.h"

double get_ps(int beg, int end)
{
    double ps = (double)((end - beg) *1000 * 1000);
    return (double)(ps / CLOCKS_PER_SEC);
}

char* read_command(void)
{
    char *str = NULL;
    size_t size = 0; 
    int rc = getline(&str, &size, stdin); // size? - what is it?
    if (rc != -1)
    {
        str[strlen(str) - 1] = '\0'; 
        return str;
    }
    return NULL;
}

void print_menu_actions()
{
    printf("\n"
    "You are in programm to work with text file (read data) and binary tree.\n"
    " Input:\n"
    "   comp num - input number of comparsions,\n"
    "   rehash - input new hash table size and rehash,\n"
    "   out tree - output tree,\n"
    "   out bal - output tree,\n"
    "   out hash - output tree,\n"
    "   add tree - add new string,\n"
    "   add bal - add new string,\n"
    "   add hash - add new string,\n"
    "   delete tree - delete node by string,\n"
    "   delete bal - delete node by string,\n"
    "   delete hash - delete node by string,\n"
    "   find tree - find input string in tree,\n"
    "   find bal - find input string in balanced tree,\n"
    "   find hash - find input string in hash,\n"
    "   compare - compare time, memory and comparsions,\n"
    "   exit - to exit from app\n");
    //"   open - open new file and init tree,\n"
}

void flush_input(void)
{
    char c;
    while((scanf("%c", &c) == 1) && (c != '\n'))
        ;
}
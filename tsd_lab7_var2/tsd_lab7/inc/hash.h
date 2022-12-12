#ifndef _HASH_H_
#define _HASH_H_

#include "string_t.h"
//#include "menu.h"

typedef struct node_string node_str;

struct node_string
{
    void *data; //void pointer to any data
    node_str *next;
};


typedef struct hash_t
{
    node_str **array;
    int real_size;
    int size;
} hash_t;


#define OK_HASH 0

#define ERR_OWERFLOW_TABLE -5
#define ERR_ALLOCATE_MEMORY -3

#include <stdio.h>
#include <stdlib.h>
#include "string_t.h"

//int create_hash_table(int size, );

//void print_hash_table(hash_t hash_table);

//int add_hash(hash_t *hash_table, int data, int *count);
int near_prime(int num);

void print_hash_table(hash_t *hash_table);

int add_hash(hash_t *hash_table, void *data);

node_str* find_hash(hash_t *hash_table, char *string, int *comparsions);

void delete_hash(hash_t *hash_table, char *string);

int fill_hash_table(hash_t *hash_table, string_t *arr, int arr_size, int size);
void free_hash_table(hash_t *hash_table);

int near_prime(int num);

int rehash(hash_t *hash_table, int size);


#endif
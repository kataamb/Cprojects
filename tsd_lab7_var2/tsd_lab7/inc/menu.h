#ifndef _MENU_H_
#define _MENU_H_

#include <stdio.h>
#include "return_codes.h"

#include "hash.h"
#include "tree.h"
#include "tree_methods.h"

#include "string_t.h"

#include "node_methods.h"

#include "time.h"
#include "preprocess.h"



void act_output_tree(tree_t *tree);
void act_find_letter_tree(tree_t *tree, char letter, string_t *res, int *size);
void act_find_letter_array(string_t *arr, int arsize, char letter, string_t *res, int *size);
int act_open_file(FILE **src);
int act_input_string(char **string);

void act_insert_node(tree_t *tree, const char *string);
void act_delete_node(tree_t *tree, const char *string);
void act_pre_tree(tree_t *tree, void *param);
void act_post_tree(tree_t *tree, void *param);

node_tr *act_find_word(node_tr *root, char *word, int *comparsions);

void act_find_and_output_tree(tree_t *tree, char letter);

//void act_compare(char *filename, double *treeT, double *arrT);
void act_compare(char *filename, double *treeT, double *arrT, int *memT, int *memA);

/// ///
node_str *act_find_word_hash(hash_t *hash_table, int *comparsions);


void efficiency_tree(tree_t *tree, char *word, double *timeT, int *memT, int *comT);
void efficiency_hash(hash_t *hash_table, char *word, double *timeH, int *memH, int *comH);

void effic_all_tree(tree_t *tree, string_t *array, int size_arr, double *timeT, int *memT, int *comT);
void effic_all_hash(hash_t *hash_table, string_t *array, int size_arr, double *timeT, int *memT, int *comT);

#endif
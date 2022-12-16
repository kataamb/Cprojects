#ifndef _GRAPH_METHODS_H_
#define _GRAPH_METHODS_H_

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

//extern const int ARR_SIZE;

void init_graph(graph_t *graph);
void free_graph(graph_t *graph);

int input_graph_tf(FILE *src, graph_t *graph);
void output_graph(graph_t *graph);

void graph_to_dot(graph_t *graph);

#endif
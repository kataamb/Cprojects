#ifndef _GRAPH_STRUCT_H_
#define _GRAPH_STRUCT_H_

//#include "graph_h.h"

//const int ARR_SIZE = 1000;
#define ARR_SIZE 1000
//const int ARR_SIZE = 1000;
//extern const int ARR_SIZE;

typedef struct node node_t;

struct node
{
    int value; //number of node
    node_t *next;
};

struct graph
{
    int size; //size of array
    node_t* array[ARR_SIZE]; //array of type node_t*
};

typedef struct graph graph_t;

#endif
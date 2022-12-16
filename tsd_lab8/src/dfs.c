#include "dfs.h"
#include <stdio.h>

#define ARR_SIZE 1000

int visited[ARR_SIZE];

void dfs(graph_t *graph, int v)
{
    if (!visited[v])
    {
        visited[v] = 1;
        node_t *cur = graph->array[v];
        while (cur)
        {
            if (!visited[ cur->value ])
            {
                dfs(graph, cur->value);
            }
            cur = cur->next;
        }
        //for i in range(len(mas[v])):
            //if (not(vis[ mas[v][i] ])):
                //dfs(mas[v][i])
    }
}


void find_components(graph_t *graph, int *components, double *picosec)
{
    *components = 0;
    //1. init visited with 0
    for (int i = 0; i < ARR_SIZE; i++)
    {
        visited[i] = 0;
    }
    //2. count components
    int time1 = clock();
    for (int i = 0; i < graph->size; i++)
    {
        if (!visited[i] && graph->array[i])
        {
            /*
            printf("Not visited: %d\n", i);
            for (int i = 0; i < 20; i++)
            {
                printf("%d ", visited[i]);
            }
            printf("\n");
            */

            (*components)++;
            dfs(graph, graph->array[i]->value);
        }
    }
    int time2 = clock();

    (*picosec) = ((time2 - time1) * 1000 * 1000 /  CLOCKS_PER_SEC);
}
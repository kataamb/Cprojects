#include "graph_methods.h"



void init_graph(graph_t *graph)
{
    graph->size = ARR_SIZE;
    for (int i = 0; i < graph->size; i++)
    {
        graph->array[i] = NULL;
    }
}

void free_graph(graph_t *graph)
{
    for (int i = 0; i < graph->size; i++)
    {
        node_t *cur = graph->array[i];
        while (cur)
        {
            node_t *next = cur->next;
            free(cur);
            cur = next;
        }
    }
}

int find_vertex(graph_t *graph, int v, int u)
{
    int found = 0;
    node_t *cur = graph->array[v];
    while (cur && found == 0)
    {
        if (cur->value == u)
        {
            found = 1;
        }
        cur = cur->next;
    }
    return found;
}

void insert_vertex(graph_t *graph, int v, int u)
{
    node_t *new_node = calloc(1, sizeof(node_t));
    new_node->value = u;
    new_node->next = NULL;

    if (graph->array[v] == NULL)
    {
        graph->array[v] = new_node;
    }
    else
    {
        node_t *cur = graph->array[v];
        node_t *prev = graph->array[v];

        while (cur)
        {
            prev = cur;
            cur = cur->next;
        }
        prev->next = new_node;
    }
}

int input_graph_tf(FILE *src, graph_t *graph)
{
    int rc = 0; //OK
    rewind(src);
    //int num = 0;
    
    while (!feof(src) && rc == 0)//OK
    {
        //printf("Here\n");
        int u, v;
        rc = fscanf(src, "%d%d", &v, &u);
        //printf("%d %d\n", v, u);

        if (rc == 2)
        {
            rc = 0;//OK
            if (v < 1000 && v > 0 && u < 1000 && u > 0)
            {
                //printf("Here\n");
                int found = find_vertex(graph, u, v); //whether it's already inserted
                if (!found)
                {
                    insert_vertex(graph, u, v);
                } 
                insert_vertex(graph, v, u);

            }
            else
            {
                rc = -3; //Incrorrect values
            }
            
        }
        else
        {
            rc = -2; //READ_ERROR;
        }
    }
    return rc;
}

void output_graph(graph_t *graph)
{
    //graph_t tgraph;
    //init_graph(&tgraph);



    for (int i = 0; i < graph->size; i++)
    {
        node_t *cur = graph->array[i];
        if (cur)
        {
            printf("%d: ", i);
            while (cur)
            {
                printf("%d -> ", cur->value);
                cur = cur->next;
            }
            printf("\n");
        }
        
    }
}




void graph_to_dot(graph_t *graph)
{
    FILE *file = fopen("graph_out.gv", "w");
    if (file)
    {
        fprintf(file, "graph G {\n");
        //fprintf(file, "node [shape = box];\n");
        
        for (int i = 0; i < graph->size; i++)
        {
            node_t *cur = graph->array[i];
            if (cur)
            {
                while (cur)
                {
                    if (i < cur->value)
                    {
                        fprintf(file, "\"%d\" -- \"%d\";\n", i, cur->value);
                    }
                    cur = cur->next;
                }
            }
        }
        
        fprintf(file, "}");
        fclose(file);
    }

    system ("/home/katamba/'Рабочий стол'/github_cprojects/git_cproj_try/Cprojects/tsd_lab8/transform_to_image.sh");
    system ("xdg-open graph_out.png &");
}

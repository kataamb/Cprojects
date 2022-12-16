#include <stdio.h>
#include "graph.h"
#include "graph_methods.h"
#include "dfs.h"
#include <string.h>

int act_input_string(char **string);
void print_menu_actions();
char* read_command(void);

int main()
{
    int rc = 0, rcf = 0, rcg = -4;//not created
    graph_t graph;

    init_graph(&graph);
    printf("Input filename:\n");

    char *filename = NULL;
    FILE *src = NULL;
    rcf = act_input_string(&filename);
    if (rcf == 0)
    {
        src = fopen(filename, "r");
    }    

    if (src)
    {
        rcg = input_graph_tf(src, &graph);
        fclose(src);
        src = NULL;

        if (rcg == 0)
        {
            printf("Sucessfully read\n");
        }
        else
        {
            printf("Incorrect data in file\n");
        }
    }
    else
    {
        rcg = -1;
    }

    if (rcg == 0)
    {
        print_menu_actions();
        char *command = read_command();

        while (strcmp(command, "exit") != 0)
        {
        // OUT OPTIONS
        if (strcmp(command, "out") == 0)
        {
            if (rcg == 0)
            {
                graph_to_dot(&graph);
            }
            
            else
            {
                printf("No graph, please open file using command\n");
            }
            //flush_input();            
        }

        else if (strcmp(command, "con") == 0)
        {
            if (rcg == 0)
            {
                int components = 0;
                double ps = 0;
                find_components(&graph, &components, &ps);
                printf("Components in graph: %d\n", components);
                if (components == 1)
                {
                    printf("Graph is connected\n");
                }
                else if (components == 0)
                {
                    printf("No graph\n");
                }
                else
                {
                    printf("Graph is NOT connected\n");
                }
            }
        }

        else if (strcmp(command, "tam") == 0)
        {
            if (rcg == 0)
            {
                int components = 0;
                double ps = 0;
                int mem = 0;
                find_components(&graph, &components, &ps);
                mem = (int)sizeof(graph);
                printf("Components in graph: %d\n", components);
                if (components == 1)
                {
                    printf("Graph is connected\n");
                }
                else if (components == 0)
                {
                    printf("No graph\n");
                }
                else
                {
                    printf("Graph is NOT connected\n");
                }
                printf("Time: %lf ps\n", ps);
                printf("Memory: %d\n", mem);
            }
        
            else
            {
                printf("No graph, please open file using command\n");
            }
        }
      
        else
        {
            rc = -100;
            if(! ((int)command[0] < 99))
            {
                //printf("UNKNOWN COMMAND\n");
            }
            
        }
        
        free(command);
        print_menu_actions();
        command = read_command();
        
    }  
    free(command); 
    free_graph(&graph);
    }


    return rc;
}

int act_input_string(char **string)
{
    int rc = 0;
    size_t buf = 0;
    int len = 0;

    //printf("Input string:\n");
    int read = getline(string, &buf, stdin);
    if (read != -1)
    {
        len = strlen(*string);
        (*string)[len - 1] = '\0';
    }
    else
    {
        printf("READ ERROR\n");
        rc = -3;
    }

    return rc;
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
    "You are in programm to work with text file (read data) and not oriented graph.\n"
    " Input:\n"
    
    "   out - find input string in balanced tree,\n"
    "   con - checks whether it's connected,\n"
    "   tam - time and memory,\n"
    "   exit - to exit from app\n");
    //"   open - open new file and init tree,\n"
}

/*
    compare time and memory
*/
void act_tam(graph_t *graph)
{

}
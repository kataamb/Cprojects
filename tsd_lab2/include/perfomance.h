#ifndef _PERFOMANCE_H
#define _PERFOMANCE_H

#define STRING 21

typedef struct
{
    char theatre[STRING];
    char perform_name[STRING];
    char director[STRING];

    int minprice;
    int maxprice;

   
    char type[STRING]; //elders, musical, kids
    
    union 
    {
        struct
        {
            char genre[STRING];
        }adults;

        struct
        {
            char genre[STRING];
            int age;
            int time;
            
        }kids;

        struct
        {
            char composer[STRING];
            char country[STRING];
            int min_age;
            int time;
        }musical;
        
        
    }variable_type;


}perform;

#endif
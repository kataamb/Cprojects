#include "perfomance_methods.h"



/*
    initialize fields of structure perform
*/
int input_perfomance_tf(FILE *src, perform *act)
{
    char buff[MAX_STRING_LEN];
    int rc = OK;

    if ((rc = read_line_text_file(buff, src)) != OK)
    {
        return rc;
    }

    strcpy(act->theatre, buff);

    if ((rc = read_line_text_file(buff, src)) != OK)
    {
        return rc;
    }

    strcpy(act->perform_name, buff);

    if ((rc = read_line_text_file(buff, src)) != OK)
    {
        return rc;
    }

    strcpy(act->director, buff);

    if ((rc = input_range_tf(&(act->minprice), &(act->maxprice), src)) != OK) //!
    {
        //debug
        printf("HERE\n");
        printf("%s\n", buff);
        printf("%s\n", act->theatre);
        printf("%s\n", act->perform_name);
        printf("%s\n", act->director);
        return rc;
    }

    if ((rc = read_line_text_file(buff, src)) != OK)
    {
        return rc;
    }


    strcpy(act->type, buff);
    ///continue with variable fields

    if (strcmp(act->type, ADULTS) == 0)
    {
        if ((rc = read_line_text_file(buff, src)) == OK)
        {
            if ((strcmp(buff, PLAY)  == 0) || \
                (strcmp(buff, COMEDY) == 0) || \
                (strcmp(buff, DRAMA) == 0))
            {
                strcpy(act->variable_type.adults.genre, buff);
            }
            else
            {
                return INCORRECT_GENRE_FIELD;
            }
        }
        else
        {
            return rc;
        }
    }
    else if (strcmp(act->type, KIDS) == 0)
    {
        if ((rc = read_line_text_file(buff, src)) == OK)
        {
            if ((strcmp(buff, PLAY)  == 0) || \
                (strcmp(buff, FAIRYTALE) == 0))
            {
                strcpy(act->variable_type.kids.genre, buff);
            }
            else
            {
                return INCORRECT_GENRE_FIELD;
            }
        }
        else
        {
            return rc;
        }

        if ((rc = input_int_tf(src, &(act->variable_type.kids.age))) != OK)
        {
            return NAN_INTEGER_FIELD;
        }
        if ((rc = input_int_tf(src, &(act->variable_type.kids.time))) != OK)
        {
            return NAN_INTEGER_FIELD;
        }

    }
    else if (strcmp(act->type, MUSICLE) == 0)
    {
        if ((rc = read_line_text_file(act->variable_type.musical.composer, src)) != OK)
        {
            return rc;
        }

        if ((rc = read_line_text_file(act->variable_type.musical.country, src)) != OK)
        {
            return rc;
        }

        if ((rc = input_int_tf(src, &(act->variable_type.musical.min_age))) != OK)
        {
            return NAN_INTEGER_FIELD;
        }

        if ((rc = input_int_tf(src, &(act->variable_type.musical.time))) != OK)
        {
            return NAN_INTEGER_FIELD;
        }

    }
    else
    {
        return INCORRECT_TYPE;
    }

    return rc;
}

/*
    read perfomance from console

    initialize fields of structure perform
*/
int input_perfomance_cs(perform *act)
{
    char buff[MAX_STRING_LEN];
    int rc = OK;

    printf("Theatre:\n");
    while ((rc = read_string(buff)) != OK)
    {
        printf("Incorrect name: it must be <= 20 symbols.\nTheatre:\n");
    }
    strcpy(act->theatre, buff);
    
    printf("Performance:\n");
    while ((rc = read_string(buff)) != OK)
    {
        //return rc;
        printf("Incorrect name: it must be <= 20 symbols.\nPerformance:\n");
    }
    strcpy(act->perform_name, buff);

    printf("Director:\n");
    while ((rc = read_string(buff)) != OK)
    {
        printf("Incorrect name: it must be <= 20 symbols.\nDirector:\n");
        //return rc;
    }
    strcpy(act->director, buff);

    printf("Price range:\n");
    while ((rc = input_range_cs(&(act->minprice), &(act->maxprice))) != OK) 
    {
        printf("Incorrect range: both numbers must be natural, first number <= second number,\n"
        "separated by probel.\nPrice range:\n");
        //return rc;
    }

    printf("Type:\n");
    while ((rc = read_string(buff)) != OK || \
        !(strcmp(act->type, ADULTS) != OK && strcmp(act->type, KIDS) != OK && strcmp(act->type, MUSICLE) != OK))
    {
        //return rc;
        printf("Incorrect name: it must be 'adults', 'kids' or 'musical'.\nType:\n");
    }
    strcpy(act->type, buff);
    ///continue with variable fields

    if (strcmp(act->type, ADULTS) == OK)
    {
        printf("Genre adults: \n");
        while ((rc = read_string(buff)) != OK)
        {
           printf("Incorrect name: it must be <= 20 symbols.\nGenre adults:\n");
        }
        while (!((strcmp(buff, PLAY)  == 0) || \
                (strcmp(buff, COMEDY) == 0) || \
                (strcmp(buff, DRAMA) == 0)))
        {
            //return INCORRECT_GENRE_FIELD;
            printf("Incorrect name: it must be 'play', 'comedy' or 'drama'\nGenre adults:\n");
                
        }
        strcpy(act->variable_type.adults.genre, buff);
    }
    else if (strcmp(act->type, KIDS) == OK)
    {
        printf("Genre kids:\n");
        while ((rc = read_string(buff)) != OK)
        {
           printf("Incorrect name: it must be <= 20 symbols.\nGenre kids:\n");
        }
        while (!((strcmp(buff, PLAY)  == 0) || \
                (strcmp(buff, FAIRYTALE) == 0)))
        {
            //return INCORRECT_GENRE_FIELD;
            printf("Incorrect name: it must be 'play', 'fairytale'\nGenre kids:\n");
                
        }
        strcpy(act->variable_type.adults.genre, buff);
        

        printf("Kid's age: \n");
        while ((rc = input_int_tf(stdin, &(act->variable_type.kids.age))) != OK)
        {
            printf("Incorrect value: it must be natural number\nKid's age:\n");
            //return NAN_INTEGER_FIELD;
        }
        printf("Kid's time: \n");
        while ((rc = input_int_tf(stdin, &(act->variable_type.kids.time))) != OK)
        {
            printf("Incorrect value: it must be natural number\nKid's time:\n");
            //return NAN_INTEGER_FIELD;
        }

    }
    else if (strcmp(act->type, MUSICLE) == OK)
    {
        printf("Composer:\n");
        while ((rc = read_string(act->variable_type.musical.composer)) != OK)
        {
            printf("Incorrect name: it must be <= 20 symbols.\nComposer:\n");
            //return rc;
        }

        printf("Country:\n");
        while ((rc = read_string(act->variable_type.musical.country)) != OK)
        {
            printf("Incorrect name: it must be <= 20 symbols.\nCountry:\n");
            //return rc;
        }

        printf("Minimal age:\n");
        while ((rc = input_int_tf(stdin, &(act->variable_type.musical.min_age))) != OK)
        {
            printf("Incorrect value: it must be natural number\nMinimal age:\n");
            //return NAN_INTEGER_FIELD;
        }

        printf("Time:\n");
        while ((rc = input_int_tf(stdin, &(act->variable_type.musical.time))) != OK)
        {
            printf("Incorrect value: it must be natural number\nTime:\n");
            //return NAN_INTEGER_FIELD;
        }

    }
    else
    {
        return INCORRECT_TYPE;
    }

    //
    return rc;
}



/*
    input integer from console 
*/
int input_int_tf(FILE *src, int *number1)
{
    int rc = OK;
    char buff[MAX_STRING_LEN];
    rc = read_line_text_file(buff, src);
    if (rc == OK)
    {
        if (is_integer(buff))
        {
            *number1 = atoi(buff);
        }
        else
        {
             rc = NAN_INTEGER_FIELD;
        }
    }
       
    return rc;
}


/*
   input two integers from one string (console)
*/
int input_range_tf(int *number1, int *number2, FILE *src)
{
    int rc = OK;
    char  buff[MAX_STRING_LEN];
    char *num1 = NULL, *num2 = NULL; 
    rc = read_line_text_file(buff, src);
    if (rc == OK)
    {
        num1 = strtok(buff, " \n");
        num2 = strtok(NULL, " \n");

        if (num1 && num2 && is_integer(num1) && is_integer(num2)) //num1 && num2 &&
        {
            *number1 = atoi(num1);
            *number2 = atoi(num2);
            if (*number1 > *number2)
            {
                rc = INCORRECT_PRICE_RANGE;
            }
        }
        else
        {
            rc = NAN_PRICE_RANGE;
        }

    }
    return rc;
}


/*
   input two integers from one string (console)
*/
int input_range_cs(int *number1, int *number2)
{
    int rc = OK;
    char  buff[MAX_STRING_LEN];
    char *num1 = NULL, *num2 = NULL; 
    rc = read_string(buff);
    if (rc == OK)
    {
        num1 = strtok(buff, " \n");
        num2 = strtok(NULL, " \n");

        if (num1 && num2 && is_integer(num1) && is_integer(num2)) //num1 && num2 &&
        {
            *number1 = atoi(num1);
            *number2 = atoi(num2);
            if (*number1 > *number2)
            {
                rc = INCORRECT_PRICE_RANGE;
            }
        }
        else
        {
            rc = NAN_PRICE_RANGE;
        }

    }
    return rc;
}



/*
    output performance
*/
void output_performance(perform *act)
{
    char buf1[MAX_STRING_LEN], buf2[MAX_STRING_LEN];
    printf("%-20s|", act->theatre); //"|%-30s|"
    printf("%-20s|", act->perform_name);
    printf("%-20s|", act->director);

    itoa(act->minprice, buf1);
    itoa(act->maxprice, buf2);
    
    printf("%-10s %-10s|", buf1, buf2);
    printf("%-20s|", act->type);

    if (strcmp(act->type, ADULTS) == 0)
    {
        //genre, is
        printf("%-20s|", act->variable_type.adults.genre);
        
        
        //age
        printf("%-20s|", "");
        //time
        printf("%-20s|", "");
        //comp
        printf("%-20s|", "");
        //country
        printf("%-20s|", "");
        //min age
        printf("%-20s|", "");
        
    }
    else if (strcmp(act->type, KIDS) == 0)
    {
        //genre, is
        printf("%-20s|", act->variable_type.kids.genre);
        // age, is

        itoa(act->variable_type.kids.age, buf1);

        printf("%-20s|", buf1); //!!!!

        //time, is
        itoa(act->variable_type.kids.time, buf1);
        printf("%-20s|", buf1);
        //comp
        printf("%-20s|", "");
        //country
        printf("%-20s|", "");
        //min age
        printf("%-20s|", "");
        
        
    }
    else if (strcmp(act->type, MUSICLE) == 0)
    {
        //genre 
        printf("%-20s|", "");
        //age
        printf("%-20s|", "");
        //time, is
        itoa(act->variable_type.musical.time, buf1);
        printf("%-20s|", buf1);
        //comp, is
        printf("%-20s|", act->variable_type.musical.composer);
        //country, is
        printf("%-20s|", act->variable_type.musical.country);
        //min age, is
        itoa(act->variable_type.musical.min_age, buf1);
        printf("%-20s|", buf1);      
    } 
    printf("\n");
}

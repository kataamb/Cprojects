#include "strings_func.h"

/*
    determines whether string is integer
*/
int is_integer(char *st)
{
    int rc = 1;
    char *pt = st;
    if (pt[0] == '+' || pt[0] == '-')
    {
        pt++;
    }
    for (;*pt != '\0' && rc == 1; pt++)
    {
        if (!(*pt >= '0' && *pt <= '9'))
        {
            rc = 0;
        }
    }
    return rc;
}

/*
    read line from text file; 
    return ERROR code if characters more 
    than STRING_MAX_SIZE - 1
*/

short read_line_text_file(char *str, FILE *text_file)
{
    //char strr[1000];
    short rc = OK;

    short rc_read = OK;

    char *fgets_rc = NULL;

    char curr_symb = ' ';

    size_t curr_str_len = 0;

    while (curr_str_len < (MAX_STRING_LEN) \
        && rc_read == OK
        && curr_symb != '\n' && (!feof(text_file)))
    {
        // "+ curr_str_len" to reduce the calculatings
        //printf("IS TRUE: %d\n", (curr_str_len + BUFFER_SIZE) < MAX_STRING_LEN);

        if ((curr_str_len + BUFFER_SIZE) < MAX_STRING_LEN) 
        {
            fgets_rc = fgets(str + curr_str_len, BUFFER_SIZE, text_file); //rewrite symbol with '\0'
            if (fgets_rc != NULL)
            {
                curr_str_len += strlen(str + curr_str_len); //count without '\0'
                //debug
                //printf("CURR SIZE %zu %s\n", curr_str_len, str);
            }
            else
            {
                rc_read = UNEXPECTED_EOF;
            }
        }
        else
        {
            //printf("Here\n");
            fgets_rc = fgets(str + curr_str_len, MAX_STRING_LEN - curr_str_len + 1, text_file);
            //debug
            
            //printf("CURRRRT SIZE %zu %s\n", curr_str_len, str);
            if (fgets_rc != NULL)
            {
                curr_str_len += MAX_STRING_LEN - curr_str_len - 1; //!!!!!
                //debug
                
                //printf("CURR SIZE %zu %s\n", curr_str_len, str);
                /*
                printf("CUR SYMB: is next line: %d\n",str[curr_str_len - 2] == '\n');
                printf("CUR SYMB: %d\n",str[curr_str_len - 2]);
                */
            }
            else
            {
                rc_read = UNEXPECTED_EOF;
            }
        }

        curr_symb = str[curr_str_len - 1];    
    }

    ///....
    //we read the string
    //now check whether it's correct (less than 256)

    if (rc_read == OK && (curr_symb == '\n'))
    {
        str[curr_str_len - 1] = '\0'; 
    }
    /*
    else if (rc_read == OK && (curr_symb == '\0'))
    {
        //str[MAX_STRING_LEN - 1] = '\0'; ////????? 
        //
        //printf("%s", str);
        //(((())))
        ///:()
        char *pt = str;
        while(*pt != '\n')
        {
            pt++;
        }
        *pt = '\0';
        //:()
    }
    */
    else if (rc_read != OK)
    {
        rc = UNEXPECTED_EOF;
    }
    else if (!(feof(text_file)))
    {
        //debug
        //////
        /*
        printf("%s\n", str);
        int j = 0;
        for (char* i = str; *i != '\n'; i++, j++)
        {
            printf("currrr: %d ind: %d \n", *i, j);
        }
        printf("END\n");
        printf("curr symb: %d\n", curr_symb);
        printf("LENGTH %zu\n", strlen(str));
        */

        rc = TOO_LONG_STRING_ERROR;
    }


    //check length after adding \0, it must be <= 20

    //printf("STRLEn: %zu\n", strlen(str));

    if (!(strlen(str) <= (MAX_STRING_LEN - 2)))
    {
        rc = TOO_LONG_STRING_ERROR;
    }
    return rc;
}

/*
    read string fixed line from console
*/
int read_string(char *st)
{
    char strr[1000];
    char cur_symb;

    int rc = OK;

    size_t i = 0;
    while ((cur_symb = getchar()) != '\n' && cur_symb != EOF ) /* && rc == OK
    EOF is in stdio.h */
    {
        if (i < MAX_STRING_LEN - 2)// - 1) //??
        {
            strr[i] = cur_symb;
            i++;
        }
        else
        {
            //printf("TOO LONG STRING\n");
            rc = TOO_LONG_STRING_ERROR; // more symbols
        }
    }
    strr[i] = '\0'; // add at the end of string
    /*
    if (!(strlen(st) <= (MAX_STRING_LEN - 2)))
    {
        rc = TOO_LONG_STRING_ERROR;
    }
    */
   /*
    if (strlen(strr) >= MAX_STRING_LEN)
    {
        rc = TOO_LONG_STRING_ERROR;
    }
    */
    if (rc == OK)
    {
        strcpy(st, strr);
    }

    return rc;
}


/*
*/
void itoa(int num, char *buff)
{
    char buff0[MAX_STRING_LEN];
    int i = 0;
    while (num > 0)
    {
        buff0[i] = '0' + num % 10;
        num /= 10;   
        i++;
    }
    buff0[i] = '\0';

    //printf("BUFFF %s\n", buff0);
    i--;
    size_t j = 0;
    for (; i >= 0; i--, j++)
    {
        buff[j] = buff0[i];
    }
    buff[j] = '\0';
}

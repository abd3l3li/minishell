#include "minishell.h"

extern int status;

void p_err(char *str, int n)
{
    status = n;
    printf("%s\n", str);
    //need to handle readline re-calling
}

int spaces(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if ((s[i] != ' ' && s[i] != '\t') && (s[i] != 34 && s[i] != 39))
            return (0);
        i++;
    }
    i = 0;
   /*
    while (s[i])
    {
        if (!(check_q(s)) && (s[i] == 34 || s[i] == 39))
            {
                printf(">\n");
                return (1);
            }
        i++;
    }*/
    return (1);
}

int count_q(char *s, char c)
{
    int n;
    int i;

    n = 0;
    i = 0;
    while(s[i])
    {
        if (s[i] == c)
            n++;
        i++;
    }
    return (n);
}

int check_q(char *str)
{
    int count_d;
    int count_s;
    int i;
    int s;
    int d;

    count_d = 0;
    count_s = 0;
    d = 0;
    s = 0;
    i = 0;
    while(str[i])
    {
        if (str[i] == 34 && !d)
        {
            count_d = count_q(str, 34);
            s = 1;
        }
        else if (str[i] == 39 && !s)
        {
            count_s = count_q(str, 39);
            d = 1;
        }
        i++;
    }
    if ((count_d % 2 != 0 || count_s % 2 != 0))
        return (1);
    else
        return (0);
}

int double_p(char *s)
{
    int i;

    i = 0;
    while(s[i])
    {
        if (s[i] == '|' && s[i + 1] == '|')
            return (1);
        i++;
    }
    return (0);
}
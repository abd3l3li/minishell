#include "minishell.h"

int ft_check(char *s)
{
    int last;
    int yes;
    int i;

    last = ft_strlen(s);
    yes = 0;
    i = 0;
    while (s[i] == 32)
        i++;
    if (check_q(s + i))
    {
        yes = 1;
        printf("quote>\n");
    }
    if ((*(s + i) == '|' || s[last - 1] == '|') || double_p(s + i))
    {
        yes = 1;
        p_err("minishell: syntax error near unexpected token `|'", 2);
    }
    return (yes);
}

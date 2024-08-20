#include "minishell.h"

int ft_check(char *s)
{
    int last;
    int yes;

    last = ft_strlen(s);
    yes = 0;
    if (check_q(s))
    {
        yes = 1;
        free(s);
        printf("quote>\n");
    }
    if (s[0] == '|' || s[last - 1] == '|')
    {
        yes = 1;
        free(s);
        p_err("minishell: syntax error near unexpected token `|'", 2);
    }
    if (double_p(s))
    {
        yes = 1;
        free(s);
        p_err("minishell: syntax error near unexpected token `||'", 2);
    }
    return (yes);
}

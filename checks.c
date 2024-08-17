#include "minishell.h"

void ft_check(char *s)
{
    int last;

    last = ft_strlen(s);
    if (check_q(s))
    {
        free(s);
        printf(">\n");
    }
    if (s[0] == '|' || s[last - 1] == '|')
    {
        free(s);
        p_err("minishell: syntax error near unexpected token `|'", 2);
    }
    if (double_p(s))
    {
        free(s);
        p_err("minishell: syntax error near unexpected token `||'", 2);
    }

}

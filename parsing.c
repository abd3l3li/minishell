#include "minishell.h"

extern int status;

int ft_pars(t_ms *cmd)
{
    t_list *tmp;

    tmp = cmd->node;
    while (tmp)
    {
        if ((ft_strnotcmp(tmp->content, ">>", 2) || ft_strnotcmp(tmp->content, "<<", 2)) && (tmp->next == NULL))
        {
            status = 2;
            printf("bash: syntax error near unexpected token\n");
            return (1);
        }
        else if (ft_strnotcmp(tmp->content, "//", 2) && tmp->next == NULL)
        {
            status = 126;
            printf("bash: Is a directory\n");
            return (1);
        }
        else if (ft_strnotcmp(tmp->content, "\\", 2) && tmp->next == NULL)
        {
            status = 127;
            printf("bash: command not found\n");
            return (1);
        }
        tmp = tmp->next;
    }
    return (0);
}

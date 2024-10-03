#include "minishell.h"

void free_list(t_list *node)
{
    t_list *temp;
    while (node)
    {
        temp = node;
        node = node->next;
        if (temp->content)
            ft_free(temp->content);
        ft_free(temp);
    }
}

void free_cmd(t_ms *cmd)
{
    if (!cmd)
        return;
    if (cmd->node)
        free_list(cmd->node);
    ft_free(cmd);
    cmd->node = NULL;
}
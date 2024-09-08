#include "minishell.h"

void free_list(t_list *node)
{
    t_list *temp;
    while (node)
    {
        temp = node;
        node = node->next;
        if (temp->content)
            free(temp->content);
        free(temp);
    }
}

/*void free_pcmd(char **pcmd)
{
    int i = 0;
    if (!pcmd)
        return;
    while (pcmd[i])
    {
        free(pcmd[i]);
        i++;
    }
    free(pcmd);
}*/


void free_cmd(t_ms *cmd)
{
    if (!cmd)
        return;
    if (cmd->node)
        free_list(cmd->node);
    free(cmd);
    cmd->node = NULL;
}
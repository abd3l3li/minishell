#include "minishell.h"

extern int status;

static void to_be_continued(t_ms *command, t_env *env_list)
{
    if (!ft_strncmp(env_list->name, command->name, ft_strlen(command->name)))
    {
        command->value = env_list->value;
        if (command->tmp->content)
            free(command->tmp->content);
        command->tmp->content = ft_strdup(command->value);
    }
    else if (command->name[0] == '0')
    {
        if (command->tmp->content)
            free(command->tmp->content);
        command->tmp->content = ft_strdup("bash");
    }
    else if (strncmp(command->name, "?", 1) == 0)
    {
        if (command->tmp->content)
            free(command->tmp->content);
        command->tmp->content = ft_strdup(ft_itoa(status));
    }
    else if (command->value == NULL)
    {
        if (command->tmp->content)
            free(command->tmp->content);
        command->tmp->content = ft_strdup("");
    }
}

void    expand_env(t_ms *command, t_env *env_list)
{
    command->tmp = command->node;
    while (command->tmp)
    {
        if (command->tmp->type == Env)
        {
            command->name = ft_strdup(command->tmp->content + 1);
            command->value = NULL;
            while (env_list)
            {
                to_be_continued(command, env_list);
                env_list = env_list->next;
            }
        free(command->name);
        }
        else if ((command->tmp->content[0] == '>' || (command->tmp->content[0] == '<' && command->tmp->content[1] == '\0'))
                && (command->tmp->next && command->tmp->next->content[0] == '$'))
                p_err("bash: ambiguous redirect", 1);
        command->tmp = command->tmp->next;
    }
}

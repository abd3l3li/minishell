#include "minishell.h"

extern int status;

void    expand_env(t_ms *command, t_env *env_list)
{
    t_list  *tmp;

    tmp = command->node;
    while (tmp)
    {
        if (tmp->type == Env)
        {
            char *name;
            char *value;

            name = ft_strdup(tmp->content + 1);
            value = NULL;
            while (env_list)
            {
                if ((ft_strncmp(env_list->name, name, ft_strlen(name)) == 0) && (env_list->name[ft_strlen(name)] == '='))
                {
                    value = env_list->value;
                    if (tmp->content)
                        free(tmp->content);
                    tmp->content = ft_strdup(value);
                    break;
                }
                else if (name[0] == '0')
                {
                    if (tmp->content)
                        free(tmp->content);
                    tmp->content = ft_strdup("bash");
                    break;
                }
                else if (strncmp(name, "?", 1) == 0)
                {
                    if (tmp->content)
                        free(tmp->content);
                    tmp->content = ft_strdup(ft_itoa(status));
                    break;
                }
                else if (value == NULL)
                {
                    if (tmp->content)
                        free(tmp->content);
                    tmp->content = ft_strdup("");
                }
                env_list = env_list->next;
            }
        free(name);
        }
        else if ((tmp->content[0] == '>' || (tmp->content[0] == '<' && tmp->content[1] == '\0'))
                && (tmp->next && tmp->next->content[0] == '$'))
                p_err("bash: ambiguous redirect", 1);
        tmp = tmp->next;
    }
}
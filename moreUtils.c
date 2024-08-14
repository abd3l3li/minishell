#include "minishell.h"

int     alphanum(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
            || (c >= '0' && c <= '9'));
}

void    expand_env(t_ms *command, t_env *env_list, int status)
{
    t_list  *tmp;

    tmp = command->node;
    while (tmp)
    {
        if (tmp->type == E)
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
        tmp = tmp->next;
    }
}

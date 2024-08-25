#include "minishell.h"

extern int status;

int     alphanum(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
            || (c >= '0' && c <= '9'));
}

void    expand_env(t_ms *command, t_env *env_list)
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
        else if ((tmp->content[0] == '>' || (tmp->content[0] == '<' && tmp->content[1] == '\0'))
                && (tmp->next && tmp->next->content[0] == '$'))
                p_err("bash: ambiguous redirect", 1);
        tmp = tmp->next;
    }
}

char    *remove_qoute(char *str)
{
    int i;
    int j;
    int len;
    char *res;

	i = 0;
	j = i;
	len = j;
    while (str[i])
    {
        if (str[i] != '\'' && str[i] != '\"')
            len++;
        i++;
    }
    res = malloc (sizeof(char) * (len + 1));
    i = 0;
    while (str[i])
    {
        if (str[i] != '\'' && str[i] != '\"')
            res[j++] = str[i];
        i++;
    }
	res[j] = 0;
    return (res);
}

void    ft_skip_q(t_ms *cmd)
{
    t_list *tmp;
    char *newstr;
    char *temp;

    tmp = cmd->node;
    while (tmp)
    {
        if(ft_strchr(tmp->content, '\'') || ft_strchr(tmp->content, '\"'))
        {
            newstr = remove_qoute(tmp->content);
            temp = tmp->content;
            tmp->content = newstr;
            free(temp);
        }
        tmp = tmp->next;
    }
}

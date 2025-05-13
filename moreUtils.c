#include "minishell.h"

int alphanum(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
            || (c >= '0' && c <= '9'));
}

char    *remove_qoute(char *str)
{
    int i;
    int j;
    int len;
    int flag;
    char *res;

	i = 0;
	j = 0;
	len = 0;
    flag = 0;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            if (flag == 0)
                flag = str[i];
            else if (flag == str[i])
                flag = 0;
            else
                len++;
        }
        else
            len++;
        i++;
    }
    res = malloc (sizeof(char) * (len + 1));
    i = 0;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            if (flag == 0)
                flag = str[i];
            else if (flag == str[i])
                flag = 0;
            else
                res[j++] = str[i];
        }
        else
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

void    ft_merge(t_ms *cmd)
{
    t_list *tmp;
    t_list *temp;
    t_list  *prev;
    char    *newstr;

    tmp = cmd->node;
    prev = NULL;
    while(tmp)
    {
        if (tmp->type == Env || tmp->type == Env_word)
        {
            if (tmp->next && tmp->next->type != Pipe && tmp->next->type != Rediracion_In && tmp->next->type != Rediracion_Out && tmp->next->type != Here_doc)
            {
                newstr = ft_strjoin(tmp->content, tmp->next->content);
                free(tmp->content);
                tmp->content = newstr;
                free(tmp->next->content);
                temp = tmp->next;
                tmp->next = tmp->next->next;
                free(temp);
                continue;
            }
            else if (prev && prev->type != Pipe && prev->type != Rediracion_In && prev->type != Rediracion_Out && prev->type != Here_doc)
            {
                newstr = ft_strjoin(prev->content, tmp->content);
                free(prev->content);
                prev->content = newstr; //do you need Env flag in this case
                free(tmp->content);
                prev->next = tmp->next;
                free(tmp);
                tmp = prev;
                continue;
            }
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

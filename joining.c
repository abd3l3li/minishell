#include "minishell.h"

void	ft_strcpy(char *dst, const char *src)
{
	while (*src)	
		*dst++ = *src++;
	*dst = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char *join;

	if (!s1 || !s2)
		return (NULL);
	join = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcpy(join + ft_strlen(s1), s2);
	return (join);
}

void ft_prev(t_list **tmp, t_list *prev)
{
    char *newstr = ft_strjoin(prev->content, (*tmp)->content);
    ft_free(prev->content);
    prev->content = newstr;
    ft_free((*tmp)->content);
    prev->next = (*tmp)->next;
    ft_free(*tmp);
    *tmp = prev;  // Update the caller's tmp to point to prev
}

void    ft_next(t_list *tmp)
{
    char    *newstr;
    t_list *temp;

    newstr = ft_strjoin(tmp->content, tmp->next->content);
    ft_free(tmp->content);
    tmp->content = newstr;
    ft_free(tmp->next->content);
    temp = tmp->next;
    tmp->next = tmp->next->next;
    ft_free(temp);
}

void    ft_merge(t_ms *cmd)
{
    t_list *tmp;
    t_list  *prev;

    tmp = cmd->node;
    prev = NULL;
    while(tmp)
    {
        if (tmp->type == Env || tmp->type == Env_word)
        {
            if (tmp->next && tmp->next->type != Pipe && tmp->next->type != Rediracion_In && tmp->next->type != Rediracion_Out && tmp->next->type != Here_doc)
            {
                ft_next(tmp);
                continue;
            }
            else if (prev && prev->type != Pipe && prev->type != Rediracion_In && prev->type != Rediracion_Out && prev->type != Here_doc)
            {
                ft_prev(&tmp, prev);
                continue;
            }
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joining.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:45:35 by abel-baz          #+#    #+#             */
/*   Updated: 2024/10/13 17:05:22 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strcpy(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	join = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcpy(join + ft_strlen(s1), s2);
	return (join);
}

void	ft_prev(t_list **tmp, t_list *prev)
{
	char	*newstr;

	newstr = ft_strjoin(prev->content, (*tmp)->content);
	ft_free(prev->content);
	prev->content = newstr;
	ft_free((*tmp)->content);
	prev->next = (*tmp)->next;
	ft_free(*tmp);
	*tmp = prev;
}

void	ft_next(t_list *tmp)
{
	char	*newstr;
	t_list	*temp;

	newstr = ft_strjoin(tmp->content, tmp->next->content);
	ft_free(tmp->content);
	tmp->content = newstr;
	ft_free(tmp->next->content);
	temp = tmp->next;
	tmp->next = tmp->next->next;
	ft_free(temp);
}

void	ft_merge(t_ms *cmd)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = cmd->node;
	prev = NULL;
	while (tmp)
	{
		if (tmp->type == ENV || tmp->type == ENV_WORD || tmp->type == WORD)
		{
			if (tmp->next && tmp->next->type != PIPE
				&& tmp->next->type != REDIRACTION_IN
				&& tmp->next->type != REDIRACTION_OUT
				&& tmp->next->type != REDIRACTION_OUT_APPEND
				&& tmp->next->type != HERE_DOC)
				ft_next(tmp);
			else if (prev && prev->type != PIPE && prev->type != REDIRACTION_IN
				&& prev->type != REDIRACTION_OUT
				&& prev->type != REDIRACTION_OUT_APPEND
				&& prev->type != HERE_DOC)
				ft_prev(&tmp, prev);
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

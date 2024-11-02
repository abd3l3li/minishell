/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:38:20 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/10 18:57:58 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glist	*ft_lstglast(t_glist *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

char	*trim_last_list_chars_helper(t_glist *last, int i)
{
	int		j;
	int		len;
	char	*trimmed_content;

	len = 0;
	while (last->content[len])
		len++;
	trimmed_content = ft_malloc(sizeof(char) * (len - i + 1));
	if (trimmed_content == NULL)
		return (NULL);
	j = 0;
	while (last->content[i])
		trimmed_content[j++] = last->content[i++];
	trimmed_content[j] = '\0';
	return (trimmed_content);
}

bool	found_new_line(t_glist *list)
{
	int		i;

	if (list == NULL)
		return (false);
	i = 0;
	if (list == NULL)
		return (false);
	while (list->next != NULL)
		list = list->next;
	while (list->content[i])
	{
		if (list->content[i] == '\n')
			return (true);
		i++;
	}
	return (false);
}

void	generate_line(char **line, t_glist *list)
{
	int	i;
	int	len;

	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		list = list->next;
	}
	*line = ft_malloc(sizeof(char) * (len + 1));
}

void	free_glist(t_glist *list)
{
	t_glist	*current;
	t_glist	*next;

	current = list;
	while (current)
	{
		ft_free(current->content);
		next = current->next;
		ft_free(current);
		current = next;
	}
}

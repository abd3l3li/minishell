/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:46:25 by abel-baz          #+#    #+#             */
/*   Updated: 2024/10/11 21:46:26 by abel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_listnew(char *content, int len, int type)
{
	t_list	*new;

	new = (t_list *)ft_malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = ft_substr(content, 0, len);
	if (!new->content)
		return (NULL);
	new->next = NULL;
	new->type = type;
	return (new);
}

void	ft_listadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!new)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	temp = (*lst);
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_garbage	*ft_lstnew_plus(void *content)
{
	t_garbage	*new;

	new = (t_garbage *)malloc(sizeof(t_garbage));
	if (!new)
		return (NULL);
	new->content = content;
	new->freed = 0;
	new->next = NULL;
	return (new);
}

void	ft_listadd_back_plus(t_garbage **lst, t_garbage *new)
{
	t_garbage	*temp;

	if (!new)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	temp = (*lst);
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

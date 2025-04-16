/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:45:23 by abel-baz          #+#    #+#             */
/*   Updated: 2024/10/11 21:45:26 by abel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_garbage	**get_data(void)
{
	static t_garbage	*data;

	return (&data);
}

void	ft_free(void *ptr)
{
	t_garbage	**tracker;
	t_garbage	*tmp;

	tracker = get_data();
	tmp = *tracker;
	while (tmp)
	{
		if (tmp->content == ptr)
		{
			if (tmp->freed)
				return ;
			free(tmp->content);
			tmp->freed = 1;
			return ;
		}
		tmp = tmp->next;
	}
}

void	*ft_malloc(size_t len)
{
	void		*ptr;
	t_garbage	**tracker;
	t_garbage	*new;

	tracker = get_data();
	ptr = malloc(len);
	if (!ptr)
		return (NULL);
	new = ft_lstnew_plus(ptr);
	if (!new)
	{
		ft_free(ptr);
		return (NULL);
	}
	ft_listadd_back_plus(tracker, new);
	return (ptr);
}

void	erase_all(void)
{
	t_garbage	**tracker;
	t_garbage	*tmp;
	t_garbage	*temp;

	tracker = get_data();
	temp = *tracker;
	while (temp)
	{
		tmp = (temp)->next;
		if (!(temp->freed))
		{
			free((temp)->content);
			temp->freed = 1;
		}
		free(temp);
		temp = tmp;
	}
	*tracker = NULL;
}

void	ft_exitt(int n)
{
	erase_all();
	exit(n);
}

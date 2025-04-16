/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:37:14 by her-rehy          #+#    #+#             */
/*   Updated: 2024/08/21 20:04:53 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_buffer_to_list(t_glist **glist, char *buffer, int num_bytes)
{
	int		i;
	t_glist	*last;
	t_glist	*new_node;

	new_node = ft_malloc(sizeof(t_glist));
	new_node->content = ft_malloc(sizeof(char) * (num_bytes + 1));
	if (new_node == NULL
		|| new_node->content == NULL)
		return ;
	new_node->next = NULL;
	i = 0;
	while (buffer[i] && i < num_bytes)
	{
		new_node->content[i] = buffer[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*glist == NULL)
		*glist = new_node;
	else
	{
		last = ft_lstglast(*glist);
		last->next = new_node;
	}
}

static void	list_from_file(int fd, t_glist **list)
{
	char	*buffer;
	int		num_bytes;

	num_bytes = 1;
	buffer = ft_malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (!found_new_line(*list) && num_bytes != 0)
	{
		if (buffer == NULL)
			return ;
		num_bytes = read(fd, buffer, BUFFER_SIZE);
		if ((*list == NULL && num_bytes == 0) || num_bytes == -1)
		{
			ft_free(buffer);
			if (num_bytes == -1)
				free_glist(*list);
			*list = NULL;
			return ;
		}
		buffer[num_bytes] = '\0';
		add_buffer_to_list(list, buffer, num_bytes);
	}
	ft_free(buffer);
}

static void	read_line_from_list(t_glist *list, char **line)
{
	int	i;
	int	j;

	if (list == NULL)
		return ;
	generate_line(line, list);
	if (*line == NULL)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				(*line)[j++] = list->content[i];
				break ;
			}
			(*line)[j++] = list->content[i++];
		}
		list = list->next;
	}
	(*line)[j] = '\0';
}

static t_glist	*trim_last_list_chars(t_glist **lst)
{
	t_glist	*last;
	t_glist	*clean_node;
	int		i;

	clean_node = ft_malloc(sizeof(t_list));
	if (lst == NULL || clean_node == NULL)
	{
		*lst = clean_node;
		return (NULL);
	}
	clean_node->next = NULL;
	last = ft_lstglast(*lst);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
		i++;
	clean_node->content = trim_last_list_chars_helper(last, i);
	if (clean_node->content == NULL)
		return (NULL);
	free_glist(*lst);
	*lst = clean_node;
	return (clean_node);
}

char	*get_next_line(int fd)
{
	static t_glist	*list;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	list_from_file(fd, &list);
	if (list == NULL)
		return (NULL);
	read_line_from_list(list, &line);
	trim_last_list_chars(&list);
	if (line[0] == '\0')
	{
		free_glist(list);
		list = NULL;
		ft_free(line);
		return (NULL);
	}
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:09:32 by her-rehy          #+#    #+#             */
/*   Updated: 2024/09/27 15:02:08 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int list_size(t_env *list)
{
	int i = 0;
	t_env *tmp = list;
	while(tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char **list_to_array(t_env *list)
{
	int i = 0;
	t_env *tmp = list;
	int size = list_size(list);
	char **envp;
	envp = ft_malloc(sizeof(char *) * (size + 1));
	while(tmp)
	{
		envp[i] = ft_strjoin(tmp->name, "=");
		envp[i] = ft_strjoin(envp[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

int	ft_strfind(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return (1);
		i--;
	}
	return (-1);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = -1;
	while (tab[++i])
		ft_free(tab[i]);
	ft_free(tab);
	tab = NULL;
}

void	error(int i)
{
	if (i == 2)
	{
		perror("pipe");
		ft_exitt(EXIT_FAILURE);
	}
	if (i == 3)
	{
		write(2, ": No such file or directory\n", 28);
		g_status = 127;
		return;
	}
}

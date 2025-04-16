/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:09:32 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/09 14:15:35 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	list_size(t_env *list)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**list_to_array(t_env *list)
{
	int		i;
	t_env	*tmp;
	int		size;
	char	**envp;

	i = 0;
	tmp = list;
	size = list_size(list);
	envp = ft_malloc(sizeof(char *) * (size + 1));
	while (tmp)
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
}

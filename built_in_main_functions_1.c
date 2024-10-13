/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_main_functions_1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:09:54 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/13 23:31:22 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnstr(char *s1, char *s2)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s1[i])
	{
		if (s1[i] == s2[j])
		{
			start = i;
			while (s1[i] == s2[j] && s2[j])
			{
				i++;
				j++;
			}
			if (s2[j] == '\0')
				return (s1 + i - 1);
			j = 0;
			i = start;
		}
		i++;
	}
	return (NULL);
}

void	print_until_quote(char **str, int i)
{
	while (str[i] && !ft_strchr(str[i], '\'') && !ft_strchr(str[i], '\"'))
	{
		printf("%s", str[i]);
		if (str[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

int	print_argument(t_exc *vars, int i)
{
	char	*str;

	if (ft_strchr(vars->builtin_tmp, '\'') || ft_strchr(vars->builtin_tmp,
			'\"'))
		print_until_quote(vars->cmd_args, i);
	if (ft_strchr(vars->builtin_tmp, '\''))
	{
		str = ft_strchr(vars->builtin_tmp, '\'');
		printf("%s", remove_qoute(str));
		return (1);
	}
	else if (ft_strchr(vars->builtin_tmp, '\"'))
	{
		str = ft_strchr(vars->builtin_tmp, '\"');
		printf("%s", remove_qoute(str));
		return (1);
	}
	else
	{
		printf("%s", vars->cmd_args[i]);
		if (vars->cmd_args[i + 1] != NULL)
			printf(" ");
	}
	return (0);
}

int	echo(t_exc *vars)
{
	int	check;
	int	i;

	check = 0;
	i = check_option(vars->cmd_args, &check);
	while (vars->cmd_args[i])
	{
		if (print_argument(vars, i))
			break ;
		i++;
	}
	if (check == 0)
		printf("\n");
	return (g_status = 0, 0);
}

int	ft_unset(t_env **env, char *str)
{
	t_env	*tmp;
	char	**name_value;
	t_env	*to_delete;

	if (!str)
		return (0);
	name_value = ft_split(str, '=');
	if (unset_first(env, str, name_value) == 0)
		return (0);
	tmp = *env;
	while (tmp != NULL && tmp->next != NULL)
	{
		if (ft_strncmp(tmp->next->name, str, ft_strlen(name_value[0])) == 0)
		{
			to_delete = tmp->next;
			tmp->next = to_delete->next;
			ft_free(to_delete->name);
			ft_free(to_delete->value);
			ft_free(to_delete);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

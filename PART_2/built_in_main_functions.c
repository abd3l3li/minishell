/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_main_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:49:56 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/15 18:17:44 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *env)
{
	ft_print_env(env);
	return (0);
}

void	print_exported_variables(t_env *export)
{
	while (export)
	{
		if (export->value != NULL)
			printf("declare -x %s=\"%s\"\n", export->name, export->value);
		else
			printf("declare -x %s\n", export->name);
		export = export->next;
	}
}

int	ft_export(t_env *env, t_env *export, t_exc *vars)
{
	int		i;
	char	*join_args;

	join_args = NULL;
	i = 1;
	while (vars->cmd_args[i])
	{
		if (vars->cmd_args[i] && vars->cmd_args[i + 1] != NULL)
		{
			join_args = ft_strjoin(vars->cmd_args[i], " ");
			join_args = ft_strjoin(join_args, vars->cmd_args[i + 1]);
		}
		i++;
	}
	if (join_args != NULL)
		vars->cmd_args[1] = ft_strdup(join_args);
	if (vars->cmd_args[1] == NULL)
		return (print_exported_variables(export), 0);
	compare_list(vars->cmd_args[1], env);
	if (compare_list(vars->cmd_args[1], export) == 1)
		return (0);
	vars->cmd = vars->cmd_args[1];
	check_values(env, export, vars);
	return (0);
}

int	ft_exit(t_exc *vars)
{
	size_t	num;

	num = 0;
	if (!validate_exit_args(vars))
		return (0);
	if (vars->cmd_args[1] != NULL)
	{
		num = handle_numeric_argument(vars);
		ft_exitt(num);
	}
	ft_free_tab(vars->cmd_args);
	ft_free(vars);
	ft_exitt(g_status);
	return (0);
}

int	change_to_home(void)
{
	const char	*home = getenv("HOME");

	if (!home)
	{
		write(1, "bash: cd: HOME not set\n", 23);
		return (1);
	}
	chdir(home);
	return (0);
}

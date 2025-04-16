/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_main_functions_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:55:09 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/13 16:56:50 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_exc *vars, t_env *env, t_env *export)
{
	char	*new_pwd;

	if (!vars->cmd_args[1])
	{
		if (change_to_home() != 0)
			return (1);
	}
	else if (chdir(vars->cmd_args[1]) == -1)
	{
		write(1, "bash: cd: ", 9);
		write(1, vars->cmd_args[1], ft_strlen(vars->cmd_args[1]));
		write(1, ": no such file or directory\n", 28);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	update_env_var(env, "PWD", new_pwd);
	update_env_var(export, "PWD", new_pwd);
	if (vars->oldpwd)
	{
		update_env_var(export, "OLDPWD", vars->oldpwd);
		update_env_var(env, "OLDPWD", vars->oldpwd);
	}
	vars->oldpwd = new_pwd;
	free(new_pwd);
	return (0);
}

int	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	put_str_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 22:49:28 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/11 22:41:14 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_here_doc(t_list *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->type == HERE_DOC)
			count++;
		list = list->next;
	}
	if (count >= 17)
	{
		put_str_fd("bash: maximum here-document count exceeded\n", 2);
		ft_exitt(2);
	}
	return (count);
}

void	*handle_error(char **splited_cmd, int flag)
{
	if (flag == 1)
	{
		put_str_fd(splited_cmd[0], 2);
		put_str_fd(": Is a directory\n", 2);
		g_status = 126;
	}
	else if (flag == 2)
	{
		put_str_fd(splited_cmd[0], 2);
		put_str_fd(": Permission denied\n", 2);
		g_status = 126;
	}
	else if (flag == 3)
	{
		put_str_fd(splited_cmd[0], 2);
		put_str_fd(": no such file or directory\n", 2);
		g_status = 127;
	}
	ft_free_tab(splited_cmd);
	return (NULL);
}

char	*handl_path(char *cmd)
{
	t_cmd_Vars	var;
	DIR			*dir;
	int			path;

	path = 0;
	var.splited_cmd = ft_split(cmd, ' ');
	while (var.splited_cmd[path])
		path++;
	path--;
	if (access(var.splited_cmd[path], F_OK) == 0)
	{
		if (access(var.splited_cmd[path], X_OK) == 0)
		{
			dir = opendir(var.splited_cmd[path]);
			if (ft_strfind(var.splited_cmd[path], '/') == 1
				&& !var.splited_cmd[path +1] && dir && path == 0)
				return (handle_error(var.splited_cmd, 1));
			ft_free_tab(var.splited_cmd);
			return (cmd);
		}
		else
			return (handle_error(var.splited_cmd, 2));
	}
	else
		return (handle_error(var.splited_cmd, 3));
}

char	*find_path(char *cmd, char **envp)
{
	t_cmd_Vars	var;

	var.result = ft_strfind(cmd, '/');
	if (var.result == 1)
		return (handl_path(cmd));
	var.paths = getpaths(envp);
	if (!var.paths)
		return (NULL);
	var.i = 0;
	while (var.paths[var.i])
	{
		var.part_path = ft_strjoin(var.paths[var.i], "/");
		var.path = ft_strjoin(var.part_path, cmd);
		ft_free(var.part_path);
		if (access(var.path, F_OK) == 0)
		{
			return (var.path);
		}
		ft_free(var.path);
		var.i++;
	}
	var.i = -1;
	ft_free_tab(var.paths);
	return (0);
}

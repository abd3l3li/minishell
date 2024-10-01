/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:19:40 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/01 23:27:04 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp(const char *str1, const char *str2)
{

    while (*str1 && (*str1 == *str2))
	{
        str1++;
        str2++;
    }
    
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}


int check_for_built_in(t_list *list,t_env *env, t_exc *vars, t_env *export)
{
	vars->cmd_args = ft_split(list->content, ' ');
    if (ft_strcmp(vars->cmd_args[0], "echo") == 0)
        return(echo(vars));
    else if (ft_strcmp(vars->cmd_args[0], "pwd") == 0)
        return(pwd(vars));
    else if (ft_strcmp(vars->cmd_args[0], "env") == 0)
        return(ft_env(env));
    else if (ft_strcmp(vars->cmd_args[0], "export") == 0)
        return(ft_export(env, export, vars));
    else if (ft_strcmp(vars->cmd_args[0], "unset") == 0)
	{
		ft_unset(&export, vars->cmd_args[1]);
        return(ft_unset(&env, vars->cmd_args[1]));
	}
    else if (ft_strcmp(vars->cmd_args[0], "exit") == 0)
        return(ft_exit(vars));
    return (1);
}

char    **getpaths(char **envp)
{
    int        i;
    char    **paths;
    int        check;

    check = 1;
    i = 0;
    while (envp[i] != NULL)
    {
        check = ft_strncmp(envp[i], "PATH", 4);
        if (check == 0)
            break ;
        i++;
    }
    if (check != 0)
        return (NULL);
    
    paths = ft_split(envp[i], ':');
    ft_memmove(&paths[0][0], &paths[0][5], ft_strlen(paths[0]) - 5);
    return (paths);
}

int is_built_in(char *cmd)
{
	char **cmd_args;

	cmd_args = ft_split(cmd, ' ');
	if(ft_strncmp(cmd_args[0], "echo", 4) == 0)
		return (1);
	else if(ft_strncmp(cmd_args[0], "pwd", 3) == 0)
		return (1);
	else if(ft_strncmp(cmd_args[0], "env", 3) == 0)
		return (1);
	else if(ft_strncmp(cmd_args[0], "export", 6) == 0)
		return (1);
	else if(ft_strncmp(cmd_args[0], "unset", 5) == 0)
		return (1);
	else if(ft_strncmp(cmd_args[0], "exit", 4) == 0)
		return (1);
	else if(ft_strncmp(cmd_args[0], "cd", 2) == 0)
		return (1);
	return (0);
}

void	initialize_execution(t_exc *exc, t_env *env_list, t_env *export, char ***env, t_list *list, t_list **pre_last)
{
	t_env **envs;

	envs = (t_env **)malloc(sizeof(t_env *) * 2);
	envs[0] = env_list;
	envs[1] = export;
	exc->saved_stdin = dup(STDIN_FILENO);
	exc->saved_stdout = dup(STDOUT_FILENO);
	exc->redirection_check = 0;
    *env = list_to_array(env_list);
	*pre_last = list;
	if (list)
		set_status(list, *env, *pre_last);

}

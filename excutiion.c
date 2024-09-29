/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:39:55 by her-rehy          #+#    #+#             */
/*   Updated: 2024/09/29 22:23:21 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int status;

void protecting_executing(t_list *tmp, char **env, t_list *pre_last, t_ms *ms, t_exc *vars, t_env *env_list, t_env *export)
{
	if (tmp)
		set_status(tmp, env, pre_last);
	if (tmp != NULL && status == 0 && (tmp->type == Pipe || (tmp->type == Word)) && pre_last->type != Here_doc)
		last_child(tmp, env, ms->node->type, vars, env_list, export);
	if (tmp != NULL && status == 127 && vars->redirection_check == 0)
	{
		write(2, tmp->content, ft_strlen(tmp->content));
		write(2, ": command not found\n", 20);
	}
	while (wait(NULL) != -1);
}
void	execute(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;
	
	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error(3);
	}
	execve(path, cmd, envp);
}
void child_process(t_list **list, char **envp, t_exc *var, t_env **envs, t_list *pre_last_list)
{
    t_child *child;
    
    child = (t_child *)malloc(sizeof(t_child));
    child->tmp = *list;
    child->env_list = envs[0];
    child->export = envs[1];  
    setup_redirections(list, var, pre_last_list, &child->tmp, &child->fd, child->env_list, child->export, envs);
    var->pid = fork();
    if (var->pid == -1)
        error(2);
    if (var->pid == 0)
    {
        execute_child_process(list, envp, var, envs, pre_last_list, child);
    }
    ms_signal(1);
}

static void	last_child(t_list *list, char **envp, int type, t_exc *var, t_env *env_list, t_env *export)
{
	pid_t	pid;

	var->cmd_args = ft_split(list->content, ' ');
	if (handle_built_in_commands(var, env_list, export))
		return;
	pid = fork();
	if (pid == 0)
	{
		if (!check_for_built_in(list, env_list, var, export))
			exit(0);
		execute(list->content, envp);
	}

	ms_signal(1);
}


int checking(t_list *list, char **env, t_ms *ms, t_env *env_list, t_env *export, t_exc *vars)
{
	pid_t pid;
	t_list *tmp;
	t_list *pre_last;
	t_exc exc;

	initialize_execution(&exc, env_list, export, &env, list, &pre_last);
	if (!list)
		return (0); // abel-baz
	exc.i = 0;
	tmp = list;
	while (list)
	{
		pre_last = tmp;
		child_process(&list, env, vars, (t_env *[]){env_list, export}, pre_last);
		wait(NULL);
		tmp = list;
		list = list->next;
	}
	protecting_executing(tmp, env, pre_last, ms, vars, env_list, export);
	dup2(exc.saved_stdout, STDOUT_FILENO);
	dup2(exc.saved_stdin, STDIN_FILENO);
	close(exc.saved_stdout);
	close(exc.saved_stdin);
	return 0;
}

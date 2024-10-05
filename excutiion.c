/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excutiion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:39:55 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/04 20:51:06 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int status;

int count_here_doc(t_list *list)
{
	int count;

	count = 0;
	while (list)
	{
		if (list->type == Here_doc)
			count++;
		list = list->next;
	}
	return (count);
}

void protecting_executing(t_list *tmp, char **env, t_list *pre_last, t_ms *ms, t_exc *vars, t_env *env_list, t_env *export)
{
	if (tmp)
		set_status(tmp, env, pre_last);
	if (tmp != NULL && status == 0 && (tmp->type == Pipe || (tmp->type == Word || tmp->type == Env_word) ) && pre_last->type != Here_doc)
		last_child(tmp, env, ms->node->type, vars, env_list, export);
	
	if (tmp != NULL && status == 127 && vars->redirection_check == 0)
	{
		put_str_fd(tmp->content, 2);
		write(2, ": command not found\n", 20);
	}
	while(waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if(WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
	}
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
		//put_str_fd(cmd[0], 2);
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		exit(127);
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
        execute_child_process(list, envp, var, envs, pre_last_list, child);
	if((*list)->type == Here_doc || pre_last_list->type == Here_doc)
		waitpid(var->pid, &status, 0);
    // ms_signal(1);
	signal(SIGINT, SIG_IGN);
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
		signal(SIGINT, SIG_DFL);
    	signal(SIGQUIT, SIG_DFL);
		if (!check_for_built_in(list, env_list, var, export))
			exit(0);
		execute(list->content, envp);
	}
	// ms_signal(1);
	signal(SIGINT, SIG_IGN);
}


int checking(t_list *list, char **env, t_ms *ms, t_env *env_list, t_env *export, t_exc *vars)
{
	t_list *tmp;
	t_list *pre_last;
	t_exc exc;
			
	if (!list)
		return (0);
	initialize_execution(&exc, env_list, export, &env, list, &pre_last);
	exc.i = 0;
	tmp = list;
	if (count_here_doc(list) >= 17)
	{
		put_str_fd("bash: maximum here-document count exceeded\n", 2);
		exit(2);
	}
	while (list)
	{
		pre_last = tmp;
		child_process(&list, env, vars, (t_env *[]){env_list, export}, pre_last);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excutiion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:39:55 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/07 18:33:14 by her-rehy         ###   ########.fr       */
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
	if(count  >= 17)
	{
		put_str_fd("bash: syntax error: unexpected end of file\n", 2);
		exit(2);
	}
	return (count);
}

void protecting_executing(t_list *tmp, char **env, t_ms *ms, t_exc *vars)
{
	printf("status before: %d\n", status);
	if (tmp)
		set_status(tmp, env, ms->pre_last);
	printf("status after: %d\n", status);
	if (tmp != NULL && status == 0 && (tmp->type == Pipe || (tmp->type == Word || tmp->type == Env_word) ) && ms->pre_last->type != Here_doc)
		last_child( tmp, env,vars, ms);
	if (tmp != NULL && status == 127 && vars->redirection_check == 0)
	{
		put_str_fd(tmp->content, 2);
		put_str_fd(": command not found\n", 2);
		return;
	}
	printf("status after2: %d\n", status);

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
		while (cmd[++i])
			ft_free(cmd[i]);
		ft_free(cmd);
		exit(127);
	}
	execve(path, cmd, envp);
}
void child_process(t_ms *ms , char **envp,t_list *pre_last_list)
{
    t_child *child;
	
    child = (t_child *)malloc(sizeof(t_child));
    child->tmp = ms->node;
    child->env_list = ms->env_list;
    child->export = ms->export;  

    setup_redirections(ms, pre_last_list, &child->tmp, &child);
    ms->vars->pid = fork();
    if (ms->vars->pid == -1)
        error(2);
    if (ms->vars->pid == 0)
        execute_child_process(ms, envp, pre_last_list, child);

	if((*ms->node).type == Here_doc || pre_last_list->type == Here_doc)
		waitpid(ms->vars->pid, &status, 0);
	
    // ms_signal(1);
	signal(SIGINT, SIG_IGN);

}

void	last_child( t_list *list, char **envp, t_exc *var, t_ms *ms)

{
	pid_t	pid;
	var->cmd_args = ft_split(list->content, ' ');
	if (handle_built_in_commands(var, ms->env_list, ms->export))
		return;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (!check_for_built_in(list, ms->env_list, var, ms->export))
			ft_exitt(0);
		execute(list->content, envp);
	}
	signal(SIGINT, SIG_IGN);
}

int checking(char **env, t_ms *ms)
{
	t_list *tmp;
	t_list *pre_last;
	t_exc exc;
	
	if (!ms->node)
		return (0);
	initialize_execution(&exc, &env , ms);
	exc.i = 0;
	tmp = ms->node;
	count_here_doc(ms->node);
	while (ms->node)
	{
		ms->pre_last = tmp;
		child_process(ms, env, ms->pre_last);
		tmp = ms->node;
		ms->node = ms->node->next;
	}
	protecting_executing(tmp, env, ms, &exc);
	dup2(exc.saved_stdout, STDOUT_FILENO);
	dup2(exc.saved_stdin, STDIN_FILENO);
	close(exc.saved_stdout);
	close(exc.saved_stdin);
	return 0;
}

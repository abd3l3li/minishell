/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excutiion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:39:55 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/24 20:37:31 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	protecting_executing(t_list *tmp, char **env, t_ms *ms, t_exc *vars)
{
	if (tmp)
		set_status(tmp, env, ms->pre_last);
	if (tmp != NULL && g_status == 0 && (tmp->type == PIPE || (tmp->type == WORD
				|| tmp->type == ENV_WORD)) && ms->pre_last->type != HERE_DOC)
		last_child(tmp, env, vars, ms);
	close(0);
	if (tmp != NULL && g_status == 127 && vars->redirection_check == 0)
	{
		if (ft_strfind(tmp->content, '/') != 1)
		{
			put_str_fd(tmp->content, 2);
			if (compare_list("PATH", ms->env_list) == 1)
				put_str_fd(": command not found\n", 2);
			else
				put_str_fd(": no such file or directory\n", 2);
			return ;
		}
	}
	while (waitpid(-1, &g_status, 0) > 0)
	{
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
		else if (WIFSIGNALED(g_status))
			g_status = 128 + WTERMSIG(g_status);
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
		ft_exitt(g_status);
	}
	execve(path, cmd, envp);
}

void	child_process(t_ms *ms, char **envp, t_list *pre_last_list)
{
	t_child	*child;

	child = (t_child *)ft_malloc(sizeof(t_child));
	child->tmp = ms->node;
	child->env_list = ms->env_list;
	child->export = ms->export;
	setup_redirections(ms, &child);
	if (child->fd == -1)
	{
		ft_free(child);
		return ;
	}
	if (*ms->vars->fd == -1)
		return ;
	ms->vars->pid = fork();
	if (ms->vars->pid == -1)
		error(2);
	if (ms->vars->pid == 0)
		execute_child_process(ms, envp, pre_last_list, child);
	else if ((*ms->node).next && ((*ms->node).type == HERE_DOC
			|| pre_last_list->type == HERE_DOC
			|| (*ms->node).next->type == HERE_DOC))
		waitpid(ms->vars->pid, &g_status, 0);
	signal(SIGINT, SIG_IGN);
}

void	last_child(t_list *list, char **envp, t_exc *var, t_ms *ms)
{
	pid_t	pid;

	var->cmd_args = ft_split(list->content, ' ');
	if (handle_built_in_commands(var, ms->env_list, ms->export))
		return ;
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

char	*checking(char **env, t_ms *ms)
{
	t_list	*tmp;
	t_exc	exc;

	if (!ms->node || !ms->node->content[0])
		return (NULL);
	initialize_execution(&exc, &env, ms);
	tmp = ms->node;
	count_here_doc(ms->node);
	while (ms->node)
	{
		if ((ms->node->next) && ((ft_strfind(ms->node->content, '/') == 1
					&& !handl_path(ms->node->content))
				|| (ft_strfind(ms->node->next->content, '/') == 1
					&& !handl_path(ms->node->next->content))))
			return (NULL);
		ms->pre_last = tmp;
		child_process(ms, env, ms->pre_last);
		tmp = ms->node;
		ms->node = ms->node->next;
	}
	exc.oldpwd = ms->vars->oldpwd;
	protecting_executing(tmp, env, ms, &exc);
	dup2(exc.saved_stdout, STDOUT_FILENO);
	dup2(exc.saved_stdin, STDIN_FILENO);
	return (close(exc.saved_stdout), close(exc.saved_stdin), NULL);
}

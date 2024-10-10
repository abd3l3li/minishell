/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:22:03 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/10 16:10:51 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_redirections(t_ms *ms, t_child **child)
{
	handle_pipe_redirection(&ms->node, ms->vars);
	if ((*ms->node).type == PIPE)
		return ;
	handle_pipe_creation(ms->vars);
	while (ms->node && ms->node->next
		&& (ms->node->next->type == REDIRACTION_OUT
			|| ms->node->type == REDIRACTION_OUT
			|| ms->node->next->type == REDIRACTION_OUT_APPEND
			|| ms->node->type == REDIRACTION_OUT_APPEND))
	{
		close((*child)->fd);
		handle_output_redirection(&ms->node, ms->vars, &(*child)->fd);
		handle_output_append_redirection(&ms->node, ms->vars, &(*child)->fd);
		ms->node = ms->node->next;
		if (!ms->node->next)
		{
			handle_last_redirection(ms->pre_last, ms->vars);
			break ;
		}
		ms->pre_last = ms->node;
		if((*child)->fd == -1)
			break;
	}

}

void	handle_redirection_out(t_child *child, t_exc *var, char **envp)
{
	dup2(child->fd, 1);
	close(child->fd);
	if (!check_for_built_in(child->tmp, child->env_list, var, child->export))
		ft_exitt(0);
	execute(child->tmp->content, envp);
	ft_exitt(0);
}

void	handle_redirection_in(t_list **list, t_exc *var, t_child *child,
		char **envp)
{
	int	fd;

	var->file = (*list)->next->next->content;
	fd = open(var->file, O_RDONLY, 0666);
	if (fd == -1)
	{
		if(access(var->file,F_OK) == 0)
			handle_error(&var->file,2);
		else
		{	
			put_str_fd(var->file,2);
			write(2, ": No such file or directory\n", 28);
		}
		ft_exitt(1);
	}
	dup2(fd, 0);
	close(fd);
	if (!check_for_built_in((*list), child->env_list, var, child->export))
		ft_exitt(0);
	execute((*list)->content, envp);
}

void	handle_heredoc_loop(int fd, char *file, char *str2)
{
	char	*str;

	str = readline("> ");
	while (str)
	{
		if (ft_strcmp(str, file) == 0)
		{
			close(fd);
			fd = open(str2, O_RDONLY);
			dup2(fd, 0);
			close(fd);
			break ;
		}
		write(fd, str, ft_strlen(str));
		write(fd,"\n",1);
		str = readline("> ");
	}
}

void	handle_here_doc(t_list **list, t_exc *var, char **envp, t_child *child)
{
	int		fd;
	char	*str;
	char	*str2;

	printf("list->content: %s\n", (*list)->content);
	if ((*list)->next->type == HERE_DOC)
		var->file = ft_strdup((*list)->next->next->content);
	else
		var->file = ft_strdup((*list)->next->content);
	fd = open("/proc/uptime", O_RDONLY, 0644);
	str = get_next_line(fd);
	str = ft_strjoin("/tmp/", str);
	close(fd);
	fd = open(str, O_CREAT | O_RDWR | O_APPEND, 0777);
	str2 = ft_strdup(str);
	ft_free(str);
	handle_heredoc_loop(fd, var->file, str2);
	if ((*list)->next->type == HERE_DOC && (*list)->type == WORD)
	{
		dup2(fd,0);
		close(fd);
		if (!check_for_built_in((*list), child->env_list, var, child->export))
			ft_exitt(0);
		execute((*list)->content, envp);
	}
}

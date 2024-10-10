/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:21:26 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/10 15:55:46 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(t_list **list, t_exc *var, t_child *child, char **envp)
{
	close(var->fd[0]);
	dup2(var->fd[1], 1);
	close(var->fd[1]);
	if (!check_for_built_in((*list), child->env_list, var, child->export))
		ft_exitt(0);
	execute((*list)->content, envp);
	ft_exitt(0);
}

void	handle_word(t_list **list, char **envp)
{
	execute((*list)->content, envp);
	ft_exitt(0);
}

void	execute_child_process(t_ms *ms, char **envp, t_list *pre_last_list,
		t_child *child)
{
	if (child->tmp->next == NULL)
		ft_exitt(0);
	if (child->tmp->next->type == REDIRACTION_OUT_APPEND
		|| child->tmp->next->type == REDIRACTION_OUT)
		handle_redirection_out(child, ms->vars, envp);
	else if ((*ms->node).next->type == REDIRACTION_IN)
		handle_redirection_in(&ms->node, ms->vars, child, envp);
	else if ((*ms->node).next->type == HERE_DOC)
		handle_here_doc(&ms->node, ms->vars, envp, child);
	else if ((*ms->node).next->type == PIPE)
		handle_pipe(&ms->node, ms->vars, child, envp);
	else if ((*ms->node).type == WORD)
		handle_word(&ms->node, envp);
	ft_exitt(0);
}

int	handle_built_in_commands(t_exc *var, t_env *env_list, t_env *export)
{
	if (ft_strncmp(var->cmd_args[0], "cd", 3) == 0)
	{
		ft_cd(var, env_list, export);
		return (1);
	}
	if (ft_strncmp(var->cmd_args[0], "unset", 5) == 0)
	{
		ft_unset(&env_list, var->cmd_args[1]);
		ft_unset(&export, var->cmd_args[1]);
		return (1);
	}
	if (ft_strncmp(var->cmd_args[0], "exit", 4) == 0)
	{
		ft_exit(var);
		return (1);
	}
	if (ft_strncmp(var->cmd_args[0], "export", 6) == 0
		&& var->cmd_args[1] != NULL)
	{
		ft_export(env_list, export, var);
		return (1);
	}
	return (0);
}

void	free_t_exc(t_exc *exc)
{
	char	**p;

	if (exc->paths)
	{
		p = exc->paths;
		while (*p)
		{
			ft_free(*p);
			p++;
		}
		ft_free(exc->paths);
	}
	if (exc->cmd_args)
	{
		p = exc->cmd_args;
		while (*p)
		{
			ft_free(*p);
			p++;
		}
		ft_free(exc->cmd_args);
	}
	ft_free(exc);
}

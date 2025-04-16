/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:22:39 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/11 21:12:15 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_pipe_redirection(t_list **list, t_exc *var)
{
	if ((*list)->type == PIPE)
	{
		close(var->fd[1]);
		dup2(var->fd[0], 0);
		close(var->fd[0]);
	}
}

void	handle_pipe_creation(t_exc *var)
{
	if (pipe(var->fd) == -1)
		error(2);
}

void	handle_output_redirection(t_list **list, t_exc *var, int *fd)
{
	if ((*list)->next->type == REDIRACTION_OUT
		|| (*list)->type == REDIRACTION_OUT)
	{
		if ((*list)->next->type == REDIRACTION_OUT)
			var->file = (*list)->next->next->content;
		else
			var->file = (*list)->next->content;
		if (var->file == NULL)
			return ;
		*fd = open(var->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (*fd == -1)
			handle_error(&var->file, 2);
	}
}

void	handle_output_append_redirection(t_list **list, t_exc *var, int *fd)
{
	if ((*list)->next->type == REDIRACTION_OUT_APPEND
		|| (*list)->type == REDIRACTION_OUT_APPEND)
	{
		if ((*list)->next->type == REDIRACTION_OUT_APPEND)
			var->file = (*list)->next->next->content;
		else
			var->file = (*list)->next->content;
		*fd = open(var->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (*fd == -1)
			handle_error(&var->file, 2);
	}
}

void	handle_last_redirection(t_list *pre_last, t_exc *var)
{
	if (pre_last && (pre_last->type == REDIRACTION_OUT
			|| pre_last->type == REDIRACTION_OUT_APPEND
			|| pre_last->type == REDIRACTION_IN))
		var->redirection_check = 1;
}

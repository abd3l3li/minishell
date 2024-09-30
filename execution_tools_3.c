/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:22:39 by her-rehy          #+#    #+#             */
/*   Updated: 2024/09/29 22:22:40 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void handle_pipe_redirection(t_list **list, t_exc *var)
{
    if ((*list)->type == Pipe)
    {
        close(var->fd[1]);
        dup2(var->fd[0], 0);
        close(var->fd[0]);
    }
}

void handle_pipe_creation(t_exc *var)
{
    if (pipe(var->fd) == -1)
        error(2);
}

void handle_output_redirection(t_list **list, t_exc *var, int *fd)
{
    if ((*list)->next->type == Rediracion_Out || (*list)->type == Rediracion_Out)
    {
        if ((*list)->next->type == Rediracion_Out)
            var->file = (*list)->next->next->content;
        else
            var->file = (*list)->next->content;
        *fd = open(var->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    }
}

void handle_output_append_redirection(t_list **list, t_exc *var, int *fd)
{
    if ((*list)->next->type == Rediracion_Out_Append || (*list)->type == Rediracion_Out_Append)
    {
        if ((*list)->next->type == Rediracion_Out_Append)
            var->file = (*list)->next->next->content;
        else
            var->file = (*list)->next->content;
        *fd = open(var->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
    }
}

void handle_last_redirection(t_list *pre_last, t_exc *var)
{
    if (pre_last && pre_last->type == Rediracion_Out || pre_last->type == Rediracion_Out_Append)
        var->redirection_check = 1;
}

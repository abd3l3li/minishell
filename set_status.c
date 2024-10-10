/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 09:57:47 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/10 15:41:00 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     set_status(t_list *list, char **env, t_list *tmp)
{
        t_exc *exc;
        
        if(ft_strcmp("exit", list->content) == 0)
                ft_exitt(g_status);
        exc = (t_exc *)ft_malloc(sizeof(t_exc));
        if (exc == NULL)
                return (0);
        if (list->type != WORD && list->type != ENV)
                return (0);
        g_status = 127;
        if (tmp->type == REDIRACTION_IN || tmp->type == REDIRACTION_OUT || tmp->type == REDIRACTION_OUT_APPEND
                || tmp->type == HERE_DOC)
                return (g_status = 0,0);
        if (list->type == HERE_DOC || list->type == REDIRACTION_IN
                || list->type == REDIRACTION_OUT || list->type == REDIRACTION_OUT_APPEND)
                return (g_status = 0,0);
        if (is_built_in(list->content))
                return (g_status = 0,1);
        exc->cmd_args = ft_split(list->content, ' ');
        exc->paths = getpaths(env);
        exc->tmp = find_path(exc->cmd_args[0], env);
        if (exc->tmp == NULL)
                return (0);
        g_status = 0;
        return (1);
}

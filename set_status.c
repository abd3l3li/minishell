/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 09:57:47 by her-rehy          #+#    #+#             */
/*   Updated: 2024/09/30 20:41:31 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     set_status(t_list *list, char **env, t_list *tmp)
{
        t_exc *exc;

  
        exc = (t_exc *)malloc(sizeof(t_exc));
        if (exc == NULL)
                return (0);
        if (list->type != Word)
                return (0);
        status = 127;
        if (tmp->type == Pipe || tmp->type == Rediracion_In
                || tmp->type == Rediracion_Out || tmp->type == Rediracion_Out_Append
                || tmp->type == Here_doc)
                return (status = 0,0);
        if (list->type == Here_doc || list->type == Rediracion_In
                || list->type == Rediracion_Out || list->type == Rediracion_Out_Append)
                return (status = 0,0);
        if (is_built_in(list->content))
                return (status = 0,1);
        exc->cmd_args = ft_split(list->content, ' ');
        exc->paths = getpaths(env);
        exc->tmp = find_path(exc->cmd_args[0], env);
        if (exc->tmp == NULL)
                return (0);
        status = 0;
        return (1);
}

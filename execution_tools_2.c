/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:22:03 by her-rehy          #+#    #+#             */
/*   Updated: 2024/09/29 22:22:05 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void setup_redirections(t_list **list, t_exc *var, t_list *pre_last_list, t_list **tmp, int *fd, t_env *env_list, t_env *export, t_env **envs)
{
    t_list *pre_last = NULL;

    handle_pipe_redirection(list, var);
    if ((*list)->type == Pipe)
        return;

    handle_pipe_creation(var);

    while (*list && (*list)->next && ((*list)->next->type == Rediracion_Out || (*list)->type == Rediracion_Out || (*list)->next->type == Rediracion_Out_Append || (*list)->type == Rediracion_Out_Append))
    {
        close(*fd);
        
        handle_output_redirection(list, var, fd);
        handle_output_append_redirection(list, var, fd);

        (*list) = (*list)->next;
        if (!(*list)->next)
        {
            handle_last_redirection(pre_last, var);
            break;
        }
        pre_last = (*list);
    }
}

void handle_redirection_out(t_list *tmp, int fd, t_env *env_list, t_exc *var, t_env *export, char **envp)
{
    dup2(fd, 1);
    close(fd);
    if (!check_for_built_in(tmp, env_list, var, export))
        ft_exitt(0);
    execute(tmp->content, envp);
    ft_exitt(0);
}

void handle_redirection_in(t_list **list, t_exc *var, t_env *env_list, t_env *export, char **envp)
{
    int fd;
    var->file = (*list)->next->next->content;
    fd = open(var->file, O_RDONLY, 0666);
    if (fd == -1)
    {
        write(2, var->file, ft_strlen(var->file));
        write(2, ": No such file or directory\n", 28);
        ft_exitt(1);
    }
    dup2(fd, 0);
    close(fd);
    if (!check_for_built_in((*list), env_list, var, export))
        ft_exitt(0);
    execute((*list)->content, envp);
}

void handle_heredoc_loop(int fd, char *file, char *str2)
{
    char *str;

    str = get_next_line(0); 
    while (str)
    {
        write(fd, str, ft_strlen(str));
        str = get_next_line(0); 
        if (ft_strncmp(str, file, ft_strlen(file)) == 0) 
        {
            close(fd);
            fd = open(str2, O_RDONLY); 
            dup2(fd, 0);
            close(fd);
            break;
        }
    }
}

void handle_here_doc(t_list **list, t_list *pre_last_list, t_exc *var, char **envp, t_env *env_list, t_env *export)
{
    int fd;
    char *str;
    char *str2;

    if ((*list)->next->type == Here_doc)
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
    if ((*list)->next->type == Here_doc)
    {
        if (!check_for_built_in((*list), env_list, var, export))
            ft_exitt(0);
        execute((*list)->content, envp);
    }
}



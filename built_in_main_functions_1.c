/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_main_functions_1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:09:54 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/06 22:48:06 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *strnstr(char *s1, char *s2)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(s1[i])
    {
        if(s1[i] == s2[j])
        {
            int start = i;  
            while(s1[i] == s2[j] && s2[j])
            {
                i++;
                j++;
            }
            if(s2[j] == '\0') 
                return (s1 + i - 1); 
            j = 0;
            i = start; 
        }
        i++;
    }
    return (NULL);
}

int echo(t_exc *vars)
{
    int i;
    int check;
    char *spaces;
    int count = 1;
    check = 0;
    i = check_option(vars->cmd_args, &check);
    while (vars->cmd_args[i])
    {
        spaces = strnstr(vars->builtin_tmp,vars->cmd_args[i-1]);
        while(spaces[count] == ' ' && spaces[count-1] == '"')
        {
            printf(" ");
            count++;
        }
        count = 1;
        printf("%s", vars->cmd_args[i]);
        spaces = strnstr(vars->builtin_tmp,vars->cmd_args[i]);
        while(spaces && spaces[count++])
        {
            if(spaces[count] == ' ')
                printf(" ");
        }
        if(vars->cmd_args[i + 1] != NULL)
            printf(" ");        
        i++;
    }
    if(check == 0)
    {
        check = 1;
        printf("\n");
    }
    status = 0;
    return (0);
}

int ft_unset(t_env **env, char *str)
{
    t_env *tmp;
    char **name_value;

    if(!str)
        return 0;
    name_value = ft_split(str, '=');
    if (unset_first(env, str, name_value) == 0)
        return (0);
    tmp = *env;
    while (tmp != NULL && tmp->next != NULL)
    {
        if (ft_strncmp(tmp->next->name, str, ft_strlen(name_value[0])) == 0)
        {
            t_env *to_delete = tmp->next;
            tmp->next = to_delete->next;
            ft_free(to_delete->name);
            ft_free(to_delete->value);
            ft_free(to_delete);
            return (0);
        }
        tmp = tmp->next;
    }

    return (0);
}

int put_str_fd(char *str, int fd)
{
    int i;

    i = 0;
    while (str[i])
    {
        write(fd, &str[i], 1);
        i++;
    }
    return (0);
}
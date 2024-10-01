/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_in_tools_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:06:42 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/01 22:55:13 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int unset_first(t_env **env, char *str, char **name_value)
{
    t_env *tmp;

    while (*env && ft_strncmp((*env)->name, str, ft_strlen(name_value[0])) == 0)
    {
        tmp = *env;
        *env = (*env)->next;
        free(tmp->name);
        free(tmp->value);
        free(tmp);
        return (0);
    }
    return (1);
}

int export_adding(t_env *list, char *args)
{
    t_env *new;

    char **name_value;
    new = malloc(sizeof(t_env));
    if (args == NULL)
        return 0;
    name_value = ft_split(args, '=');
    new->name = ft_strdup(name_value[0]);
    if(name_value[1] == NULL)
        new->value = NULL;
    else
        new->value = ft_strdup(name_value[1]);
    new->next = NULL;
    lstadd_back(&list, new);
    return (0);
}


int check_values(t_env *env,t_env *export, t_exc *vars)
{
    int i;
    i = 0;

    vars->cmd_args = ft_split(vars->cmd, '='); 
    while(vars->cmd[i])
    {
        if(vars->cmd[i] == '=')
        {
            if(ft_isdigit(vars->cmd[i - 1]) == 1)
                return (write(1, "bash: export: `", 15),
                        write(1, vars->cmd, ft_strlen(vars->cmd)),write(1
                        , "': not a valid identifier\n", 27),0);
            if(vars->cmd[i + 1] == '\0' && vars->cmd[i - 1] != ' ')
                return (export_adding(export, vars->cmd),0);
            else if(vars->cmd[i - 1] == ' ')
                return (write(1, "bash: export: `=': not a valid identifier", 41),0);
            else
                return (export_adding(env, vars->cmd),export_adding(export, vars->cmd),0);
        }
        i++;
    }
    export_adding(export, vars->cmd);
    return (0);
}

int compare_list(const char *str, t_env *env_list)
{
    t_env **current = &env_list;
    char **name_value;

    name_value = ft_split(str, '=');
        while ((*current) != NULL)
        {
            if (ft_strcmp(name_value[0], (*current)->name) == 0)
            {
                if(name_value[1] == NULL || ft_strcmp(name_value[1], (*current)->value) == 0)
                        return 1;
                else
                {
                    free((*current)->value);
                    (*current)->value = ft_strdup(name_value[1]);
                    return 1;
                }
            }
            (*current) = (*current)->next;
        }
    return 0; 
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_in_tools_0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:06:42 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/10 18:36:09 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	unset_first(t_env **env, char *str, char **name_value)
{
	t_env	*tmp;

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

int	export_adding(t_env *list, char *args)
{
	t_env	*new;
	char	**name_value;

	new = ft_malloc(sizeof(t_env));
	if (args == NULL)
		return (0);
	if (ft_strchr(args, '=') == NULL)
	{
		new->name = ft_strdup(args);
		new->value = NULL;
		lstadd_back(&list, new);
		return (0);
	}
	name_value = ft_split(args, '=');
	new->name = ft_strdup(name_value[0]);
	if (name_value[1] == NULL)
		new->value = ft_strdup("");
	else
		new->value = ft_strdup(name_value[1]);
	new->next = NULL;
	lstadd_back(&list, new);
	return (0);
}
int process_cmd_char(t_env *env, t_env *export, t_exc *vars, int i)
{
    if (vars->cmd[i] == '=')
    {
        if (ft_isdigit(vars->cmd[i - 1]) == 1)
        {
            write(1, "bash: export: `", 15);
            write(1, vars->cmd, ft_strlen(vars->cmd));
            write(1, "': not a valid identifier\n", 27);
            return 1;
        }
        if (vars->cmd[i + 1] == '\0' && vars->cmd[i - 1] != ' ')
            return ( export_adding(export, vars->cmd), 0);
        else if (vars->cmd[i - 1] == ' ')
            return (write(1, "bash: export: `=': not a valid identifier", 41), 0);
        else
        {
            export_adding(env, vars->cmd);
            export_adding(export, vars->cmd);
            return 1;
        }
    }
    return 0;
}

int check_values(t_env *env, t_env *export, t_exc *vars)
{
    int i;

    i = 0;
    vars->cmd_args = ft_split(vars->cmd, '=');
    if (ft_str_isdigit(vars->cmd_args[0]) == 1)
    {
        write(1, "bash: export: `", 15);
        write(1, vars->cmd, ft_strlen(vars->cmd));
        write(1, "': not a valid identifier\n", 27);
        return 0;
    }
    if (vars->cmd_args[1] == NULL)
        return (export_adding(export, vars->cmd), 0);
    while (vars->cmd[i])
    {
        if (process_cmd_char(env, export, vars, i))
            return 0;
        i++;
    }
    export_adding(export, vars->cmd);
    return 0;
}

int	compare_list(const char *str, t_env *env_list)
{
	t_env	**current;
	char	**name_value;

	current = &env_list;
	name_value = ft_split(str, '=');
	while ((*current) != NULL)
	{
		if ((*current)->value == NULL)
			(*current)->value = ft_strdup("");
		if (ft_strcmp(name_value[0], (*current)->name) == 0)
		{
			if (name_value[1] == NULL || ft_strcmp(name_value[1],
					(*current)->value) == 0)
				return (1);
			else
			{
				ft_free((*current)->value);
				(*current)->value = ft_strdup(name_value[1]);
				return (1);
			}
		}
		(*current) = (*current)->next;
	}
	return (0);
}

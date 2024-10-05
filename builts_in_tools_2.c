/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_in_tools_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:06:32 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/04 21:56:26 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **create_own_env(void)
{
    char **env;
    env = (char **)malloc(sizeof(char **) * 4);
    env[0] = ft_strjoin("PWD=",ft_strdup(getcwd(NULL, 0)));
    env[1] = ft_strdup("SHLVL=1");
    env[2] = ft_strdup("_=/usr/bin/env");
    env[3] = NULL;
    return (env);
}

int handle_numeric_argument(t_exc *vars)
{
    int  num = ascii_to_long(vars->cmd_args[1]);
    if (num == -1)
    {
        write(1, "bash: exit: ", 12);
        put_str_fd(vars->cmd_args[1], 1);
        write(1, ": numeric argument required\n", 29);
        exit(2);
    }
    return (num);
}

t_env	*ft_lstlast(t_env *lst)
{

	while (lst)
	{
		if (!lst->next)
        {
			return (lst);
        }
		lst = lst->next;
	}
	return (lst);
}

void	lstadd_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (env)
	{
		if (*env == NULL)
			*env = new;
		else
		{
			tmp = ft_lstlast(*env);
			tmp->next = new;
		}
	}
}

int index_of_char(const char *str, char ch)
{
    char *pos = ft_strchr(str, ch);
    if (pos != NULL)
        return pos - str;
    else
        return (-1); 
}

int fill_env(t_env **env, char **envp)
{
    int i;
    t_env *tmp;

    i = 0;
    if(!envp[0])
        envp = create_own_env();
    *env = malloc(sizeof(t_env));
    tmp = *env;
    while(envp[i])
    {
        (*env)->name = ft_substr(envp[i], 0, index_of_char(envp[i], '='));
        (*env)->value = ft_substr(envp[i], index_of_char(envp[i], '=') + 1, ft_strlen(envp[i]) - index_of_char(envp[i], '='));
        if(envp[i + 1] == NULL)
            break;
        (*env)->next = malloc(sizeof(t_env));
        (*env) = (*env)->next;
        i++;
    }
    (*env)->next = NULL;
    (*env) = tmp;
    return (0);
}

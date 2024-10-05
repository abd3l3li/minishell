/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_in_tools_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:05:53 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/03 22:31:36 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	x;

	x = ft_strlen(src);
	i = 0;
	if (size != 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (x);
}

int	ascii_to_long(char *str)
{
    size_t    result;
    int		i;
    int     neg;

    i = 0;
    neg = 1;
    if(str[0] == '-')
    {
        i = 1;
        neg = -1;
    }
    result = 0;
    while (str[i])
    {
        if(!ft_isdigit(str[i]))
            return (-1);
        result = result * 10 + str[i] - '0';
        i++;
    }
    result = result * neg;
    if(result > 255 || result < 0)
        return (-1);
    return (result);
}

int ft_print_env(t_env *env)
{
    while(env)
    {
        if(env->value != NULL)
            printf("%s=%s\n", env->name, env->value);
        env = env->next;
    }
    return (0);
}

void update_env_var(t_env *env,  char *name, char *new_value)
{
    t_env *tmp = env;

    while (tmp)
    {
        if (ft_strncmp(tmp->name, name, ft_strlen(name)) == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(new_value);
        }
        tmp = tmp->next;
    }
}

int validate_exit_args(t_exc *vars)
{
    int number_of_args = 0;

    while (vars->cmd_args[number_of_args])
        number_of_args++;

    if (number_of_args > 2)
    {
        write(1, "bash: exit: too many arguments\n", 31);
        return (0);
    }
    return (1);
}

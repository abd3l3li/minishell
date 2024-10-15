/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools_6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:55:13 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/15 18:42:51 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

char	*find_env_value(const char *name, t_env *env_list)
{
	char	*value_copy;

	while (env_list != NULL)
	{
		if (ft_strcmp(env_list->name, name) == 0)
		{
			value_copy = ft_malloc(ft_strlen(env_list->value) + 1);
			if (value_copy == NULL)
				return (NULL);
			strcpy(value_copy, env_list->value);
			return (value_copy);
		}
		env_list = env_list->next;
	}
	return (NULL);
}

char	*extract_after_dollar(char *str)
{
	char	*dollar_ptr;
	size_t	length;
	char	*end_ptr;
	char	*result;

	dollar_ptr = ft_strchr(str, '$');
	if (dollar_ptr == NULL)
		return (NULL);
	dollar_ptr++;
	end_ptr = dollar_ptr;
	while (*end_ptr != '\0' && !ft_isspace(*end_ptr))
		end_ptr++;
	length = end_ptr - dollar_ptr;
	result = ft_malloc(length + 1);
	if (result == NULL)
		return (NULL);
	ft_strncpy(result, dollar_ptr, length);
	result[length] = '\0';
	return (result);
}

char	*find_first(char *str, char ch1, char ch2)
{
	while (*str != '\0')
	{
		if (*str == ch1 || *str == ch2)
			return (str);
		str++;
	}
	return (NULL);
}

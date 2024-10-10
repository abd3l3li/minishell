/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_in_tools_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:08:39 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/09 21:55:40 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	ft_tolower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int	compare_strings_ignore_case(const char *str1, const char *str2)
{
	int		i;
	char	c1;
	char	c2;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		c1 = ft_tolower(str1[i]);
		c2 = ft_tolower(str2[i]);
		if (c1 != c2)
			return (c1 - c2);
		i++;
	}
	return (ft_tolower(str1[i]) - ft_tolower(str2[i]));
}

int	export_sort(t_env **export)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*tmp_str;

	tmp = (*export);
	tmp2 = (*export);
	while (tmp->next)
	{
		tmp2 = tmp;
		while (tmp2->next)
		{
			if (compare_strings_ignore_case(tmp->name, tmp2->name) > 0)
			{
				tmp_str = tmp->name;
				tmp->name = tmp2->name;
				tmp2->name = tmp_str;
				tmp_str = tmp->value;
				tmp->value = tmp2->value;
				tmp2->value = tmp_str;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_free(tab[i]);
		i++;
	}
	ft_free(tab);
	return (0);
}

int	check_option(char **str, int *check)
{
	int		return_value;
	char	*s;

	return_value = 1;
	while (*(++str))
	{
		if (**str == '-' && *(*str + 1) == 'n')
		{
			return_value++;
			s = *str + 2;
			while (*s++)
			{
				if (*s != 'n')
				{
					return_value -= 1;
					if (return_value >= 2)
						*check = 1;
					return (return_value);
				}
			}
		}
	}
	    if (return_value >= 2)
        	*check = 1;
    return return_value;
}

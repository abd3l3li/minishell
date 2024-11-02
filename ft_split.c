/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:24:55 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/11 21:18:51 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest2;
	char	*src2;

	dest2 = dest;
	src2 = (char *)src;
	if (src2 < dest2)
	{
		dest2 += n - 1;
		src2 += n - 1;
		while (n--)
		{
			*dest2 = *src2;
			dest2--;
			src2--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}

static void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	word_count(char const *str, char c)
{
	int	i;
	int	result;

	result = 1;
	i = 0;
	if (str[0] == c)
		result = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c && str[i + 1] != c && str[i + 1] != '\0')
		{
			i++;
			result++;
		}
		i++;
	}
	return (result);
}

static int	ft_allocate(char **arrstr, char const *s, char sep)
{
	char const	*temp;

	temp = s;
	while (*temp)
	{
		while (*s && *s == sep)
			++s;
		temp = s;
		while (*temp && *temp != sep)
			++temp;
		if ((*temp == sep || *temp == '\0') && temp > s)
		{
			*arrstr = ft_substr(s, 0, temp - s);
			if (*arrstr == NULL)
			{
				ft_free_split(arrstr);
				return (0);
			}
			s = temp;
			arrstr++;
		}
	}
	*arrstr = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**arrstr;

	if (!s)
		return (NULL);
	arrstr = ft_malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!arrstr)
		return (NULL);
	if (!ft_allocate(arrstr, s, c))
		return (NULL);
	return (arrstr);
}

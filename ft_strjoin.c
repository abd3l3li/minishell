/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:30:05 by her-rehy          #+#    #+#             */
/*   Updated: 2024/08/13 10:22:32 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_mystrcpy(char *dest, const char *src, const char *src2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (src2[j] != '\0')
	{
		dest[i] = src2[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*nstr;
	unsigned int	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	nstr = (char *)malloc(sizeof(char) * (len + 1));
	if (nstr == 0)
		return (0);
	ft_mystrcpy(nstr, (char *)s1, (char *)s2);
	return (nstr);
}

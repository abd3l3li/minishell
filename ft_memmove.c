/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:34:38 by her-rehy          #+#    #+#             */
/*   Updated: 2024/08/13 10:29:46 by her-rehy         ###   ########.fr       */
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

#include "minishell.h"

void	*ft_memcpy(void *dest, const void *src, int n)
{
	int	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if (dest != src)
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
        p_err("Malloc error", 54);
	ft_memcpy(result, s + start, len);
	result[len] = '\0';
	return (result);
}
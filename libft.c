#include "minishell.h"

void	*ft_memcpy(void *dest, const void *src, int n)
{
	size_t	i;

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

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n) && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return (0);
}

int	ft_isdigit(int i)
{
	if (i >= '0' && i <= '9')
		return (1);
	return (0);
}
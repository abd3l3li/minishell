#include "minishell.h"

char	*ft_strtrim(char const *s1, char const *set, t_ms *command)
{
	size_t	len;
	char	*result;

	if (!s1)
		return (0);
	while (*s1 && ft_strchr(set, *s1) != 0)
		s1++;
	len = ft_strlen(s1);
	while (len && s1[len - 1] && ft_strchr(set, s1[len - 1]) != 0)
		len--;
	result = (char *)ft_malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	ft_memcpy(result, s1, len);
	result[len] = '\0';
	return (result);
}

char	*ft_strdup(char *src)
{
	int	size;
	char	*dest;

	size = ft_strlen(src);
	dest = (char *)ft_malloc(size * sizeof(char) + 1);
	if (!dest)
		return (0);
	ft_memcpy(dest, src, size);
	dest[size] = '\0';
	return (dest);
}

size_t	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*result;
	long	nb;

	len = ft_len(n);
	nb = n;
	result = ft_malloc(sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	if (n < 0)
	{
		result[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		result[0] = '0';
	result[len--] = '\0';
	while (nb)
	{
		result[len] = nb % 10 + '0';
		len--;
		nb = nb / 10;
	}
	return (result);
}
int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	if (!s1 || !s2)
		return (1);
	while ((i < n) && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (1);
		if (!s1[i] && !s2[i] )
			return (0);
		i++;
	}
	return (0);
}

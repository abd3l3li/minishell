#include "minishell.h"

char	*ft_strdup(const char *src)
{
	int	size;
	char	*dest;

	size = ft_strlen(src);
	dest = (char *)malloc(size * sizeof(char) + 1);
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
	result = malloc(sizeof(char) * len + 1);
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
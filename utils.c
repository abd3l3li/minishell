#include "minishell.h"

extern int status;

void p_err(char *str, int n)
{
    status = n;
    printf("%s\n", str);
}

/*int spaces(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if ((s[i] != ' '))
            return (0);
        i++;
    }
    return (1);
}*/

/*int count_q(char *s, char c)
{
    int n;
    int i;

    n = 0;
    i = 0;
    while(s[i])
    {
        if (s[i] == c)
            n++;
        i++;
    }
    return (n);
}*/

int check_q(char *str)
{
    int i;
    int s;
    int d;

    d = 0;
    s = 0;
    i = 0;
    while(str[i])
    {
        if (str[i] == 34 && !d)
        {
            s = !s;
        }
        else if (str[i] == 39 && !s)
        {
            d = !d;
        }
        i++;
    }
    if (s || d)
        return (1);
    else
        return (0);
}

int double_p(char *s)
{
    int i;

    i = 0;
    while(s[i])
    {
        if (s[i] == '|' && s[i + 1] == '|')
            return (1);
        i++;
    }
    return (0);
}

/*char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!str && !len)
		return (0);
	if (to_find[0] == '\0' || to_find == str)
		return ((char *)str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] == to_find[j] && (i + j) < len)
		{
			if (str[i + j] == '\0' && to_find[j] == '\0')
				return ((char *)&str[i]);
			j++;
		}
		if (to_find[j] == '\0')
			return ((char *)(str + i));
		i++;
	}
	return (0);
}*/

#include "minishell.h"

int	ft_symbols(char c)
{
	return (c == '$' || c == '<' || c == '>' || c == '|' || c == '\0');
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = ft_malloc(size * count);
	if (!result)
		return (0);
	ft_memset(result, 0, (size * count));
	return (result);
}

char	*remove_qoute(char *str)
{
	char	*res;

	int (i), (j), (flag);
	i = 0;
	j = 0;
	flag = 0;
	res = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (flag == 0)
				flag = str[i];
			else if (flag == str[i])
				flag = 0;
			else
				res[j++] = str[i];
		}
		else
			res[j++] = str[i];
		i++;
	}
	res[j] = 0;
	return (res);
}
void	ft_skip_q(t_ms *cmd)
{
	t_list	*tmp;
	char	*newstr;
	char	*temp;

    tmp = cmd->node;
    while (tmp)
    {
        if((ft_strchr(tmp->content, '\'') || ft_strchr(tmp->content, '\"')) 
            && (!ft_strnstr(tmp->content, "echo")))
        {
            newstr = remove_qoute(tmp->content);
            temp = tmp->content;
            tmp->content = newstr;
            ft_free(temp);
        }
        tmp = tmp->next;
    }
}

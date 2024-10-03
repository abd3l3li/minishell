#include "minishell.h"

extern int status;

int	empty_check(char *s)
{
	int len;
	int i;

	len = ft_strlen(s);
	if (len == 2 && ((s[0] == '\"' && s[len - 1] == '\"') || (s[0] == '\'' && s[len - 1] == '\'')))
		return (1);
	else if ((s[0] == '\"' && s[len - 1] == '\"') || (s[0] == '\'' && s[len - 1] == '\''))
	{
		s++;
		len -= 2;
	}
	i = 0;
	while (s[i] && i < len)
	{
		if (s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int to_be_continued(t_list *tmp)
{
    /*if (ft_strnotcmp(tmp->content, "//", 2) && tmp->next == NULL)
        {
            status = 126;
            printf("bash: Is a directory\n");
            return (1);
        }
    else if (ft_strnotcmp(tmp->content, "\\", 2) && tmp->next == NULL)
    {
        status = 127;
        printf("bash: command not found\n");
        return (1);
    }*/
    if (tmp->next && ft_strnotcmp(tmp->content, ">>", 2) && ft_strnotcmp(tmp->next->content, "<<", 2))
    {
            status = 2;
            printf("bash: syntax error near unexpected token\n");
            return (1);
    }
    else if (tmp->next && ft_strnotcmp(tmp->content, "<<", 2) && ft_strnotcmp(tmp->next->content, ">>", 2))
    {
            status = 127;
            printf("bash: syntax error near unexpected token\n");
            return (1);
    }
    return (0);
}

int ft_pars(t_ms *cmd)
{
    t_list *tmp;
    int     i;

    tmp = cmd->node;
    while (tmp)
    {
        if ((ft_strnotcmp(tmp->content, ">>", 2) || ft_strnotcmp(tmp->content, "<<", 2)) && (tmp->next == NULL))
        {
            status = 2;
            printf("bash: syntax error near unexpected token\n");
            return (1);
        }
        else
        {
            i = to_be_continued(tmp);
            if (i == 1)
                return (1);
        }
        tmp = tmp->next;
    }
    return (i);
}

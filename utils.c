/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:47:27 by abel-baz          #+#    #+#             */
/*   Updated: 2024/10/11 21:47:30 by abel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quoted(t_ms *command, char *s, int i)
{
	char	c;
	int		flag;

	flag = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && !flag)
		{
			flag = 1;
			c = s[i];
			i++;
		}
		else if (flag && c == s[i])
		{
			flag = 0;
			i++;
			break ;
		}
		else
			i++;
	}
	ft_listadd_back(&(command->node), ft_listnew(s, i, QUOTED));
	return (i);
}

int	valid_cmd(t_ms *cmd)
{
	int	len;
	int	i;

	i = 1;
	len = ft_strlen(cmd->s);
	if (len >= 2 && ((cmd->s[0] == '\'' && cmd->s[len - 1] == '\'')
			|| (cmd->s[0] == '\"' && cmd->s[len - 1] == '\"')))
	{
		while (i < len - 1)
		{
			if (cmd->s[i] == '|' || cmd->s[i] == '<' || cmd->s[i] == '>'
				|| cmd->s[i] == '-')
				return (1);
			i++;
		}
	}
	return (0);
}

void	p_err(char *str, int n)
{
	g_status = n;
	printf("%s\n", str);
}

int	check_q(char *str)
{
	int	i;
	int	s;
	int	d;

	d = 0;
	s = 0;
	i = 0;
	while (str[i])
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

char	*ft_strchr(char const *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	else
		return (NULL);
}

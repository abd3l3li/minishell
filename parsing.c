/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:46:55 by abel-baz          #+#    #+#             */
/*   Updated: 2024/10/13 22:32:29 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check(char *s)
{
	int	last;
	int	yes;
	int	i;

	last = ft_strlen(s);
	yes = 0;
	i = 0;
	while (s[i] == 32)
		i++;
	if (check_q(s + i))
	{
		yes = 1;
		printf("syntax error>\n");
	}
	if ((*(s + i) == '|' || s[last - 1] == '|'))
	{
		yes = 1;
		p_err("minishell: syntax error near unexpected token `|'", 2);
	}
	return (yes);
}

int	empty_check(char *s)
{
	int	len;
	int	i;

	len = ft_strlen(s);
	if (len == 2 && ((s[0] == '\"' && s[len - 1] == '\"') || (s[0] == '\''
				&& s[len - 1] == '\'')))
		return (1);
	else if ((s[0] == '\"' && s[len - 1] == '\"') || (s[0] == '\'' && s[len
				- 1] == '\''))
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

static int	to_be_continued(t_list *tmp)
{
	if (tmp->next && ft_strnotcmp(tmp->content, ">>", 2)
		&& ft_strnotcmp(tmp->next->content, "<<", 2))
	{
		g_status = 2;
		printf("bash: syntax error near unexpected token\n");
		return (1);
	}
	else if (tmp->next && ft_strnotcmp(tmp->content, "<<", 2)
		&& ft_strnotcmp(tmp->next->content, ">>", 2))
	{
		g_status = 127;
		printf("bash: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}

int	ft_pars(t_ms *cmd)
{
	t_list	*tmp;
	int		i;

	tmp = cmd->node;
	while (tmp)
	{
		if ((ft_strnotcmp(tmp->content, ">>", 2) || ft_strnotcmp(tmp->content,
					"<<", 2)) && (tmp->next == NULL))
		{
			g_status = 2;
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
	i = ft_more_parse(cmd);
	return (i);
}

void	ft_remove_spaces(t_ms *cmd)
{
	int		i;
	t_list	*tmp;

	tmp = cmd->node;
	while (tmp)
	{
		i = ft_strlen(tmp->content) - 1;
		while ((i >= 0 && tmp->content[i] == 32) && tmp->content[i] != '\''
			&& tmp->content[i] != '\"')
		{
			if (tmp->next->type == ENV || tmp->next->type == ENV_WORD)
				break ;
			tmp->content[i] = '\0';
			i--;
		}
		tmp = tmp->next;
	}
}

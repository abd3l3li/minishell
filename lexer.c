/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:45:51 by abel-baz          #+#    #+#             */
/*   Updated: 2024/10/11 21:45:53 by abel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_var(t_ms *command, char *s)
{
	int	i;

	i = 0;
	if ((s[i] == '$') && (s[i + 1] == '\0' || s[i + 1] == 32 || empty_check(s
				+ 1)))
	{
		if (empty_check(s + 1))
			ft_listadd_back(&(command->node), ft_listnew("", 1, ENV_WORD));
		else
			ft_listadd_back(&(command->node), ft_listnew(s, 1, ENV_WORD));
		i++;
		return (i);
	}
	i++;
	if (s[i] == '?' || (s[i] >= '0' && s[i] <= '9'))
		i++;
	else
		while (s[i] != '\0' && !ft_symbols(s[i]))
			i++;
	ft_listadd_back(&(command->node), ft_listnew(s, i, ENV));
	return (i);
}

static int	to_be_continue(t_ms *command, char *s, int i)
{
	int	num;

	num = 0;
	if (s[i] == s[i + 1])
		num = 2;
	else
		num = 1;
	if (s[i] == '>')
	{
		if (num == 2)
			ft_listadd_back(&(command->node), ft_listnew(s, 2,
					REDIRACTION_OUT_APPEND));
		else
			ft_listadd_back(&(command->node), ft_listnew(s, 1,
					REDIRACTION_OUT));
	}
	else if (s[i] == '<')
	{
		if (num == 2)
			ft_listadd_back(&(command->node), ft_listnew(s, 2, HERE_DOC));
		else
			ft_listadd_back(&(command->node), ft_listnew(s, 1, REDIRACTION_IN));
	}
	return (i + num);
}

int	ft_var(t_ms *command, char *s, int i)
{
	if (ft_symbols(s[i + 1]) || s[i + 1] == '=' || s[i + 1] == 32)
	{
		ft_listadd_back(&(command->node), ft_listnew(s, 2, ENV_WORD));
		i += 2;
	}
	else
		i += env_var(command, s + i);
	return (i);
}

int	ms_split(t_ms *command, char *s)
{
	command->i = 0;
	if (s[command->i] == ':' || s[command->i] == '!' || s[command->i] == '#')
		g_status = (s[command->i++] == '!');
	else if (s[command->i] == 32 || s[command->i] == '|')
	{
		if (s[command->i] == '|')
			ft_listadd_back(&(command->node), ft_listnew(s, 1, PIPE));
		command->i++;
	}
	else if (!ft_symbols(s[command->i]))
	{
		while (!ft_symbols(s[command->i]))
			command->i++;
		ft_listadd_back(&(command->node), ft_listnew(s, command->i, WORD));
	}
	else if (s[command->i] == '$')
		command->i += ft_var(command, s, command->i);
	else
		command->i += to_be_continue(command, s, command->i);
	return (command->i);
}

void	ft_lexer(char *s, t_ms *command)
{
	int	i;

	i = 0;
	if (empty_check(s))
		return (ft_listadd_back(&(command->node), ft_listnew(s, (ft_strlen(s)),
					WORD)));
	else if (valid_cmd(command))
		return (ft_listadd_back(&(command->node), ft_listnew(s, (ft_strlen(s)),
					WORD)));
	i = 0;
	while (s[i])
		i += ms_split(command, s + i);
	ft_remove_spaces(command);
	ft_skip_q(command);
}

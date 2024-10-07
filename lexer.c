#include "minishell.h"

extern int	status;

int	env_var(t_ms *command, char *s)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	if (s[i] == '$' && s[i + 1] == '\0' || s[i + 1] == 32 || empty_check(s + 1))
	{
		if (empty_check(s + 1))
			ft_listadd_back(&(command->node), ft_listnew("", 1, Env_word));
		else
			ft_listadd_back(&(command->node), ft_listnew(s, 1, Env_word));
		i++;
		return (i);
	}
	i++;
	if (s[i] == '?' || (s[i] >= '0' && s[i] <= '9'))
		i++;
	else
		while (s[i] != '\0' && !ft_symbols(s[i]))
			i++;
	ft_listadd_back(&(command->node), ft_listnew(s, i, Env));
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
					Rediracion_Out_Append));
		else
			ft_listadd_back(&(command->node), ft_listnew(s, 1, Rediracion_Out));
	}
	else if (s[i] == '<')
	{
		if (num == 2)
			ft_listadd_back(&(command->node), ft_listnew(s, 2, Here_doc));
		else
			ft_listadd_back(&(command->node), ft_listnew(s, 1, Rediracion_In));
	}
	return (i + num);
}

int	ft_var(t_ms *command, char *s, int i)
{
	if (ft_symbols(s[i + 1]) || s[i + 1] == '=' || s[i + 1] == 32)
	{
		ft_listadd_back(&(command->node), ft_listnew(s, 2, Env_word));
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
		status = (s[command->i++] == '!');
	else if (s[command->i] == 32 || s[command->i] == '|')
	{
		if (s[command->i] == '|')
			ft_listadd_back(&(command->node), ft_listnew(s, 1, Pipe));
		command->i++;
	}
	else if (!ft_symbols(s[command->i]))
	{
		while (!ft_symbols(s[command->i]))
			command->i++;
		ft_listadd_back(&(command->node), ft_listnew(s, command->i, Word));
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
					Word)));
	else if (valid_cmd(command))
		return (ft_listadd_back(&(command->node), ft_listnew(s, (ft_strlen(s)),
					Word)));
	i = 0;
	while (s[i])
		i += ms_split(command, s + i);
	ft_remove_spaces(command);
	ft_skip_q(command);
}

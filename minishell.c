/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:46:36 by abel-baz          #+#    #+#             */
/*   Updated: 2024/10/24 20:33:50 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_status;

void	ft_clear(t_ms *cmd)
{
	if (cmd->s)
		ft_free(cmd->s);
	if (cmd->tmp_s)
		ft_free(cmd->tmp_s);
	cmd->node = NULL;
	cmd->tmp = NULL;
	cmd->name = NULL;
	cmd->value = NULL;
	cmd->s = NULL;
	cmd->tmp_s = NULL;
	cmd->i = 0;
	cmd->done = 0;
}

void	get_init(t_ms **cmd)
{
	*cmd = ft_malloc(sizeof(t_ms));
	if (!*cmd)
		(p_err("Malloc error", 54), exit(54));
	(*cmd)->node = NULL;
	(*cmd)->tmp = NULL;
	(*cmd)->name = NULL;
	(*cmd)->value = NULL;
	(*cmd)->s = NULL;
	(*cmd)->tmp_s = NULL;
	(*cmd)->i = 0;
	(*cmd)->done = 0;
}

void	input(t_ms *command, char **env)
{
	fill_env(&command->env_list, env);
	fill_env(&command->export, env);
	export_sort(&command->export);
	command->prompt = BOLD CMAGENTA "Hamas" CCYAN "-shell" RESET "> ";
	while (1)
	{
		ms_signal();
		command->tmp_s = readline(command->prompt);
		if (!command->tmp_s)
			(p_err("exit", g_status), ft_exitt(g_status));
		command->s = ft_strtrim(command->tmp_s, " ");
		if (ft_check(command->s))
		{
			(add_history(command->s), ft_free(command->s));
			continue ;
		}
		if (command->s[0] != '\0')
			add_history(command->s);
		ft_lexer(command->s, command);
		expand_env(command, command->env_list);
		ft_merge(command);
		if (!ft_pars(command))
			checking(env, command);
		ft_clear(command);
	}
}

int	main(int ac, char **av, char **env)
{
	t_ms	*cmd;

	(void)av;
	if (ac != 1)
		ft_exitt(1);
	get_init(&cmd);
	cmd->vars = ft_malloc(sizeof(t_exc));
	cmd->vars->file = NULL;
	if (!cmd->vars)
		(p_err("Malloc error", 54), exit(54));
	ms_signal();
	input(cmd, env);
}

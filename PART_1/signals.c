/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:47:17 by abel-baz          #+#    #+#             */
/*   Updated: 2024/10/11 21:47:19 by abel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_env(t_ms *command)
{
	t_list	*tmp;

	tmp = command->node;
	while (tmp)
	{
		if (tmp->content[0] == '\"' && tmp->content[1] == '$')
		{
			ft_skip_q(command);
			tmp->type = ENV;
		}
		else if (tmp->content[0] == '\"' && tmp->content[1] == '\''
			&& tmp->content[2] == '$')
		{
			ft_skip_q(command);
			tmp->type = ENV;
		}
		tmp = tmp->next;
	}
}

void	handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_status = 130;
}

void	ms_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:45:00 by abel-baz          #+#    #+#             */
/*   Updated: 2024/10/11 21:45:04 by abel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_value(t_ms *command, char *new_value)
{
	if (command->tmp->content)
		ft_free(command->tmp->content);
	command->tmp->content = ft_strdup(new_value);
}

static void	to_be_continued(t_ms *command, t_env *env_list)
{
	if (!ft_strncmp(env_list->name, command->name, ft_strlen(command->name)))
	{
		command->value = env_list->value;
		set_value(command, command->value);
		command->tmp->type = ENV_WORD;
		command->done = 1;
	}
	else if (command->name[0] == '0')
	{
		set_value(command, "bash");
		command->done = 1;
	}
	else if (strncmp(command->name, "?", 1) == 0)
	{
		set_value(command, ft_itoa(g_status));
		command->done = 1;
	}
	else if (command->value == NULL)
		set_value(command, "");
}

void	expand_env(t_ms *command, t_env *env_list)
{
	command->tmp = command->node;
	while (command->tmp)
	{
		if (command->tmp->type == HERE_DOC)
			command->tmp = command->tmp->next;
		else if (command->tmp->type == ENV)
		{
			command->name = ft_strdup(command->tmp->content + 1);
			command->value = NULL;
			while (env_list && !command->done)
			{
				to_be_continued(command, env_list);
				env_list = env_list->next;
			}
			ft_free(command->name);
		}
		else if ((command->tmp->content[0] == '>'
				|| (command->tmp->content[0] == '<'
					&& command->tmp->content[1] == '\0'))
			&& (command->tmp->next
				&& command->tmp->next->content[0] == '$'))
			p_err("bash: ambiguous redirect", 1);
		command->tmp = command->tmp->next;
	}
}

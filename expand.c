/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:45:00 by abel-baz          #+#    #+#             */
/*   Updated: 2024/10/12 20:11:20 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_merge_quoted(t_ms *cmd)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = cmd->node;
	prev = NULL;
	while (tmp)
	{
		if (prev && prev->type == WORD && tmp->type == QUOTED)
		{
			ft_prev(&tmp, prev);
			continue ;
		}
		else if (tmp->type == QUOTED)
			tmp->type = WORD;
		prev = tmp;
		tmp = tmp->next;
	}
}

void	set_value(t_ms *command, char *new_value)
{
	if (command->tmp->content)
		ft_free(command->tmp->content);
	command->tmp->content = ft_strdup(new_value);
}

static void	to_be_continued(t_ms *command, t_env *env_list)
{
	if (!ft_strcmp(env_list->name, command->name))
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
	else if (ft_strncmp(command->name, "?", 1) == 0)
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
		command->tmp_env = env_list;
		if (command->tmp->type == HERE_DOC)
			command->tmp = command->tmp->next;
		else if (command->tmp->type == ENV)
		{
			command->name = ft_strdup(command->tmp->content + 1);
			command->value = NULL;
			while (command->tmp_env)
			{
				to_be_continued(command, command->tmp_env);
				command->tmp_env = command->tmp_env->next;
			}
			ft_free(command->name);
		}
		else if ((command->tmp->content[0] == '>'
				|| (command->tmp->content[0] == '<'
					&& command->tmp->content[1] == '\0')) && (command->tmp->next
				&& command->tmp->next->content[0] == '$'))
			p_err("bash: ambiguous redirect", 1);
		command->tmp = command->tmp->next;
	}
}

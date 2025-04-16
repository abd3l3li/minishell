/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 09:57:47 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/15 18:16:15 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**create_own_env(void)
{
	char	**env;

	env = ft_malloc(sizeof(char **) * 4);
	env[0] = ft_strjoin("PWD=", ft_strdup(getcwd(NULL, 0)));
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	return (env);
}

int	set_status(t_list *list, char **env, t_list *tmp)
{
	t_exc	*exc;

	if (ft_strcmp("exit", list->content) == 0)
		ft_exitt(g_status);
	exc = (t_exc *)ft_malloc(sizeof(t_exc));
	if (exc == NULL)
		return (0);
	if (list->type != WORD && list->type != ENV)
		return (0);
	g_status = 127;
	if (tmp->type == REDIRACTION_IN || tmp->type == REDIRACTION_OUT
		|| tmp->type == REDIRACTION_OUT_APPEND || tmp->type == HERE_DOC)
		return (g_status = 0, 0);
	if (list->type == HERE_DOC || list->type == REDIRACTION_IN
		|| list->type == REDIRACTION_OUT
		|| list->type == REDIRACTION_OUT_APPEND)
		return (g_status = 0, 0);
	if (is_built_in(list->content))
		return (g_status = 0, 1);
	exc->cmd_args = ft_split(list->content, ' ');
	exc->paths = getpaths(env);
	exc->tmp = find_path(exc->cmd_args[0], env);
	if (exc->tmp == NULL)
		return (0);
	return (g_status = 0, 1);
}

int	compare_list(const char *str, t_env *env_list)
{
	t_env	**current;
	char	**name_value;

	current = &env_list;
	name_value = ft_split(str, '=');
	while ((*current))
	{
		if (!(*current)->value)
			(*current)->value = ft_strdup("");
		if (ft_strcmp(name_value[0], (*current)->name) == 0)
		{
			if (!name_value[1] || ft_strcmp(name_value[1],
					(*current)->value) == 0)
				return (1);
			else
			{
				ft_free((*current)->value);
				(*current)->value = ft_strdup(name_value[1]);
				return (1);
			}
		}
		(*current) = (*current)->next;
	}
	return (0);
}

int	ft_flags(char *s)
{
	return ((s[0] == '|' || s[0] == '<' || s[0] == '>') || (s[1] && (s[1] == '<'
				|| s[1] == '>')));
}

int	ft_more_parse(t_ms *cmd)
{
	t_list	*tmp;

	tmp = cmd->node;
	while (tmp)
	{
		if (ft_flags(tmp->content))
		{
			if (tmp->next && ft_flags(tmp->next->content))
			{
				printf("bash: syntax error near unexpected token\n");
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

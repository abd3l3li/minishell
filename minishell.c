#include "minishell.h"

int status;

void ft_clear(t_ms *cmd)
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

void    get_init(t_ms **cmd)
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

void ft_lexer(char *s, t_ms *command)
{
	int i;

	i = 0;
	//pipe_split(s + i, command); //to be used
	while (s[i])
	{
		if (s[i] == '\t')
			s[i] = 32;
		i++;
	}
	if (empty_check(s))
		return (ft_listadd_back(&(command->node), ft_listnew(s, (ft_strlen(s)), Word)));
	i = 0;
	while (s[i])
		i += ms_split(command, s + i);
	ft_remove_spaces(command);
	ft_skip_q(command);
}

void input(t_ms *command, char **env , t_exc *vars)
{
	fill_env(&command->env_list, env);
	fill_env(&command->export, env);
	export_sort(&command->export);

	command->prompt = PROMPT;
	while(1)
	{
		ms_signal();
		command->tmp_s = readline(command->prompt);
		if (!command->tmp_s)
			(p_err("exit", 0), ft_exitt(0));
		command->s = ft_strtrim(command->tmp_s, " ", command);
		if (command->s[0] == '\0' || ft_check(command->s))
		{
			(add_history(command->s), ft_free(command->s));
			continue;
		}
		add_history(command->s);
		ft_lexer(command->s, command);
		expand_env(command, command->env_list);
		ft_merge(command);
		if (!ft_pars(command))
			checking(command->node, env, command, command->env_list, command->export, vars);
		ft_clear(command);
	}
}

int main(int ac, char **av, char **env)
{
	t_ms *cmd;
	t_exc *vars;

	if (ac != 1)
		ft_exitt(1);
	vars = ft_malloc(sizeof(t_exc));
	if (!vars)
		(p_err("Malloc error", 54), exit(54));
	vars->oldpwd = getcwd(NULL, 0);
	get_init(&cmd);
	ms_signal();
	input(cmd, env, vars);
}   


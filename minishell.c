#include "minishell.h"

int status;

int	empty_check(char *s)
{
	int len;
	int i;

	len = ft_strlen(s);
	if (len == 2 && ((s[0] == '\"' && s[len - 1] == '\"') || (s[0] == '\'' && s[len - 1] == '\'')))
		return (1);
	else if ((s[0] == '\"' && s[len - 1] == '\"') || (s[0] == '\'' && s[len - 1] == '\''))
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

void    get_init(t_ms **cmd)
{
	*cmd = malloc(sizeof(t_ms));
	if (!cmd)
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
	ft_skip_q(command);
}

void inpute(t_ms *command, char **env , t_exc *vars)
{
	fill_env(&command->env_list, env);
	fill_env(&command->export, env);
	export_sort(&command->export);// need to recheck with houssam
	command->prompt = BOLD CMAGENTA "Hamas" CCYAN "-shell" RESET "> ";
	while(1)
	{
		signal(SIGINT, handler);
		command->tmp_s = readline(command->prompt);
		if (!command->tmp_s)
			(free_cmd(command), p_err("exit", 0), exit(0));
		if (command->tmp_s[0] == '\0' || ft_check(command->tmp_s))// history of spaces recheck
		{
			free(command->tmp_s);
			continue;
		}
		command->s = ft_strtrim(command->tmp_s, " ", command);
		add_history(command->s);
		ft_lexer(command->s, command);
		expand_env(command, command->env_list);
		ft_merge(command);
		if (!ft_pars(command))
			checking(command->node, env, command, command->env_list, command->export, vars);
		if (command->node || command->s)//need to free init also
			(free(command->s), free_cmd(command));
		get_init(&command);
	}
}

int main(int ac, char **av, char **env)
{
	t_ms *cmd;
	t_exc *vars;


	if (ac != 1)
		exit(1);
	vars = malloc(sizeof(t_exc));
	if (!vars)
		(p_err("Malloc error", 54), exit(54));
	vars->oldpwd = getcwd(NULL, 0);
	get_init(&cmd);
	// ms_signal(0);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	inpute(cmd, env, vars);
}   


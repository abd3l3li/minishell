#include "minishell.h"

int status;

void    get_init(t_ms **cmd)
{
	*cmd = (t_ms *)malloc(sizeof(t_ms));
	if (!(*cmd))
		(p_err("Malloc error", 54), exit(54));
	**cmd = (t_ms){ .node = NULL};
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
	i = 0;	
	while (s[i])
		i += ms_split(command, s + i);
	ft_skip_q(command);
}

void inpute(t_ms *command, char **env )
{
	char *s;
	t_env *env_list;
    t_env *export;
	const char  *prompt;

	fill_env(&env_list, env);
    fill_env(&export, env);
    export_sort(&export,env);
	prompt = BOLD CMAGENTA "Hamas" CCYAN "-shell" RESET "> ";
	while(1)
	{
		s = readline(prompt);
		if (!s)
			(free_cmd(command), p_err("exit", 0), exit(0));
			
		if (s[0] == '\0' || (spaces(s))) //not needed ig
		{
			free(s);
			continue;
		}
		add_history(s);
		if (ft_check(s))
			continue;
		ft_lexer(s, command);
		expand_env(command, env_list); //need first to get the env list
		ft_merge(command);
	    if (!ft_pars(command))
			checking(command->node, env, command, env_list, export);
			

		//freeing and re init
		//if (command->node)
			//free_cmd(command);
		get_init(&command);
	}
}

int main(int ac, char **av, char **env)
{
	t_ms *cmd;

	if (ac != 1)
		exit(1);
	get_init(&cmd);
	ms_signal(0);
	inpute(cmd, env);
}   


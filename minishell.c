#include "minishell.h"

int status;

void    get_init(t_ms **cmd)
{
	*cmd = (t_ms *)malloc(sizeof(t_ms));
	if (!(*cmd))
		(p_err("Malloc error", 54), exit(54));
	**cmd = (t_ms){ .node = NULL, .pcmd = NULL};
}

void    ft_lexer(char *s, t_ms *command)
{
	int i;

	i = 0;
	//while (s[i] == ' ' || s[i] == '\t')
		//i++;
	//pipe_split(s + i, command); //to be used
	while (s[i])
		i += ms_split(command, s + i);
	ft_skip_q(command);
}

void    inpute(t_ms *command, t_env *env_list)
{
	char *s;
	int i = 0;;
	const char  *prompt;

	prompt = BOLD CMAGENTA "Hamas" CCYAN "-shell" RESET "> ";
	while(1)
	{
		s = readline(prompt);
		if (!s)
			(free_cmd(command), p_err("exit", 0), exit(0));
			
		//if (s[0] != '\0' && !(spaces(s))) //not needed ig
		add_history(s);
		if (ft_check(s))
			continue;
		ft_lexer(s, command);
		//expand_env(command, env_list); //need first to get the env list
	    if (!ft_pars(command))
			printf("I'am here\n");
			//*houssam call his funcs here
			

	//printing node content
	while (command->node)
	{
		printf("num %d is %s\n", i, command->node->content);
		i++;
		command->node = command->node->next;
	}
		//freeing and re init
		if (command->node)
			free_cmd(command);
		get_init(&command);
	}
}

int main(int ac, char **av, char **env)
{
	t_ms *cmd;
	t_env *env_list;

	if (ac != 1)
		exit(1);
	get_init(&cmd);
	ms_signal();
	inpute(cmd, env_list);
}   
	      
#include "minishell.h"
int status;

void ft_lexer(char *s, t_ms *command)
{
    int i;

    i = 0;
    ft_check(s);
    //while (s[i] == ' ' || s[i] == '\t')
        //i++;
    //pipe_split(s + i, command);
    while (s[i])
        i += ms_split(command, s + i);


}

void inpute(t_ms *command, t_env *env_list)
{
    char *s;

    while(1)
    {
        s = readline("minishell> ");
        if (!s)
            p_err("exit", 0);
        if (s[0] != '\0' && !(spaces(s)))
            add_history(s);
        ft_lexer(s, command);
        expand_env(command, env_list, status); //need first to get the env list

    int i = 0;
    while (command->node)
    {
        printf("num %d is %s\n", i, command->node->content);
        i++;
        command->node = command->node->next;
    }
    }
}

int main(int ac, char **av, char **env)
{
    t_ms *cmd;
    t_env *env_list;

    if (ac != 1)
        exit(1);
    cmd = (t_ms *)malloc(sizeof(t_ms));
    if (!cmd)
        p_err("Malloc error", 54);
    *cmd = (t_ms){ .node = NULL, .pcmd = NULL};
   // signals();
    inpute(cmd, env_list);
}
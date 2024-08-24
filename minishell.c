#include "minishell.h"

void free_list(t_list *node) {
    t_list *temp;
    while (node) {
        temp = node;
        node = node->next;
        if (temp->content)
            free(temp->content);
        free(temp);
    }
}

void free_pcmd(char **pcmd) {
    int i = 0;
    if (!pcmd)
        return;
    while (pcmd[i]) {
        free(pcmd[i]);
        i++;
    }
    free(pcmd);
}


void free_cmd(t_ms *cmd) {
    if (!cmd)
        return;
    if (cmd->node)
        free_list(cmd->node);
    if (cmd->pcmd)
        free_pcmd(cmd->pcmd);
    free(cmd);
}

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

void inpute(t_ms *command, char **env)
{
    char *s;
    t_env *env_list;
    t_env *export;

    fill_env(&env_list, env);
    fill_env(&export, env);
    export_sort(&export,env);
    while(1)
    {
        s = readline("minishell> ");
        if (!s)
            p_err("exit", 0);
        if (s[0] != '\0' && !(spaces(s)))
            add_history(s);
        ft_lexer(s, command);
        int i = 0;
            checking(command->node, env, command,env_list,export);
            free_cmd(command);
            command = (t_ms *)malloc(sizeof(t_ms));
            *command = (t_ms){ .node = NULL, .pcmd = NULL};
    }
}

int main(int ac, char **av, char **env)
{
    t_ms *cmd;

    if (ac != 1)
        exit(1);
    cmd = (t_ms *)malloc(sizeof(t_ms));
    if (!cmd)
        p_err("Malloc error", 54);
    *cmd = (t_ms){ .node = NULL, .pcmd = NULL};
   // signals();
    inpute(cmd,env);
}
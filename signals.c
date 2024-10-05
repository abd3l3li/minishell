#include "minishell.h"

extern int status;

//handler for child process

void    handler(int sig)
{
    (void)sig;
    write(0, "\n", 1);
    // rl_on_new_line();
    rl_replace_line("", 0);
    printf(BOLD CMAGENTA "Hamas" CCYAN "-shell" RESET "> ");
    status = 130;
}

void    chandler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    status = 130;
}
void    ms_signal(int num)
{
    if(!num)
    {
        signal(SIGINT, handler);
        signal(SIGQUIT, SIG_IGN);

    }
    else
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);

    }
}


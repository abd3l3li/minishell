#include "minishell.h"

extern int status;

void    handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();;
    status = 130;
}

void    ms_signal(void)
{
    signal(SIGINT, handler);
    signal(SIGQUIT, SIG_IGN);
}


#include "minishell.h"

extern int status;

//handler for child process

void    handler(int sig)
{
    (void)sig;
    rl_replace_line("", 0);
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
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
    struct sigaction	sig;

    if (!num)
        sig.sa_handler =  &handler;
    else
        sig.sa_handler =  &chandler;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sigaction(SIGINT, &sig, NULL);
    signal(SIGQUIT, SIG_IGN);

}


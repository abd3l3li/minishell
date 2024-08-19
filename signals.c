#include "minishell.h"

extern int status;

void    handler(int sig)
{
    (void)sig;
    rl_replace_line("", 0);
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
    status = 1;
}
void    ms_signal(void)
{
    struct sigaction	sig;

    sig.sa_handler =  &handler;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sigaction(SIGINT, &sig, NULL);
    signal(SIGQUIT, SIG_IGN);

}


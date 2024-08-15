#include "minishell.h"

int env_var(t_ms *command, char *s)
{
    int i;

    i = 0;
    if (s[i] == '$' && s[i + 1] == '\0' || s[i + 1] == 32)
    {
        ft_listadd_back(&(command->node), ft_listnew(s, 1, Word));
        i++;
        return (i);
    }
    i++;
    if(s[i] == '?' || (s[i] >= '0' && s[i] <= '9'))
        i++;
    else
        while(alphanum(s[i]) && s[i] != '\0')
            i++;
    ft_listadd_back(&(command->node), ft_listnew(s, i, E));
    return (i);
}

int ft_symbols(char c)
{
    return (c == 34 || c == 39 || c == '$' || c == '<'
                || c == '>' || c == '|' || c <= 32);
}

int next_q(char *s, int i, char c)
{
    while(s[i] && s[i] != c)
        i++;
    return (i);
}

int to_be_continue(t_ms *command, char *s, int i)
{
    if (s[i] == '>')
        if (s[i + 1] == '>')
        {
            ft_listadd_back(&(command->node), ft_listnew(s, 2, Rediracion_Out));
            i += 2;
        }
        else
        {
            ft_listadd_back(&(command->node), ft_listnew(s, 1, Rediracion_Out));
            i++;
        }
    else if (s[i] == '<')
    {
        if (s[i + 1] == '<')
        {
            ft_listadd_back(&(command->node), ft_listnew(s, 2, Here_doc));
            i += 2;
        }
        else
        {
            ft_listadd_back(&(command->node), ft_listnew(s, 1, Rediracion_In));
            i++;
        }
    }
    return (i);
}

int ms_split(t_ms *command, char *s)
{
    int i;

    i = 0;
    if (s[i] == 34 || s[i] == 39)
    {
        i += next_q(s, i + 1, s[i]);
        ft_listadd_back(&(command->node), ft_listnew(s + 1, i - 1, Word));
        i++;
    }
    else if (!ft_symbols(s[i]))
    {
        while (!ft_symbols(s[i]))
            i++;
        ft_listadd_back(&(command->node), ft_listnew(s, i, Word));
    }
    else if (s[i] == '|')
    {
        ft_listadd_back(&(command->node), ft_listnew(s, 1, Pipe));
        i++;
    }
    else if (s[i] == '$')
        if ((ft_symbols(s[i + 1]) || s[i + 1] == '=') &&
                (s[i + 1] != '\0' && s[i + 1] != 32))
        {
            ft_listadd_back(&(command->node), ft_listnew(s, 2, Word));
            i += 2;
        }
        else
            i += env_var(command, s + i);
    else if (s[i] == 32)
        i++;
    else
        i += to_be_continue(command, s, i);
    return (i);
}

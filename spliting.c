#include "minishell.h"

extern int status;

int env_var(t_ms *command, char *s)
{
    int i;

    i = 0;
    if (s[i] == '$' && s[i + 1] == '\0' || s[i + 1] == 32)
    {
        ft_lstadd_back(&(command->node), ft_lstnew(s, 1, Word));
        i++;
        return (i);
    }
    i++;
    if(s[i] == '?' || (s[i] >= '0' && s[i] <= '9'))
        i++;
    else
        while(s[i] != '\0' && !ft_symbols(s[i]))
            i++;
    ft_lstadd_back(&(command->node), ft_lstnew(s, i, Env));
    return (i);
}

int ft_symbols(char c)
{
    return (c == '$' || c == '<' || c == '>' || c == '|' || c == '\0');
}


int to_be_continue(t_ms *command, char *s, int i)
{
    if (s[i] == '>')
        if (s[i + 1] == '>')
        {
            ft_lstadd_back(&(command->node), ft_lstnew(s, 2, Rediracion_Out));
            i += 2;
        }
        else
        {
            ft_lstadd_back(&(command->node), ft_lstnew(s, 1, Rediracion_Out));
            i++;
        }
    else if (s[i] == '<')
    {
        if (s[i + 1] == '<')
        {
            ft_lstadd_back(&(command->node), ft_lstnew(s, 2, Here_doc));
            i += 2;
        }
        else
        {
            ft_lstadd_back(&(command->node), ft_lstnew(s, 1, Rediracion_In));
            i++;
        }
    }
    return (i);
}

int ms_split(t_ms *command, char *s)
{
    int i;

    i = 0;
    if (s[i] == ':' || s[i] == '!' || s[i] == '#')
    {
        if (s[i] == '!')
            status = 1;
        i++;
    }
    else if (s[i] == 32)
        i++;
    else if (!ft_symbols(s[i]))
    {
        while (!ft_symbols(s[i]))
            i++;
        ft_lstadd_back(&(command->node), ft_lstnew(s, i, Word));
    }
    else if (s[i] == '|')
    {
        ft_lstadd_back(&(command->node), ft_lstnew(s, 1, Pipe));
        i++;
    }
    else if (s[i] == '$')
    {
        if ((ft_symbols(s[i + 1]) || s[i + 1] == '=') &&
                (s[i + 1] != '\0' && s[i + 1] != 32))
        {
            ft_lstadd_back(&(command->node), ft_lstnew(s, 2, Word));
            i += 2;
        }
        else
            i += env_var(command, s + i);
    }
    else
        i += to_be_continue(command, s, i);
    return (i);
}

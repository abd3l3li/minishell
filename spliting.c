#include "minishell.h"

int env_var(t_ms *command, char *s)
{
    int i;

    i = 0;
    if (s[i] == '$' && s[i + 1] == '\0' || s[i + 1] == 32)
    {
        ft_lstadd_back(&(command->node), ft_lstnew(s, 1, W));
        i++;
        return (i);
    }
    i++;
    if(s[i] == '?' || (s[i] >= '0' && s[i] <= '9'))
        i++;
    else
        while(alphanum(s[i]) && s[i] != '\0')
            i++;
    ft_lstadd_back(&(command->node), ft_lstnew(s, i, E));
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
            ft_lstadd_back(&(command->node), ft_lstnew(s, 2, R_O));
            i += 2;
        }
        else
        {
            ft_lstadd_back(&(command->node), ft_lstnew(s, 1, R_O));
            i++;
        }
    else if (s[i] == '<')
        if (s[i + 1] == '<')
        {
            ft_lstadd_back(&(command->node), ft_lstnew(s, 2, H));
            i += 2;
        }
        else
        {
            ft_lstadd_back(&(command->node), ft_lstnew(s, 1, R_I));
            i++;
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
        ft_lstadd_back(&(command->node), ft_lstnew(s + 1, i - 1, W));
        i++;
    }
    else if (!ft_symbols(s[i]))
    {
        while (!ft_symbols(s[i]))
            i++;
        ft_lstadd_back(&(command->node), ft_lstnew(s, i, W));
    }
    else if (s[i] == '|')
    {
        ft_lstadd_back(&(command->node), ft_lstnew(s, 1, P));
        i++;
    }
    else if (s[i] == '$')
        if ((ft_symbols(s[i + 1]) || s[i + 1] == '=') &&
                (s[i + 1] != '\0' && s[i + 1] != 32))
        {
            ft_lstadd_back(&(command->node), ft_lstnew(s, 2, W));
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

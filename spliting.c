#include "minishell.h"

extern int status;

int env_var(t_ms *command, char *s)
{
    int i;
    int len;

    i = 0;
    len =  ft_strlen(s);
    if (s[i] == '$' && s[i + 1] == '\0' || s[i + 1] == 32 || empty_check(s + 1))
    {
        if (empty_check(s + 1))
            ft_listadd_back(&(command->node), ft_listnew("", 1, Env_word));
        else
            ft_listadd_back(&(command->node), ft_listnew(s, 1, Env_word));
        i++;
        return (i);
    }    
    i++;
    if(s[i] == '?' || (s[i] >= '0' && s[i] <= '9'))
        i++;
    else
        while(s[i] != '\0' && !ft_symbols(s[i]))
            i++;
    ft_listadd_back(&(command->node), ft_listnew(s, i, Env));
    return (i);
}

int ft_symbols(char c)
{
    return (c == '$' || c == '<' || c == '>' || c == '|' || c == '\0');
}


static int to_be_continue(t_ms *command, char *s, int i)
{
    if (s[i] == '>')
        if (s[i + 1] == '>')
        {
            ft_listadd_back(&(command->node), ft_listnew(s, 2, Rediracion_Out_Append));
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
int ft_var(t_ms *command, char *s, int i)
{
    if (ft_symbols(s[i + 1]) || s[i + 1] == '=' || s[i + 1] == 32)
    {
        ft_listadd_back(&(command->node), ft_listnew(s, 2, Env_word));
        i += 2;
    }
    else
        i += env_var(command, s + i);
    return (i);
}
int ms_split(t_ms *command, char *s)
{
    command->i = 0;
    if (s[command->i] == ':' || s[command->i] == '!' || s[command->i] == '#')
        status = (s[command->i++] == '!');
    else if (s[command->i] == 32 || s[command->i] == '|')
    {
        if (s[command->i] == '|')
            ft_listadd_back(&(command->node), ft_listnew(s, 1, Pipe));
        command->i++;
    }
    else if (!ft_symbols(s[command->i]))
    {
        while (!ft_symbols(s[command->i]))
            command->i++;
        ft_listadd_back(&(command->node), ft_listnew(s, command->i, Word));
    }
    else if (s[command->i] == '$')
        command->i += ft_var(command, s, command->i);
    else
        command->i += to_be_continue(command, s, command->i);
    return (command->i);
}

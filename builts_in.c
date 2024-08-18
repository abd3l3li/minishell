#include "minishell.h"

size_t	ascii_to_long(char *str)
{
    size_t    result;
    int		i;
    size_t  nbr;
    int     neg;

    nbr = LONG_MAX;
    nbr++;
    i = 0;
    neg = 1;
    if(str[0] == '-')
    {
        i = 1;
        neg = -1;
    }
    result = 0;
    while (str[i] && str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + str[i] - '0';
        i++;
    }
    if(neg == -1 && result > nbr)
            return (-1);
    else if(neg == 1 && result > LONG_MAX)
        return (-1);
    return (result * neg);
}

int print_env(t_env *env)
{
    while(env)
    {
       printf("%s=%s\n", env->name, env->value);
        env = env->next;
    }
    return (0);
}

t_env	*lstlast(t_env *lst)
{
    t_env *tmp;
	while (lst->next)
	{
        tmp = lst;
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (tmp);
}

void	lstadd_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (env)
	{
		if (*env == NULL)
			*env = new;
		else
		{
			tmp = lstlast(*env);
			tmp->next = new;
		}
	}
}

int index_of_char(const char *str, char ch)
{
    char *pos = ft_strchr(str, ch);
    if (pos != NULL)
        return pos - str;
    else
        return (-1); 
}

int fill_env(t_env **env, char **envp)
{

    int i;
    t_env *tmp;
    i = 0;
    *env = malloc(sizeof(t_env));
    tmp = *env;
    
    while(envp[i])
    {
        (*env)->name = ft_substr(envp[i], 0, index_of_char(envp[i], '='));
        (*env)->value = ft_substr(envp[i], index_of_char(envp[i], '=') + 1, ft_strlen(envp[i]) - index_of_char(envp[i], '='));
        (*env)->next = malloc(sizeof(t_env));
        (*env) = (*env)->next;
        i++;
    }
    (*env)->next = NULL;
    (*env) = tmp;
    return (0);
}

int export_sort(t_env **export,char **envp)
{
    t_env *tmp;
    t_env *tmp2;
    char *tmp_str;
    
    fill_env(export, envp);
    tmp = (*export);
    tmp2 = (*export);
    while(tmp->next)
    {
        tmp2 = tmp;
        while(tmp2->next)
        {
            if(ft_strncmp(tmp->name, tmp2->name, ft_strlen(tmp->name)) > 0)
            {
                tmp_str = tmp->name;
                tmp->name = tmp2->name;
                tmp2->name = tmp_str;
                tmp_str = tmp->value;
                tmp->value = tmp2->value;
                tmp2->value = tmp_str;
            }
            tmp2 = tmp2->next;
        }
        tmp = tmp->next;
    }
    return (0);
}

int free_tab(char **tab)
{
    int i;

    i = 0;
    while(tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
    return (0);
}

int pwd(t_exc *vars)
{
	printf("2222222222222222222\n");

    char *pwd;
    pwd = getcwd(NULL, 0);
    printf("%s\n", pwd);
    free(pwd);
    return (0);
}

int check_option(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == '-' && str[i + 1] == 'n')
        {
            i++;
            while(str[i])
            {
                if(str[i] != 'n')
                {
                    return (0);
                }
                i++;
            }
            return (1);
        }
        i++;
    }
    return (0);
}

int echo(t_exc *vars)
{
    int i;

    i = 0;
    if(check_option(vars->cmd_args[0]) == 1)
        i = 1;
    while (vars->cmd_args[i])
    {
        printf("%s", vars->cmd_args[i]);
    
        i++;
    }
    if(check_option(vars->cmd_args[0]) == 0)
        printf("\n");
    return (0);
}

int change_direrctory(t_exc *vars)
{
    printf("%s\n",vars->cmd_args[1]);
    if(vars->cmd_args[1] == NULL)
    {
        chdir(getenv("HOME\n"));
    }
    else
    {
        chdir(vars->cmd_args[1]);
    }
    return (0);
}

int ft_unset(t_env **env, char *str)
{
    t_env *tmp;

    tmp = (*env);
    if(ft_strncmp((*env)->name, str, ft_strlen(str)) == 0)
    {
        *env = (*env)->next;
        free(tmp->name);
        free(tmp->value);
        free(tmp);
        return (0);
    }
    while((*env)->next)
    {
        if(ft_strncmp((*env)->name, str, ft_strlen(str)) == 0)
        {
            tmp->next = (*env)->next;
            free((*env)->name);
            free((*env)->value);
            free(env);
            return (0);
        }
        tmp = (*env);
        (*env) = (*env)->next;
    }
    return (0);
} 

int export_adding(t_env *list, char *args)
{
    t_env *new;
    char **name_value;
    new = malloc(sizeof(t_env));
    if (args == NULL)
        return 0;
    name_value = ft_split(args, '=');
    new->name = name_value[0];
    new->value = name_value[1];
    new->next = NULL;
    lstadd_back(&list, new);
    return (0);
}

int ft_env(t_env *env)
{
    print_env(env);
    return (0);
}

int check_values(t_env *env,t_env *export, t_exc *vars)
{
    int i;

    i = 0;
    while(vars->cmd[i])
    {
        if(vars->cmd[i] == '=')
        {
            if(vars->cmd[i + 1] == '\0' && vars->cmd[i - 1] != ' ')
            {
                export_adding(env, vars->cmd);
                export_adding(export, vars->cmd);
                return (0);
            }
            else if(vars->cmd[i - 1] == ' ')
            {
                write(1, "bash: export: `=': not a valid identifier", 41);
                return (0);
            }
            else
            {
                export_adding(env, vars->cmd);
                export_adding(export, vars->cmd);
                return (0);
            }
        }
        i++;
    }
    export_adding(export, vars->cmd);
    return (0);
}

int ft_export(t_env *env,t_env *export, t_exc *vars)
{
    int i;
    i = 0;
     if(vars->cmd_args == NULL)\
        print_env(export);
         
    check_values(env,export,vars);
    return (0);
}

int ft_exit(t_exc *vars)
{
    char **cmd;
    int i;
    size_t num;
    int number_of_args;

    i = 0;
    number_of_args = 0;
    cmd = ft_split(vars->cmd, ' ');
    while(cmd[number_of_args])
        number_of_args++;    
    if(number_of_args > 2)
    {
        write(1, "bash: exit: too many arguments\n", 31);
        return (0);
    }
    if(cmd[1] != NULL)
    {
        num = ascii_to_long(cmd[1]);
        if(num == -1)
        {

            write(1, "bash: exit: ", 12);
            write(1, cmd[1], ft_strlen(cmd[1]));
            write(1, ": numeric argument required\n", 29);
            return (0);
        }
        else
        {
            free_tab(cmd);
            free_tab(vars->cmd_args);
            free(vars);
            exit(num);
        }
    }
    free_tab(cmd);
    free_tab(vars->cmd_args);
    free(vars);
    exit(num);
    return (0);
}


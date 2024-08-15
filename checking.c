#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((i < n) && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
		{
			return (-1);
		}
		else if (((unsigned char)s1[i] > (unsigned char)s2[i]))
			return (1);
		i++;
	}
	return (0);
}

int check_for_built_in(t_list *list,t_env *env, t_ms *ms, t_exc *vars, t_env *export)
{
    if (ft_strncmp(vars->cmd_args[0], "echo", 4) == 0)
        return(echo(vars));
    else if (ft_strncmp(vars->cmd_args[0], "pwd", 3) == 0)
        return(pwd(vars));
    else if (ft_strncmp(vars->cmd_args[0], "env", 3) == 0)
        return(ft_env(env));
    else if (ft_strncmp(vars->cmd_args[0], "export", 6) == 0)
        return(ft_export(env, export, vars));
    else if (ft_strncmp(vars->cmd_args[0], "unset", 5) == 0)
        return(ft_unset(&env, vars->cmd));
    else if (ft_strncmp(vars->cmd_args[0], "exit", 4) == 0)
        return(ft_exit(vars));
    return (1);
}
char    **getpaths(char **envp)
{
    int        i;
    char    **paths;
    int        check;

    check = 1;
    i = 0;
    while (envp[i] != NULL)
    {
        check = ft_strncmp(envp[i], "PATH", 4);
        if (check == 0)
            break ;
        i++;
    }
    if (check != 0)
        return (NULL);
    
    paths = ft_split(envp[i], ':');
    ft_memmove(&paths[0][0], &paths[0][5], ft_strlen(paths[0]) - 5);
    return (paths);
}

int checking(t_list *list, char **env, t_ms *ms)
{
    int i;
    t_exc vars;
    t_env *env_list;
    t_env *export;
    pid_t pid;

    fill_env(&env_list, env);
    fill_env(&export, env);
    export_sort(&export,env);
    vars.cmd_args = ft_split(list->content, ' ');
    if(!check_for_built_in(list, env_list, ms,&vars, export))
        return 0;
    printf("this shit should not be printed \n");
    vars.paths = getpaths(env);
    i = 0;
    if(!vars.paths)
    {
        printf("minishell: cmd not found\n");
        return 0;
    }
    while(list)
    {
    i = 0;
    while (vars.paths[i])
    {
        vars.tmp = ft_strjoin(vars.paths[i], "/");
        vars.cmd = ft_strjoin(vars.tmp, vars.cmd_args[0]);
            if (access(vars.cmd, X_OK) == 0)
            {
	            pid = fork();
	            if (pid == -1)
		            write(2, "Error\n", 6);
                
	            if (pid == 0)
		            execve(vars.cmd, vars.cmd_args, env);
            }
        i++;
        free(vars.cmd);
        free(vars.tmp);
    }
    list = list->next;
    }
    return 0;
}





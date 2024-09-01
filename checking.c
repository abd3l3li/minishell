#include "minishell.h"


int	ft_strfind(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return (1);
		i--;
	}
	return (-1);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	tab = NULL;
}

void	error(int i)
{
	if (i == 1)
	{
		write(2, "Insufficient Arguments Provided, Please Try Again\n", 50);
		exit(EXIT_FAILURE);
	}
	if (i == 2)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if (i == 3)
	{
		write(2, "Error: Permission Denied or Invalid Command\n", 45);
		exit(127);
	}
}
char	*handl_path(char *cmd)
{
	t_cmd_Vars	var;

	var.splited_cmd = ft_split(cmd, ' ');
	var.result = access(var.splited_cmd[0], X_OK);
	if (var.result == 0)
	{
		ft_free_tab(var.splited_cmd);
		return (cmd);
	}
	ft_free_tab(var.splited_cmd);
	return (0);
}
char	*find_path(char *cmd, char **envp)
{
	t_cmd_Vars	var;

	var.result = ft_strfind(cmd, '/');
	if (var.result == 1)
		return (handl_path(cmd));
	var.paths = getpaths(envp);
	if (!var.paths)
		return (NULL);
	var.i = 0;
	while (var.paths[var.i])
	{
		var.part_path = ft_strjoin(var.paths[var.i], "/");
		var.path = ft_strjoin(var.part_path, cmd);
		free(var.part_path);
		if (access(var.path, F_OK) == 0)
		{
			return (var.path);
		}
		free(var.path);
		var.i++;
	}
	var.i = -1;
	ft_free_tab(var.paths);
	return (0);
}
void	execute(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error(3);
	}
	execve(path, cmd, envp);
}

void	child_process(t_list *list, char **envp, t_exc *var)
{
	int	fd;
	char *str;
	int check;
	char *str2;

	if (pipe(var->fd) == -1)
		error(2);
	var->pid = fork();
	if (var->pid == -1)
		error(2);
	if (var->pid == 0)
	{
		if(list->next->type == Rediracion_Out)
		{
			var->file = list->next->next->content;
			fd = open(var->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			dup2(fd, 1);
			close(fd);
			execute(list->content, envp);
		}
		else if(list->next->type == Rediracion_In)
		{
			var->file = list->next->next->content;
			fd = open(var->file, O_RDONLY, 0666);
			if(fd == -1)
			{
				write(2, var->file, ft_strlen(var->file));
				write(2, ": No such file or directory\n", 28);
				exit(1);
			}
			dup2(fd, 0);
			close(fd);
			execute(list->content, envp);
		}
		else if(list->next->type == Rediracion_Out_Append)
		{
			var->file = list->next->next->content;
			fd = open(var->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
			dup2(fd, 1);
			close(fd);
			execute(list->content, envp);
		}
		else if(list->next->type == Here_doc)
		{
			printf("Here_doc\n");
			fd = open("/proc/uptime", O_RDONLY , 0644);
			str = get_next_line(fd);
			str = ft_strjoin("/tmp/", str);
			close(fd);
			fd = open(str, O_CREAT | O_RDWR | O_APPEND, 777);
			str2 = strdup(str);
			free(str);
			while(1)
			{
				str = get_next_line(0);
				write(fd, str, ft_strlen(str));
				if(ft_strncmp(str, var->file, ft_strlen(var->file)) == 0)
				{
					close(fd);

					fd = open(str2, O_RDONLY);
					while(1)
					{	
						str = get_next_line(fd);
						if(!str)
							break;
						write(1, str, ft_strlen(str));
					}
					unlink(str2);
					break;
				}
			}
		}
		else if (list->next->type == Pipe)
		{
			close(var->fd[0]);
			dup2(var->fd[1], 1);
			execute(list->content, envp);
		}
		else
			execute(list->content, envp);
	}
	else
	{
		close(var->fd[1]);
		dup2(var->fd[0], 0);
		close(var->fd[0]);
	}
	ms_signal(1);
}

static void	last_child(char *argv, char **envp, int type, t_exc *var)
{
	char	**cmd;
	int		i;
	char	*path;
	pid_t	pid;
	int		fd;
	char *str;
	ssize_t check;
	char *str2;

	pid = fork();
	if (pid == 0)
	{
		if(type == Rediracion_Out)
		{
			fd = open(var->file, O_CREAT | O_WRONLY | O_TRUNC, 777);
			dup2(fd, 1);
			close(fd);
			execute(argv, envp);
		}
		else if(type == Rediracion_In)
		{
		fd = open(var->file, O_RDONLY);
		dup2(fd, 0);
		close(fd);
		execute(argv, envp);
		}
		else if(type == Here_doc)
		{
			fd = open("/proc/uptime", O_RDONLY , 0644);
			str = get_next_line(fd);
			str = ft_strjoin("/tmp/", str);
			close(fd);
			fd = open(str, O_CREAT | O_RDWR | O_APPEND, 777);
			str2 = strdup(str);
			free(str);
			while(1)
			{
				str = get_next_line(0);
				write(fd, str, ft_strlen(str));
				if(ft_strncmp(str, var->file, ft_strlen(var->file)) == 0)
				{
					close(fd);
					fd = open(str2, O_RDONLY);
					while(1)
					{	
						str = get_next_line(fd);
						if(!str)
							break;
						write(1, str, ft_strlen(str));
					}
					unlink(str2);
					break;
				}
			}
		}
		i = -1;
		cmd = ft_split(argv, ' ');
		path = find_path(cmd[0], envp);
		if (!path)
		{
			while (cmd[++i])
				free(cmd[i]);
			free(cmd);
			error(3);
		}
		execve(path, cmd, envp);
	}
	ms_signal(1);
}

void free_t_exc(t_exc *exc)
{
    if (exc->paths)
    {
        char **p = exc->paths;
        while (*p)
        {
            free(*p);
            p++;
        }
        free(exc->paths);
    }
    if (exc->cmd_args)
    {
        char **p = exc->cmd_args;
        while (*p)
        {
            free(*p);
            p++;
        }
        free(exc->cmd_args);
    }
    free(exc);
}

int check_for_built_in(t_list *list,t_env *env, t_ms *ms, t_exc *vars, t_env *export)
{
	vars->cmd_args = ft_split(list->content, ' ');
    if (ft_strncmp(vars->cmd_args[0], "echo", 4) == 0)
        return(echo(vars));
    else if (ft_strncmp(vars->cmd_args[0], "pwd", 3) == 0)
        return(pwd(vars));
    else if (ft_strncmp(vars->cmd_args[0], "env", 3) == 0)
        return(ft_env(env));
    else if (ft_strncmp(vars->cmd_args[0], "export", 6) == 0)
        return(ft_export(env, export, vars));
    else if (ft_strncmp(vars->cmd_args[0], "unset", 5) == 0)
        return(ft_unset(&env, vars->cmd_args[1]));
    else if (ft_strncmp(vars->cmd_args[0], "exit", 4) == 0)
        return(ft_exit(vars));
	else if (ft_strncmp(vars->cmd_args[0], "cd", 2) == 0)
		return(ft_cd(vars));
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

int checking(t_list *list, char **env, t_ms *ms, t_env *env_list, t_env *export)
{
	int saved_stdin = dup(STDIN_FILENO);
	int saved_stdout = dup(STDOUT_FILENO);
    int i;
    t_exc *vars;
    pid_t pid;
	t_list *tmp = list;

	if(!list)
		return (0); //abel-baz
    vars = malloc(sizeof(t_exc));
    while(list->next)
    {
		if(!check_for_built_in(list, env_list, ms,vars, export))
			return 0;
		child_process(list, env, vars);
       // free_t_exc(vars);
        //vars = malloc(sizeof(t_exc));
		tmp = list->next;
        list = list->next->next;
    }
	if(!check_for_built_in(list, env_list, ms,vars, export))
		return 0;
	 if(tmp->type == Pipe || tmp->type == Word) 
	 	last_child(list->content, env, ms->node->type, vars);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
	while(wait(NULL) != -1)
	{
	}
    return 0;
}

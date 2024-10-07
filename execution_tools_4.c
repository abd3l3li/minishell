
#include "minishell.h"

char *handl_path(char *cmd)
{
    t_cmd_Vars var;
    var.splited_cmd = ft_split(cmd, ' ');
    
    if (access(var.splited_cmd[0], F_OK) == 0)
    {
        if (access(var.splited_cmd[0], X_OK) == 0)
        {
            ft_free_tab(var.splited_cmd);
            return (cmd);
        }
        else
        {
            put_str_fd(var.splited_cmd[0], 2);
            put_str_fd(": Permission denied\n", 2);
            status = 126;
            ft_free_tab(var.splited_cmd);
            return (0);
        }
    }
    else
    {
        put_str_fd(var.splited_cmd[0], 2);
        put_str_fd(": No such file or directory\n", 2);
        status = 127;
        ft_free_tab(var.splited_cmd);
        return (0);
    }
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
		ft_free(var.part_path);
		if (access(var.path, F_OK) == 0)
		{
			return (var.path);
		}
		ft_free(var.path);
		var.i++;
	}
	var.i = -1;
	ft_free_tab(var.paths);
	return (0);
}


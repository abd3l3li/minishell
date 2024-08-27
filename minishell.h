# ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>


# define BUFFER_SIZE 10
# define Word 0
# define Pipe 1
# define Singl_Quot 2
# define Double_Quot 3
# define Rediracion_In 4
# define Rediracion_Out 5
# define E 6
# define Here_doc 7
# define Rediracion_Out_Append 8


typedef struct s_list
{
	char			*content;
	struct s_list	*next;
    int             type;
}	t_list;


typedef struct s_ms
{
    t_list *node;
    char **pcmd;
} t_ms;

typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_cmd_vars
{
	int		i;
	char	*path;
	char	*fullpath;
	char	**splited_cmd;
	int		result;
	char	**paths;
	char	*part_path;
}	t_cmd_Vars;

typedef struct s_exc
{
    char **paths;
    char *tmp;
    char *cmd;
    char **cmd_args;
    int fd[2];
    char *file;
    pid_t pid;

} t_exc;

typedef struct s_glist
{
	char			*content;
	struct s_glist	*next;
}	t_glist;

t_glist	*ft_lstglast(t_glist *lst);
char	*trim_last_list_chars_helper(t_glist *last, int i);
bool	found_new_line(t_glist *list);
void	free_glist(t_glist *list);
char	*get_next_line(int fd);
void	generate_line(char **line, t_glist *list);
void    ft_check(char *s);
void	*ft_memcpy(void *dest, const void *src, int n);
char	*ft_substr(char const *s, unsigned int start, int len);
size_t	ft_strlen(const char *s);
void    ft_lexer(char *s, t_ms *command);
void    inpute(t_ms *command, char **env);
int     next_q(char *s, int i, char c);
void    p_err(char *str, int n);
int     spaces(char *s);
int     check_q(char *s);
int     count_q(char *s, char c);
int     double_p(char *s);
int     ft_symbols(char c);
int     ms_split(t_ms *command, char *s);
char	**ft_split(char const *s, char c);
t_list	*ft_listnew(char *content, int len, int type);
void	ft_listadd_back(t_list **lst, t_list *new);
int     env_var(t_ms *command, char *s);
int     alphanum(char c);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
int     echo(t_exc *vars);
int     pwd(t_exc *vars);
int     ft_env(t_env *env);
int     ft_export(t_env *env,t_env *export, t_exc *vars);
int     ft_unset(t_env **env, char *str);
int     ft_exit(t_exc *vars);
int     fill_env(t_env **env, char **envp);
int     export_sort(t_env **export,char **envp);
int     checking(t_list *list, char **env, t_ms *ms, t_env *env_list, t_env *export);
size_t  ascii_to_long(char *str);
char	*ft_strchr(char const *str, int c);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char    **getpaths(char **envp);
int     ft_print_env(t_env *env);
t_env	*ft_lstlast(t_env *lst);
int     ft_cd(t_exc *vars);
char	*ft_strdup(const char *s);
#endif
#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

# define Word 0
# define Pipe 1
# define Singl_Quot 2
# define Double_Quot 3
# define Rediracion_In 4
# define Rediracion_Out 5
# define E 6
# define Here_doc 7

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

typedef struct s_exc
{
    char **paths;
    char *tmp;
    char *cmd;
    char **cmd_args;
    t_env *env;
} t_exc;


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
int     checking(t_list *list, char **env, t_ms *ms);
size_t  ascii_to_long(char *str);
char	*ft_strchr(char const *str, int c);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
#endif
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define Word 0
# define Pipe 1
# define Singl_Quot 2
# define Double_Quot 3
# define Rediracion_In 4
# define Rediracion_Out 5
# define Env 6
# define Here_doc 7

# define CMAGENTA   "\x1B[35m"
# define CCYAN     "\x1B[36m"    
# define BOLD      "\x1B[1m"
# define RESET     "\x1B[0m"

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
    int             type;
}	t_list;

typedef struct s_ms
{
    t_list  *node;
}   t_ms;

typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *next;
} t_env;


void    get_init(t_ms **cmd);
int     ft_check(char *s);
void	*ft_memcpy(void *dest, const void *src, int n);
char	*ft_substr(char const *s, unsigned int start, int len);
int     ft_strlen(const char *str);
void    ft_lexer(char *s, t_ms *command);
void    inpute(t_ms *command, t_env *env_list);
int     next_q(char *s, int i, char c);
void    p_err(char *str, int n);
int     spaces(char *s);
int     check_q(char *s);
int     count_q(char *s, char c);
int     double_p(char *s);
int     ft_symbols(char c);
int     ms_split(t_ms *command, char *s);
t_list	*ft_lstnew(char *content, int len, int type);
void	ft_lstadd_back(t_list **lst, t_list *new);
int     env_var(t_ms *command, char *s);
int     alphanum(char c);
void    expand_env(t_ms *command, t_env *env_list);
char	*ft_strdup(const char *src);
int     ft_isdigit(int i);
int     ft_strnotcmp(const char *s1, const char *s2, int n);
int     ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_itoa(int n);
void    free_cmd(t_ms *cmd);
void    ms_signal(void);
int     ft_pars(t_ms *cmd);
void    ft_skip_q(t_ms *cmd);
int     ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
void    ft_merge(t_ms *cmd);

#endif
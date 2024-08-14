#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define W 0
# define P 1
# define S_Q 2
# define D_Q 3
# define R_I 4
# define R_O 5
# define E 6
# define H 7

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
    int             type;
}	t_list;

typedef struct s_ms
{
    t_list  *node;
    char    **pcmd;
}   t_ms;

typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *next;
} t_env;


void    ft_check(char *s);
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
void    expand_env(t_ms *command, t_env *env_list, int status);
char	*ft_strdup(const char *src);
int     ft_isdigit(int i);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_itoa(int n);


#endif
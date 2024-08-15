#ifndef MS_H
# define MS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

# define W 0
# define P 1
# define Q 2
# define R 3

typedef struct s_lst
{
    char            *cmd;
    struct s_lst    *next;
    int type;
}    t_lst;

typedef struct s_ms
{
    t_lst *node;
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

#endif 
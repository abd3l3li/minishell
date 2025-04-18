/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: her-rehy <her-rehy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:14:26 by her-rehy          #+#    #+#             */
/*   Updated: 2024/10/15 18:41:57 by her-rehy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*libraries section*/

# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

/*definitions section*/

# define WORD 0
# define PIPE 1
# define REDIRACTION_IN 2
# define REDIRACTION_OUT 3
# define ENV 4
# define HERE_DOC 5
# define REDIRACTION_OUT_APPEND 6
# define ENV_WORD 7
# define QUOTED 9
# define BUFFER_SIZE 8

# define CMAGENTA "\001\x1B[35m\002"
# define CCYAN "\001\x1B[36m\002"
# define BOLD "\001\x1B[1m\002"
# define RESET "\001\x1B[0m\002"

extern int				g_status;

/*structs section*/

typedef struct s_exc
{
	char				**paths;
	char				*builtin_tmp;
	char				*tmp;
	char				*cmd;
	char				**cmd_args;
	int					fd[2];
	char				*file;
	pid_t				pid;
	char				*oldpwd;
	int					saved_stdin;
	int					saved_stdout;
	int					i;
	int					redirection_check;
}						t_exc;

typedef struct s_list
{
	char				*content;
	struct s_list		*next;
	int					type;
}						t_list;

typedef struct s_garbage
{
	char				*content;
	struct s_garbage	*next;
	int					freed;
}						t_garbage;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_ms
{
	t_list				*node;
	t_list				*tmp;
	t_list				*pre_last;
	t_list				*exc_tmp;
	char				*name;
	char				*value;
	char				*s;
	char				*tmp_s;
	t_env				*env_list;
	t_env				*export;
	t_env				*tmp_env;
	const char			*prompt;
	int					i;
	int					done;
	t_exc				*vars;
}						t_ms;

typedef struct s_child
{
	t_list				*tmp;
	char				*expanded;
	t_env				*env_list;
	t_env				*export;
	int					fd;
}						t_child;

typedef struct s_cmd_vars
{
	int					i;
	char				*path;
	char				*fullpath;
	char				**splited_cmd;
	int					result;
	char				**paths;
	char				*part_path;
}						t_cmd_Vars;

typedef struct s_last_child
{
	char				**cmd;
	int					i;
	char				*path;
	pid_t				pid;
	int					fd;
	char				*str;
	ssize_t				check;
	char				*str2;
}						t_last_child;

typedef struct s_glist
{
	char				*content;
	struct s_glist		*next;
}						t_glist;

/*prototype section*/

t_glist					*ft_lstglast(t_glist *lst);
int						set_status(t_list *list, char **env, t_list *tmp);
char					*trim_last_list_chars_helper(t_glist *last, int i);
bool					found_new_line(t_glist *list);
void					*handle_error(char **splited_cmd, int flag);
int						list_size(t_env *list);
int						is_built_in(char *cmd);
char					**list_to_array(t_env *list);
char					*ft_strncpy(char *dest, const char *src, size_t n);
int						ft_strfind(const char *s, int c);
void					free_glist(t_glist *list);
char					*find_env_value(const char *name, t_env *env_list);
char					*get_next_line(int fd);
void					ft_free_tab(char **tab);
char					*extract_after_dollar(char *str);
void					generate_line(char **line, t_glist *list);
void					error(int i);
char					*remove_qoute(char *str);
char					*ft_strnstr(char *s1, char *s2);
int						ft_isspace(char c);
int						ft_isdigit(int i);
void					get_init(t_ms **cmd);
int						ft_check(char *s);
void					handler(int sig);
void					*ft_memcpy(void *dest, const void *src, int n);
char					*ft_substr(char const *s, unsigned int start, int len);
int						ft_strlen(const char *s);
void					ft_lexer(char *s, t_ms *command);
void					input(t_ms *command, char **env);
void					p_err(char *str, int n);
int						check_q(char *s);
int						change_to_home(void);
int						double_p(char *s);
int						ft_symbols(char c);
int						ms_split(t_ms *command, char *s);
char					**ft_split(char const *s, char c);
t_list					*ft_listnew(char *content, int len, int type);
t_garbage				*ft_lstnew_plus(void *content);
void					ft_listadd_back(t_list **lst, t_list *new);
int						env_var(t_ms *command, char *s);
int						ft_strnotcmp(const char *s1, const char *s2, int n);
int						ft_strncmp(const char *s1, const char *s2, int n);
int						echo(t_exc *vars);
int						ft_env(t_env *env);
int						ft_export(t_env *env, t_env *export, t_exc *vars);
int						ft_unset(t_env **env, char *str);
int						ft_exit(t_exc *vars);
int						fill_env(t_env **env, char **envp);
int						export_sort(t_env **export);
char					*checking(char **env, t_ms *ms);
char					*ft_strchr(char const *str, int c);
void					*ft_memmove(void *dest, const void *src, size_t n);
char					**getpaths(char **envp);
char					*find_path(char *cmd, char **envp);
int						ft_print_env(t_env *env);
t_env					*ft_lstlast(t_env *lst);
int						ft_cd(t_exc *vars, t_env *env, t_env *export);
int						check_values(t_env *env, t_env *export, t_exc *vars);
int						compare_list(const char *str, t_env *env_list);
int						ft_export(t_env *env, t_env *export, t_exc *vars);
int						validate_exit_args(t_exc *vars);
int						export_adding(t_env *list, char *args);
void					update_env_var(t_env *env, char *name, char *new_value);
int						handle_numeric_argument(t_exc *vars);
int						ft_env(t_env *env);
char					ft_tolower(char c);
void					lstadd_back(t_env **env, t_env *new);
int						echo(t_exc *vars);
int						ft_unset(t_env **env, char *str);
int						pwd(void);
int						unset_first(t_env **env, char *str, char **name_value);
int						check_option(char **str, int *check);
int						free_tab(char **tab);
int						index_of_char(const char *str, char ch);
int						compare_strings_ignore_case(const char *str1,
							const char *str2);
int						export_sort(t_env **export);
int						fill_env(t_env **env, char **envp);
char					*find_first( char	*str, char ch1, char ch2);
void					ms_signal(void);
int						ft_pars(t_ms *cmd);
void					ft_skip_q(t_ms *cmd);
char					*handl_path(char *cmd);
char					*ft_strjoin(char *s1, char *s2);
void					ft_merge(t_ms *cmd);
void					free_cmd(t_ms *cmd);
void					expand_env(t_ms *command, t_env *env_list);
char					*ft_strjoin(char *s1, char *s2);
char					*ft_strdup(char *src);
char					*ft_itoa(int n);
int						check_for_built_in(t_list *list, t_env *env,
							t_exc *vars, t_env *export);
int						ft_strcmp(const char *str1, const char *str2);
void					free_t_exc(t_exc *exc);
void					last_child(t_list *list, char **envp, t_exc *var,
							t_ms *ms);
void					execute(char *argv, char **envp);
size_t					ft_strlcpy(char *dest, const char *src, size_t size);
int						count_here_doc(t_list *list);
int						ascii_to_long(char *str);
int						ft_print_env(t_env *env);
void					handle_pipe_redirection(t_list **list, t_exc *var);
void					handle_pipe_creation(t_exc *var);
void					handle_output_redirection(t_list **list, t_exc *var,
							int *fd);
void					handle_output_append_redirection(t_list **list,
							t_exc *var, int *fd);
void					handle_last_redirection(t_list *pre_last, t_exc *var);
void					setup_redirections(t_ms *ms, t_child **child);
void					handle_redirection_out(t_child *child, t_exc *var,
							char **envp);
void					handle_redirection_in(t_list **list, t_exc *var,
							t_child *child, char **envp);
void					handle_heredoc_loop(int fd, char *file, char *str2,
							t_child *child);
void					handle_here_doc(t_list **list, t_exc *var, char **envp,
							t_child *child);
void					ft_strcpy(char *dst, const char *src);
void					handle_pipe(t_list **list, t_exc *var, t_child *child,
							char **envp);
void					handle_word(t_list **list, char **envp);
void					execute_child_process(t_ms *ms, char **envp,
							t_list *pre_last_list, t_child *child);
int						handle_built_in_commands(t_exc *var, t_env *env_list,
							t_env *export);
void					initialize_execution(t_exc *exc, char ***env, t_ms *ms);
void					protecting_executing(t_list *tmp, char **env, t_ms *ms,
							t_exc *vars);
int						empty_check(char *s);
char					*ft_strtrim(char *s1, char const *set);
int						put_str_fd(char *str, int fd);
void					*ft_malloc(size_t len);
char					**create_own_env(void);
void					ft_exitt(int n);
void					ft_free(void *ptr);
void					ft_listadd_back_plus(t_garbage **lst, t_garbage *new);
void					ft_remove_spaces(t_ms *command);
int						valid_cmd(t_ms *cmd);
int						ft_more_parse(t_ms *cmd);
int						ft_quoted(t_ms *command, char *s, int i);
void					ft_merge_quoted(t_ms *cmd);
void					ft_prev(t_list **tmp, t_list *prev);
void					ft_next(t_list *tmp);
void					ft_check_env(t_ms	*command);

#endif
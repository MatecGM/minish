/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:02:32 by fparis            #+#    #+#             */
/*   Updated: 2024/07/01 18:08:06 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>

extern sig_atomic_t	g_signal;

typedef enum e_type
{
	tnull = 0,
	tpipe,
	tinfile,
	toutfile,
	theredoc,
	tappend,
}	t_type;

typedef enum e_quote
{
	NO_QUOTE,
	SINGLE,
	DOUBLE,
}	t_quote;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_divpipe
{
	char				**cmd;
	char				*cmd_path;
	struct s_redirect	*redirect;
	struct s_divpipe	*next;
	int					child_pid;
}	t_divpipe;

typedef struct s_redirect
{
	t_type				type;
	char				*arg;
	char				*heredoc_name;
	t_bool				quote;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_minish
{
	char		**env;
	char		*to_free;
	t_divpipe	*divpipe;
	int			exit_status;
	int			in_pipe;
	t_bool		synt_err;
}	t_minish;

void		ft_envdelone(t_env *env, void (*del)(void *));
int			get_env_index(char **env, char *name);
char		**dup_env_tab(char **old_env);
char		*get_env_value(char **env_var, char *name);
void		print_error(char *str1, char *str2, char *str3);
void		remove_var(t_minish *minish, char *name);
void		add_var(t_minish *minish, char *env_var);
void		print_error(char *str1, char *str2, char *str3);
void		ft_echo(char **tab, t_minish *minish, int fd);
void		ft_cd(char **tab, t_minish *minish, int fd);
void		ft_pwd(char **tab, t_minish *minish, int fd);
void		ft_unset(char **tab, t_minish *minish);
void		ft_env(char **tab, char **env, t_minish *minish, int fd);
void		ft_export(char **tab, t_minish *minish, int fd);
int			init_signal_handler(void);
int			interactive_mode(t_bool to_change, int new_value);
int			is_good_env(char *env_var);
void		append_var(t_minish *minish, char *env_var);
void		ft_exit(char **tab, t_minish *minish);
size_t		get_name_len(char *env_var);
t_divpipe	*ft_parsing(char *input, t_minish *minish);
char		**ft_split_quote(char *str);
char		**ft_tokenizer(char *str);
t_bool		ft_quote_first_arg(char *str);
char		*extender(char *str, t_minish *minish, t_bool onheredock);
t_bool		ft_hasdollars(char *str);
t_divpipe	*ft_pipenew(void);
void		ft_pipeadd_back(t_divpipe **l, t_divpipe *new);
t_redirect	*ft_rednew(t_type type, char *arg);
void		ft_redadd_back(t_redirect **red, t_redirect *new);
char		*put_paths(t_divpipe *divpipe, char **env);
t_divpipe	*executer(t_divpipe	*divpipe, t_minish *minish, int *fd);
int			is_builtin(char	*cmd);
char		*create_heredoc(char *heredoc_EOF,
				t_minish *minish, t_redirect *red);
void		ft_redirection(t_redirect *red, int *fd, t_minish *minish);
void		ft_freered(t_redirect *redirect);
void		ft_free_pipe(t_divpipe *pipe);
void		exit_free(t_minish *minish, int exit_code);
void		update_underscore(t_minish *minish);
void		update_pwd(t_minish *minish, char *name);
void		update_shlvl(t_minish *minish);
void		cd_home(t_minish *minish);
void		default_cd(char **tab, t_minish *minish);
void		cd_back(t_minish *minish, int fd);
int			check_signal(t_minish *minish);
void		manage_static_minish(t_minish *to_set);
void		signal_heredoc(int signal);
void		manage_static_minish(t_minish *to_set);
void		signal_heredoc(int signal);
void		ft_execpipes(t_divpipe	*divpipe, t_minish *minish);
void		wait_all_pipe(t_minish *minish);
void		unlink_all_heredoc(t_minish *minish);
void		exit_free_fork(t_minish *minish, int exit_code);
void		close_all_fd(void);
int			get_good_fd(int pipread, int fd[2], int pip[2], t_divpipe *divpipe);
char		*ft_chardup(char c, int i);
t_bool		ft_strisspace(char *str);
void		ft_syntax_checker(char **toked, t_minish *minish);
char		**check_splitquote_str(char *str);
t_bool		ft_ambiguous_checker(char *str);
t_bool		ft_hasspace(char *str);
void		get_exit_status(int new_value, t_minish *minish);
t_bool		ft_hasdollars(char *str);
t_type		typage(char *elem);

#endif

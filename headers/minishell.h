/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:02:32 by fparis            #+#    #+#             */
/*   Updated: 2024/06/04 22:18:48 by fparis           ###   ########.fr       */
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

typedef enum	e_type
{
	tnull = 0,
	tpipe,
	theredoc,
	tinfile,
	toutfile,
	tappend,
}	t_type;

typedef enum	e_quote
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

typedef struct	s_divpipe
{
	char				**cmd;
	char				*cmd_path;
	struct s_redirect	*redirect;
	struct s_divpipe	*next;
}	t_divpipe;

typedef struct	s_redirect
{
	t_type				type;
	char				*arg;
	t_bool				quote;
	struct s_redirect	*next;
}	t_redirect;

typedef struct	s_minish
{
	char		**env;
	t_divpipe	*divpipe;
	int			exit_status;
}	t_minish;

void	ft_envdelone(t_env *env, void (*del)(void *));
int		get_env_index(char **env, char *name);
char	**dup_env_tab(char **old_env);
char	*get_env_value(char **env_var, char *name);
void	print_error(char *str1, char *str2, char *str3);
void	remove_var(t_minish *minish, char *name);
void	add_var(t_minish *minish, char *env_var);
void	print_error(char *str1, char *str2, char *str3);
void	ft_echo(char **tab);
void	ft_cd(char **tab);
void	ft_pwd(char **tab);
void	ft_unset(char **tab, t_minish *minish);
void	ft_env(char **tab, char **env);
void	ft_export(char **tab, t_minish *minish);
int		init_signal_handler();
int		get_current_signal();
int		interactive_mode(t_bool to_change, int new_value);
int		is_good_env(char *env_var);
void	append_var(t_minish *minish, char *env_var);
void	ft_exit(char **tab, t_minish *minish);

t_divpipe	*ft_parsing(char *input, char **env);
char		**ft_split_quote(char *str);
char		**ft_tokenizer(char *str);
t_bool		ft_quote_first_arg(char *str);
char		*extender(char *str, char **env);
t_bool		ft_hasdollars(char *str);

t_divpipe	*ft_pipenew(void);
void		ft_pipeadd_back(t_divpipe **l, t_divpipe *new);
t_redirect	*ft_rednew(t_type type, char *arg);
void		ft_redadd_back(t_redirect **red, t_redirect *new);

char		*put_paths(t_divpipe *divpipe, char **env);
t_divpipe	*executer(t_divpipe	*divpipe, t_minish *minish);
int			is_builtin(char	*cmd);
char		*create_heredoc(char *heredoc_EOF);

void	ft_freered(t_redirect *redirect);
void	ft_free_pipe(t_divpipe *pipe);
void	exit_free(t_minish *minish, int exit_code);

#endif

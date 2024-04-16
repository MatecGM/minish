/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:02:32 by fparis            #+#    #+#             */
/*   Updated: 2024/04/16 20:34:11 by fparis           ###   ########.fr       */
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

typedef enum	s_type
{
	tfirst,
	tpipe,
	theredoc,
	tinfile,
	toutfile,
	tappend,
	tcommand,
}	t_type;

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
	struct s_redirect	*next;
}	t_redirect;

char	**ft_split_quote(char *str);
void	ft_envdelone(t_env *env, void (*del)(void *));
char	**ft_tokenizer(char *str);
int		get_env_index(char **env, char *name);
char	**dup_env_tab(char **old_env);
char	*get_env_value(char **env_var, char *name);
void	print_error(char *str1, char *str2, char *str3);

#endif

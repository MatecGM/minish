/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:02:32 by fparis            #+#    #+#             */
/*   Updated: 2024/04/09 19:25:31 by mbico            ###   ########.fr       */
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
	syntax_error = -1,
	pipe,
	heredoc,
	app,
	infile,
	outfile,
	command,
}	t_type;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

char	**ft_split_quote(char *str);
void	ft_envdelone(t_env *env, void (*del)(void *));
char	**ft_tokenizer(char *str);

#endif

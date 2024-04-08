/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:02:32 by fparis            #+#    #+#             */
/*   Updated: 2024/04/08 16:36:04 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/headers/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef enum s_bool
{
	ERROR = -1,
	FALSE,
	TRUE,
}			t_bool;

typedef enum	s_type
{
	syntax_error = -1,
	separator,
	command,
	parameter,
}	t_type;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

char	**ft_split_quote(char *str);
void	ft_envdelone(t_env *env, void (*del)(void *));

#endif

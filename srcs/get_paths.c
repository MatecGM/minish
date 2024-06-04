/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 18:14:11 by fparis            #+#    #+#             */
/*   Updated: 2024/06/04 21:48:15 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_splitted_paths(char **env)
{
	char	*env_path;
	char	**splitted;

	env_path = get_env_value(env, "PATH");
	if (!env_path)
		return (NULL);
	splitted = ft_split(env_path, ':');
	free(env_path);
	if (!splitted)
		return (NULL);
	return (splitted);
}

char	**get_paths(char **env)
{
	char	**splitted;
	char	**paths;
	int		i;

	splitted = get_splitted_paths(env);
	if (!splitted)
		return (NULL);
	paths = ft_calloc(ft_strtablen(splitted) + 1, sizeof(char *));
	i = 0;
	while (splitted[i])
	{
		paths[i] = ft_strjoin(splitted[i], "/");
		if (!paths[i])
		{
			ft_free_tab(splitted);
			ft_free_tab(paths);
		}
		i++;
	}
	ft_free_tab(splitted);
	return (paths);
}

void	set_path_to_base_cmd(t_divpipe *divpipe)
{
	while (divpipe)
	{
		if (divpipe->cmd && divpipe->cmd[0])
			divpipe->cmd_path = divpipe->cmd[0];
		else
			divpipe->cmd_path = NULL;
		divpipe = divpipe->next;
	}
}

char	*try_path(t_divpipe *divpipe, char **paths)
{
	char	*test;
	int		i;

	if (!divpipe->cmd || !divpipe->cmd[0])
		return (NULL);
	if (is_builtin(divpipe->cmd[0]))
		return ("IS BUILTIN");
	i = 0;
	while (paths[i])
	{
		test = ft_strjoin(paths[i], divpipe->cmd[0]);
		if (!test)
			return (NULL);
		if (access(test, F_OK | X_OK) == 0)
		{
			divpipe->cmd_path = test;
			return (test);
		}
		free(test);
		i++;
	}
	divpipe->cmd_path = NULL;
	return ("UNKNOWN");
}

char	*put_paths(t_divpipe *divpipe, char **env)
{
	char		**paths;
	t_divpipe	*tmp_pipe;

	set_path_to_base_cmd(divpipe);
	if (get_env_index(env, "PATH") < 0)
		return ("NO PATH");
	paths = get_paths(env);
	if (!paths)
		return (NULL);
	tmp_pipe = divpipe;
	while (tmp_pipe)
	{
		if (!try_path(tmp_pipe, paths))
		{
			ft_free_tab(paths);
			return (NULL);
		}
		tmp_pipe = tmp_pipe->next;
	}
	ft_free_tab(paths);
	return ("DONE");
}

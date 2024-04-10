/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:52:47 by fparis            #+#    #+#             */
/*   Updated: 2024/04/10 22:31:52 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_index(char **env, char *name)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len))
			return (i);
		i++;
	}
	return (-1);
}

char	*get_env_value(char **env, char *name)
{
	int		i;
	int		i2;
	char	*res;
	int		index;

	index = get_env_index(name);
	i = 0;
	i2 = 1;
	while (index >= 0 && env[index][i] && env[index][i] != '=')
		i++;
	if (index < 0 || !env[index][i])
		return (NULL);
	while (env[index][i + i2])
		i2++;
	res = ft_calloc(i2, sizeof(char));
	if (!res)
		return (NULL);
	i2 = 0;
	while (env[index][i + i2 + 1])
	{
		res[i2] = env[index][i + i2 + 1];
		i2++;
	}
	return (res);
}

char	**dup_env_tab(char **old_env)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(ft_strtablen(old_env) + 1, sizeof(char *));
	i = 0;
	while (old_env[i])
	{
		new_env[i] = ft_strdup(old_env[i]);
		if (!new_env[i])
		{
			ft_free_tab(new_env);
			//inserer exit ici
		}
		i++;
	}
	return (new_env);
}

void	remove_var(char **env, char *name)
{
	//j'attends le grep de ton pipex
}

void	add_var(char **env, char *name, char *value)
{
	int		i;
	char	**new_env;

	if (get_env_index(env, name))
	{
		remove_var(env, name);
		add_var(env, name, value);
	}
	new_env = ft_calloc(ft_strtablen(env) + 1, sizeof(char **));
	i = 0;
	while (new_env && env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	ft_free_tab(env);
	if (new_env)
		new_env[i] = ft_vajoin(name, "=", value, NULL);
	if (!new_env || !new_env[i])
	{
		ft_free_tab(new_env);
		//inserer exit ici
	}
}

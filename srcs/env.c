/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:52:47 by fparis            #+#    #+#             */
/*   Updated: 2024/04/19 19:02:21 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_index(char **env, char *name)
{
	int	i;
	int	len;

	len = 0;
	while (name[len] && name[len] != '=')
		len++;
	len += name[len] == '=';
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

	index = get_env_index(env, name);
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

void	remove_var(char ***env, char *name)
{
	int		index;
	char	**new_env;
	int		i;
	int		i2;

	index = get_env_index(*env, name);
	if (index < 0)
		return ;
	new_env = ft_calloc(ft_strtablen(*env) + 1, sizeof(char **));
	if (!new_env)
		return ;
		//inserer exit qui free env;
	free((*env)[index]);
	i = 0;
	i2 = 0;
	while ((*env)[i])
	{
		if (i != index)
		{
			new_env[i2] = (*env)[i];
			i2++;
		}
		i++;
	}
	free(*env);
	*env = new_env;
}

void	add_var(char ***env, char *env_var)
{
	int		i;
	char	**new_env;

	if (get_env_index(*env, env_var) >= 0)
		remove_var(env, env_var); //bien check ce cas la parce que changement de tab inter fonction suspect
	new_env = ft_calloc(ft_strtablen(*env) + 2, sizeof(char **));
	if (!new_env)
		return ;
		//inserer exit qui free env
	i = 0;
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	free(*env);
	new_env[i] = env_var;
	*env = new_env;
}
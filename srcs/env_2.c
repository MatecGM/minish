/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:41:37 by fparis            #+#    #+#             */
/*   Updated: 2024/06/05 22:24:18 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_name_len(char *env_var)
{
	int	len;

	len = 0;
	while (env_var[len] && env_var[len] != '=')
		len++;
	return (len);
}

char	*remove_plus(char *env_var)
{
	int		i;
	char	*new_var;

	new_var = ft_calloc(sizeof(char), ft_strlen(env_var));
	if (!new_var)
		return (NULL);
	i = 0;
	while (env_var[i] && env_var[i] != '+')
	{
		new_var[i] = env_var[i];
		i++;
	}
	while (env_var[i] && env_var[i + 1])
	{
		new_var[i] = env_var[i + 1];
		i++;
	}
	return (new_var);
}

int	get_append_len(char *env_var)
{
	int	len;

	len = 0;
	while (env_var[len] && env_var[len] != '=')
		len++;
	return (ft_strlen(env_var) - len);
}

char	*get_append(char *env_var, int len)
{
	int		i;
	int		name_len;
	char	*append;

	append = ft_calloc(sizeof(char), len);
	if (!append)
		return (NULL);
	name_len = ft_strlen(env_var) - len + 1;
	i = 0;
	while (env_var[i + name_len])
	{
		append[i] = env_var[i + name_len];
		i++;
	}
	return (append);
}

void	append_var(t_minish *minish, char *env_var)
{
	int		len;
	int		last_index;
	char	*new_var;

	last_index = get_env_index(minish->env, env_var);
	if (last_index >= 0)
	{
		len = get_append_len(env_var);
		if (!len)
			return ;
		new_var = (ft_strjoin(minish->env[last_index], env_var + (ft_strlen(env_var) - len + (ft_strchr(minish->env[last_index], '=') != NULL))));
	}
	else
		new_var = remove_plus(env_var);
	if (!new_var)
		exit_free(minish, 1);
	add_var(minish, new_var); //si malloc echoue ca fait des leaks mais bon
	free(new_var);
}

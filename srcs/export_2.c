/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:41:37 by fparis            #+#    #+#             */
/*   Updated: 2024/05/30 22:37:08 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_plus(char *env_var)
{
	int		i;
	char	*new_var;

	new_var = ft_calloc(sizeof(char), ft_strlen(env_var) - 1);
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

void	append_var(char ***env, char *env_var)
{
	int		len;
	int		last_index;
	char	*new_var;

	last_index = get_env_index(*env, env_var);
	if (last_index >= 0)
	{
		len = get_append_len(env_var);
		if (!len)
			return ;
		new_var = (ft_strjoin((*env)[last_index], env_var + (ft_strlen(env_var) - len + 1)));
	}
	else
		new_var = remove_plus(env_var);
	if (!new_var)
		return ; //inserer exit free ou code erreur ou retour NULL
	add_var(env, new_var);
}

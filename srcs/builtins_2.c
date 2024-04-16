/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:50:08 by fparis            #+#    #+#             */
/*   Updated: 2024/04/16 20:55:40 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char **tab, char **env)
{
	int	i;

	if (!tab || !tab[0])
		return ;
	i = 1;
	while (tab[i])
	{
		remove_var(&env, tab[i]);
		i++;
	}
}

void	env(char **tab, char **env)
{
	int	i;

	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

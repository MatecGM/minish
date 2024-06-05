/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:50:08 by fparis            #+#    #+#             */
/*   Updated: 2024/06/05 19:55:02 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **tab, t_minish *minish)
{
	int	i;

	if (!tab || !tab[0])
		return ;
	i = 1;
	while (tab[i])
	{
		remove_var(minish, tab[i]);
		i++;
	}
}

void	ft_env(char **tab, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (is_good_env(env[i]) == 1)
			printf("%s\n", env[i]);
		i++;
	}
}

int	get_exit_code(char **tab)
{
	int	i;
	int	exit_code;

	exit_code = 0;
	i = 0;
	if (tab && tab[0])
	{
		i = 0;
		while (tab[0][i])
		{
			if (tab[0][i] < '0' || tab[0][i] > '9')
			{
				printf("minish: exit: %s: numeric argument required", tab[0]);
				return (0);
			}
			else
				exit_code = exit_code * 10 + (tab[0][i] - '0');
			i++;
		}
	}
	return (exit_code);
}

void	ft_exit(char **tab, t_minish *minish)
{
	int	exit_code;

	if (!tab)
		return ;
	ft_putstr_fd("exit\n", 2);
	exit_code = 0;
	if (ft_strtablen(tab) > 1)
		printf("minish: exit: too many arguments");
	else
		exit_code = get_exit_code(tab) & 255;
	exit_free(minish, exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:50:08 by fparis            #+#    #+#             */
/*   Updated: 2024/07/09 19:09:56 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **tab, t_minish *minish)
{
	int	i;

	minish->exit_status = 0;
	if (minish->in_pipe)
		return ;
	if (!tab || !tab[0])
		return ;
	i = 1;
	while (tab[i])
	{
		remove_var(minish, tab[i]);
		i++;
	}
}

void	ft_env(char **tab, char **env, t_minish *minish, int fd)
{
	int	i;

	if (ft_strtablen(tab) > 1)
	{
		minish->exit_status = 1;
		ft_putstr_fd("env: too many arguments\n", 2);
		return ;
	}
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "_=", 2))
			ft_putstr_fd("_=/usr/bin/env\n", fd);
		else if (is_good_env(env[i]) == 1)
			ft_putendl_fd(env[i], fd);
		i++;
	}
	minish->exit_status = 0;
}

int	get_exit_code(char **tab)
{
	int			i;
	long long	exit_code;

	exit_code = 0;
	if (!tab || !tab[1])
		return (0);
	i = 0;
	while (ft_isspace(tab[1][i]))
		i++;
	while (tab[1][i] >= '0' && tab[1][i] <= '9')
	{
		if (exit_code * 10 + (tab[1][i] - '0') < exit_code)
			break ;
		exit_code = exit_code * 10 + (tab[1][i] - '0');
		i++;
	}
	if (tab[1][i])
	{
		print_error("minish: exit: ",
			tab[1], ": numeric argument required");
		return (2);
	}
	return (exit_code);
}

void	ft_exit(char **tab, t_minish *minish)
{
	long long	exit_code;

	ft_putstr_fd("exit\n", 2);
	exit_code = 0;
	if (ft_strtablen(tab) > 2)
	{
		ft_putstr_fd("minish: exit: too many arguments\n", 2);
		minish->exit_status = 1;
		return ;
	}
	else
		exit_code = get_exit_code(tab) & 255;
	minish->exit_status = exit_code;
	if (!tab || minish->in_pipe)
		return ;
	exit_free(minish, exit_code);
}

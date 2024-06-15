/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:43:21 by fparis            #+#    #+#             */
/*   Updated: 2024/06/15 18:27:06 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str1, char *str2, char *str3)
{
	if (str1)
		ft_putstr_fd(str1, 2);
	if (str2)
		ft_putstr_fd(str2, 2);
	if (str3)
		ft_putstr_fd(str3, 2);
	ft_putstr_fd("\n", 2);
}

int	check_echo_parameter(char **check)
{
	int	res;
	int	i;

	res = 1;
	if (!check[res])
		return (res);
	while (check[res] && !ft_strncmp(check[res], "-n", 2))
	{
		i = 1;
		while (check[res][i] == 'n')
			i++;
		if (!check[res][i])
			res++;
		else
			return (res);
	}
	return (res);
}

void	ft_echo(char **tab, t_minish *minish, int fd)
{
	int		i;
	int		parameter;

	parameter = check_echo_parameter(tab);
	i = parameter;
	while (tab[i])
	{
		ft_putstr_fd(tab[i], fd);
		i++;
		if (tab[i])
			ft_putchar_fd(' ', fd);
	}
	if (parameter == 1)
		ft_putstr_fd("\n", fd);
	minish->exit_status = 0;
}

void	ft_cd(char **tab, t_minish *minish, int fd)
{
	if (minish->in_pipe)
		return ;
	minish->exit_status = 1;
	if (ft_strtablen(tab) == 1)
		cd_home(minish);
	else if (ft_strtablen(tab) > 2)
		print_error("minish: cd: too many arguments", NULL, NULL);
	else if (!ft_strcmp(tab[1], "-"))
		cd_back(minish, fd);
	else
		default_cd(tab, minish);
}

void	ft_pwd(char **tab, t_minish *minish, int fd)
{
	char *path;

	minish->exit_status = 1;
	if (ft_strtablen(tab) > 1)
		ft_putstr_fd("pwd: too many arguments\n", 2);
	path = getcwd(NULL, 0);
	if (!path)
	{
		if (errno == ENOENT)
		{
			print_error("minish: Stale file handle", NULL, NULL);
			return ;
		}
		exit_free(minish, 1);
	}
	ft_putendl_fd(path, fd);
	free(path);
	minish->exit_status = 0;
}

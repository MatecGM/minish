/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:43:21 by fparis            #+#    #+#             */
/*   Updated: 2024/06/06 22:10:57 by fparis           ###   ########.fr       */
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

t_bool	check_echo_parameter(char *check)
{
	t_bool	res;
	int		i;

	i = 1;
	res = FALSE;
	if (check && !ft_strncmp(check, "-n", 2))
	{
		while (check[i] == 'n')
			i++;
		if (!check[i])
			res = TRUE;
	}
	return (res);
}

void	ft_echo(char **tab, t_minish *minish)
{
	int		i;
	t_bool	parameter;

	i = 1;
	parameter = check_echo_parameter(tab[1]);
	if (parameter)
		i = 2;
	while (tab[i])
	{
		printf("%s", tab[i]);
		i++;
		if (tab[i])
			printf(" ");
	}
	if (!parameter)
		printf("\n");
	minish->exit_status = 0;
}

void	ft_cd(char **tab, t_minish *minish)
{
	if (minish->in_pipe)
		return ;
	if (ft_strtablen(tab) == 1)
	{
		cd_home(minish);
		return ;
	}
	else if (ft_strtablen(tab) > 2)
		print_error("cd: string not in pwd: ", tab[1], NULL);
	else if (access(tab[1], F_OK) == 0)
	{
		if (access(tab[1], R_OK) == 0)
		{
			update_pwd(minish, "OLDPWD=");
			chdir(tab[1]);
			update_pwd(minish, "PWD=");
			minish->exit_status = 0;
			return ;
		}
		else
			print_error("cd: permission denied: ", tab[1], NULL);
	}
	else
		print_error("cd: no such file or directory: ", tab[1], NULL);
	minish->exit_status = 1;
}

void	ft_pwd(char **tab, t_minish *minish)
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
			print_error("minish: The current working",
				"directory has been unlinked", NULL);
			return ;
		}
		exit_free(minish, 1);
	}
	printf("%s\n", path);
	free(path);
	minish->exit_status = 0;
}

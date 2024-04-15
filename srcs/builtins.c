/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:43:21 by fparis            #+#    #+#             */
/*   Updated: 2024/04/15 17:54:49 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *str1, char *str2)
{
	if (str1)
		ft_putstr_fd(str1, 2);
	if (str2)
		ft_putstr_fd(str2, 2);
	ft_putstr_fd("\n", 2);
}

void	echo(char **tab)
{
	int		i;
	t_bool	parameter;

	parameter = FALSE;
	i = 1;
	if (tab[1] && !ft_strcmp(tab[1], "-n"))
	{
		parameter = TRUE;
		i = 2;
	}
	while (tab[i])
	{
		printf("%s", tab[i]);
		i++;
	}
	if (!parameter)
		printf("\n");
}

void	cd(char **tab)
{
	//g2rer home variable si aucun arg
	if (ft_strtablen(tab) > 2)
		print_error("cd: string not in pwd: ", tab[1]);
	if (access(tab[1], F_OK) == 0)
	{
		if (access(tab[1], R_OK) == 0)
			chdir(tab[1]);
		else
			print_error("cd: permission denied: ", tab[1]);
	}
	else
		print_error("cd: no such file or directory: ", tab[1]);
	//faut changer la variable d'environnement pwd manuellement
}

void	pwd(char **tab)
{
	char tab[69420];

	if (ft_strtablen(tab) > 1)
		ft_putstr_fd("pwd: too many arguments\n", 2);
	getcwd(tab, 69420);
	printf("%s\n", tab);
}

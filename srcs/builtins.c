/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:43:21 by fparis            #+#    #+#             */
/*   Updated: 2024/04/19 18:23:16 by fparis           ###   ########.fr       */
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

void	ft_echo(char **tab)
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

void	ft_cd(char **tab)
{
	//g2rer home variable si aucun arg
	if (ft_strtablen(tab) > 2)
		print_error("cd: string not in pwd: ", tab[1], NULL);
	if (access(tab[1], F_OK) == 0)
	{
		if (access(tab[1], R_OK) == 0)
			chdir(tab[1]);
		else
			print_error("cd: permission denied: ", tab[1], NULL);
	}
	else
		print_error("cd: no such file or directory: ", tab[1], NULL);
	//faut changer la variable d'environnement pwd manuellement
}

void	ft_pwd(char **tab)
{
	char tab2[69420];

	if (ft_strtablen(tab) > 1)
		ft_putstr_fd("pwd: too many arguments\n", 2);
	getcwd(tab2, 69420);
	printf("%s\n", tab2);
}

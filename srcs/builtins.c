/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:43:21 by fparis            #+#    #+#             */
/*   Updated: 2024/04/08 14:53:30 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	cd(char *new_path)
{
	chdir(new_path);
	//faut changer la variable d'environnement pwd manuellement
}

void	pwd()
{
	char tab[69420];

	getcwd(tab, 69420);
	printf("%s\n", tab);
}

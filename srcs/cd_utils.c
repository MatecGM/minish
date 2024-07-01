/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:33:29 by fparis            #+#    #+#             */
/*   Updated: 2024/07/01 17:40:43 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_home(t_minish *minish)
{
	char	*home;

	minish->exit_status = 1;
	home = get_env_value(minish->env, "HOME=");
	if (!home)
	{
		ft_putstr_fd("minish: cd: HOME not set\n", 2);
		return ;
	}
	else if (access(home, F_OK) == 0)
	{
		if (access(home, R_OK) == 0)
		{
			update_pwd(minish, "OLDPWD=");
			chdir(home);
			update_pwd(minish, "PWD=");
			minish->exit_status = 0;
		}
		else
			print_error("cd: permission denied: ", home, NULL);
	}
	free(home);
}

void	default_cd(char **tab, t_minish *minish)
{
	if (!tab[1][0] || access(tab[1], F_OK) == 0)
	{
		if (!tab[1][0] || access(tab[1], R_OK) == 0)
		{
			update_pwd(minish, "OLDPWD=");
			chdir(tab[1]);
			update_pwd(minish, "PWD=");
			minish->exit_status = 0;
		}
		else
			print_error("cd: permission denied: ", tab[1], NULL);
	}
	else
		print_error("cd: no such file or directory: ", tab[1], NULL);
}

void	cd_back(t_minish *minish, int fd)
{
	char	*old_pwd;

	old_pwd = get_env_value(minish->env, "OLDPWD=");
	if (!old_pwd)
	{
		print_error("minish: cd: OLDPWD not set", NULL, NULL);
		return ;
	}
	if (!old_pwd[0] || access(old_pwd, F_OK) == 0)
	{
		if (!old_pwd[0] || access(old_pwd, R_OK) == 0)
		{
			ft_putstr_fd(old_pwd, fd);
			ft_putstr_fd("\n", fd);
			update_pwd(minish, "OLDPWD=");
			chdir(old_pwd);
			update_pwd(minish, "PWD=");
			minish->exit_status = 0;
		}
		else
			print_error("cd: permission denied: ", old_pwd, NULL);
	}
	else
		print_error("cd: no such file or directory: ", old_pwd, NULL);
	free(old_pwd);
}

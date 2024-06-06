/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:50:08 by fparis            #+#    #+#             */
/*   Updated: 2024/06/06 22:01:22 by fparis           ###   ########.fr       */
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

void	ft_env(char **tab, char **env, t_minish *minish)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "_=", 2))
			printf("_=/usr/bin/env\n"); //bizarre
		else if (is_good_env(env[i]) == 1)
			printf("%s\n", env[i]);
		i++;
	}
	minish->exit_status = 0;
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
				return (2);
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

	ft_putstr_fd("exit\n", 2);
	exit_code = 0;
	if (ft_strtablen(tab) > 1)
	{
		printf("minish: exit: too many arguments");
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
			chdir(home); //home pas protect
			update_pwd(minish, "PWD=");
			minish->exit_status = 0;
		}
		else
			print_error("cd: permission denied: ", home, NULL);
	}
	free(home);
}

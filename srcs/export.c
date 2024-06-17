/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:45:11 by fparis            #+#    #+#             */
/*   Updated: 2024/06/18 00:12:41 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_declare(char **env, int fd)
{
	int	i2;
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "_=", 2) != 0)
		{
			ft_putstr_fd("declare -x ", fd);
			i2 = -1;
			while (env[i][++i2] && env[i][i2] != '=')
				ft_putchar_fd(env[i][i2], fd);
			if (env[i][i2] == '=')
			{
				ft_putstr_fd("=\"", fd);
				while (env[i][++i2])
					ft_putchar_fd(env[i][i2], fd);
				ft_putstr_fd("\"", fd);
			}
			ft_putstr_fd("\n", fd);
		}
		i++;
	}
	return (*env);
}

void	print_ascii_order(char **env, int fd)
{
	char	**env_dup;
	int		i;
	int		i2;
	int		i_min;

	env_dup = dup_env_tab(env);
	if (!env_dup)
		return ;
	i = 0;
	while (env_dup[i])
	{
		i_min = i;
		i2 = i + 1;
		while (env_dup[i2])
		{
			if (ft_strcmp(env_dup[i_min], env_dup[i2]) > 0)
				i_min = i2;
			i2++;
		}
		ft_swap_str(env_dup, i, i_min);
		i++;
	}
	print_declare(env_dup, fd);
	ft_free_tab(env_dup);
}

int	is_good_env(char *env_var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(env_var[0]) && env_var[0] != '_')
		return (0);
	while (env_var[i] && env_var[i] != '=' && !(env_var[i] == '+' && env_var[i
				+ 1] == '='))
	{
		if (!ft_isalpha(env_var[i]) && !ft_isdigit(env_var[i])
			&& env_var[i] != '_')
			return (0);
		i++;
	}
	if (env_var[i] == '+')
		return (2);
	if (env_var[i] == '=')
		return (1);
	return (-1);
}

void	ft_export(char **tab, t_minish *minish, int fd)
{
	int	res;
	int	i;

	minish->exit_status = 0;
	if (ft_strtablen(tab) == 1)
	{
		print_ascii_order(minish->env, fd);
		return ;
	}
	i = 1;
	while (tab[i])
	{
		res = is_good_env(tab[i]);
		if (res == 0)
		{
			print_error("minish: export: '", tab[i],
				"': not a valid identifier");
			minish->exit_status = 1;
		}
		else if (!minish->in_pipe && (res == 1 || res == -1))
			add_var(minish, tab[i]);
		else if (!minish->in_pipe && res == 2)
			append_var(minish, tab[i]);
		i++;
	}
}

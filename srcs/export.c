/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:45:11 by fparis            #+#    #+#             */
/*   Updated: 2024/04/19 18:48:05 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_declare(char **env)
{
	int		i;
	int		i2;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "_=", 2) != 0)
		{
			printf("declare -x ");
			i2 = -1;
			while (env[i][++i2] != '=')
				printf("%c", env[i][i2]);
			printf("=\"");
			while (env[i][++i2])
				printf("%c", env[i][i2]);
			printf("\"\n");
		}
		i++;
	}
	return (*env);
}

void	print_ascii_order(char **env)
{
	char	**env_dup;
	int		i;
	int		i2;
	int		i_min;

	env_dup = dup_env_tab(env);
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
	print_declare(env_dup);
	ft_free_tab(env_dup);
}

int	is_good_env(char *env_var)
{
	int	i;
	int	has_equal;

	has_equal = 0;
	i = 0;
	if (!ft_isalpha(env_var[0]) && env_var[0] != '_')
		return (0);
	while (env_var[i])
	{
		if (env_var[i] == '=')
			has_equal = 1;
		if (!ft_isalpha(env_var[i]) && !ft_isdigit(env_var[i])
			&& env_var[i] != '_' && env_var[i] != '=')
			return (0);
		i++;
	}
	if (!has_equal)
		return (-1);
	return (1);
}

void	ft_export(char **tab, char ***env)
{
	int	res;
	int	i;

	if (ft_strtablen(tab) == 1)
	{
		print_ascii_order(*env);
		return ;
	}
	i = 1;
	while (tab[i])
	{
		res = is_good_env(tab[i]);
		if (res == 0)
			print_error("minish: export: '", tab[i], "': not a valid identifier");
		else if (res == 1)
			add_var(env, tab[i]);
		i++;
	}
}

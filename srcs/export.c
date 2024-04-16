/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:45:11 by fparis            #+#    #+#             */
/*   Updated: 2024/04/16 20:48:01 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_str(char **env, int i1, int i2)
{
	char	*tmp;

	if (i1 == i2)
		return ;
	tmp = env[i1];
	env[i1] = env[i2];
	env[i2] = tmp;
}

char	*print_declare(char **env)
{
	int		i;
	int		i2;
	char	*value;
	char	*value_quote;

	i = 0;
	while (env[i])
	{
		printf("declare -x ");
		i2 = -1;
		while (env[i][++i2] != '=')
			printf("%c", env[i][i2])
		printf("=");
		value = get_env_value(env, env[i]);
		if (!value)
			return (NULL);
		value_quote = ft_vajoin("\"", value, "\"", NULL);
		free(value)
		if (!value_quote)
			return (NULL)
		printf("%s\n", value_quote);
		free(value_quote);
		i++;
	}
	return (*env);
}

char	*print_ascii_order(char **env)
{
	char	**env_dup;
	int		i;
	int		i2;
	int		i_min;
	char	*error_test;

	env_dup = dup_env_tab(env);
	i = 0;
	while (env_dup[i])
	{
		i_min = i;
		i2 = i + 1;
		char_min = env_dup[i];
		while (env_dup[i2])
		{
			if (ft_strcmp(env_dup[i_min], env_dup[i2]) > 0)
				i_min = i2;
			i2++;
		}
		swap_str(env, i, i_min);
		i++;
	}
	error_test = print_declare(env_dup);
	ft_free_tab(env_dup);
	return (error_test);
}

int	is_good_env(char *env_var)
{
	int	i;
	int	has_equal;

	has_equal = 0;
	i = 0;
	if (!ft_isalpha(env_var[0]) && env_var != '_')
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

void	export(char **tab, char **env)
{
	int	res;
	int	i;

	if (ft_strtablen(tab) == 1)
	{
		if (!print_ascii_order(env));
			//inserer exit la
		return ;
	}
	i = 1;
	while (tab[i])
	{
		res = is_good_env(tab[i]);
		if (res == 0)
			print_error("minish: export: '", tab[i], "': not a valid identifier");
		else if (res == 1)
			add_var(&env, tab[i]);
		i++;
	}
}

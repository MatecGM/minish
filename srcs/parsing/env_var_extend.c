/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_extend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:22:33 by mbico             #+#    #+#             */
/*   Updated: 2024/06/27 20:37:45 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_hasdollars(char *str)
{
	while (str && *str)
	{
		if (*str == '$')
			return (TRUE);
		str ++;
	}
	return (FALSE);
}

static t_bool	ft_insingle(char *str, int index, t_bool onheredock)
{
	int	i;
	int	quote;

	i = 0;
	quote = FALSE;
	if (onheredock)
		return (FALSE);
	while (i < index)
	{
		if (str[i] == '\'')
			quote = !quote;
		i ++;
	}
	return (quote);
}

int	is_exit_status(char *str, int *len, int *i, t_minish *minish)
{
	if (str[*i + 1] == '?')
	{
		*len += ft_intlen(minish->exit_status);
		*i += 2;
		return (1);
	}
	return (0);
}

static int	ft_strlen_extend(char *str, t_minish *minish, t_bool onheredock)
{
	int		i;
	char	*value;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$' && !ft_insingle(str, i, onheredock))
		{
			if (is_exit_status(str, &len, &i, minish))
				continue ;
			value = get_env_value(minish->env, str + i + 1);
			len += ft_strlen(value);
			i ++;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i ++;
			free(value);
			continue ;
		}
		len ++;
		i ++;
	}
	return (len);
}

t_bool	ft_envvar_exitcode(char *str, t_minish *minish, int *i, char **new)
{
	char	*value;

	if (str[*i + 1] == '?')
	{
		*i += 2;
		value = ft_itoa(minish->exit_status);
		if (!value)
			exit_free(minish, 1);
		*new = ft_strcat(*new, value);
		free(value);
		return (TRUE);
	}
	value = get_env_value(minish->env, str + *i + 1);
	if (value)
		*new = ft_strcat(*new, value);
	free(value);
	(*i)++;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	return (FALSE);
}

char	*extender(char *str, t_minish *minish, t_bool ohd)
{
	int		i;
	int		j;
	char	*value;
	char	*new;
	t_bool	single_quote;

	new = ft_calloc(ft_strlen_extend(str, minish, ohd) + 1, sizeof(char));
	if (!new)
		exit_free(minish, 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && !ft_insingle(str, i, ohd))
		{
			if (!ft_envvar_exitcode(str, minish, &i, &new))
				j += ft_strlen(value);
			continue ;
		}
		new[j] = str[i];
		j ++;
		i ++;
	}
	free(str);
	return (new);
}

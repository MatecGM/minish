/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_extend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:22:33 by mbico             #+#    #+#             */
/*   Updated: 2024/07/05 18:19:48 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	ft_insingle(char *str, int index, t_bool onheredock)
{
	int	i;
	int	quote;
	int	doublequote;

	i = 0;
	quote = FALSE;
	doublequote = FALSE;
	if (onheredock)
		return (FALSE);
	while (i < index)
	{
		if (str[i] == '\'' && !doublequote)
			quote = !quote;
		else if (str[i] == '"' && !quote)
			doublequote = !doublequote;
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

int	ft_envvar_exitcode(char *str, t_minish *minish, int *i, char **new)
{
	char	*value;
	int		len;

	if (str[*i + 1] == '?')
	{
		*i += 2;
		value = ft_itoa(minish->exit_status);
		if (!value)
			exit_free(minish, 1);
		len = ft_strlen(value);
		*new = ft_strcat(*new, value);
		free(value);
		return (len);
	}
	value = get_env_value(minish->env, str + *i + 1);
	if (value)
		*new = ft_strcat(*new, value);
	len = ft_strlen(value);
	free(value);
	(*i)++;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	return (len);
}

char	*extender(char *str, t_minish *minish, t_bool ohd)
{
	int		i;
	int		j;
	char	*new;

	new = ft_calloc(ft_strlen_extend(str, minish, ohd) + 1, sizeof(char));
	if (!new)
	{
		free(str);
		exit_free(minish, 1);
	}
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && !ft_insingle(str, i, ohd))
		{
			j += ft_envvar_exitcode(str, minish, &i, &new);
			continue ;
		}
		new[j] = str[i];
		j ++;
		i ++;
	}
	free(str);
	return (new);
}

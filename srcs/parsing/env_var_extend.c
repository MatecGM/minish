/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_extend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:22:33 by mbico             #+#    #+#             */
/*   Updated: 2024/06/18 00:21:13 by fparis           ###   ########.fr       */
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
			if (str[i + 1] == '?')
			{
				len += ft_intlen(minish->exit_status);
				i += 2;
				continue ;
			}
			value = get_env_value(minish->env, str + i + 1);
			len += ft_strlen(value);
			i ++;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i ++;
			free(value);
		}
		else
		{
			len ++;
			i ++;
		}
	}
	return (len);
}

char	*extender(char *str, t_minish *minish, t_bool onheredock)
{
	int		i;
	int		j;
	char	*value;
	char	*new;
	t_bool	single_quote;

	new = ft_calloc(ft_strlen_extend(str, minish, onheredock)
			+ 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && !ft_insingle(str, i, onheredock))
		{
			if (str[i + 1] == '?')
			{
				i += 2;
				value = ft_itoa(minish->exit_status);
				if (!value)
					return (NULL);
				new = ft_strcat(new, value);
				free(value);
				continue ;
			}
			value = get_env_value(minish->env, str + i + 1);
			if (value)
				new = ft_strcat(new, value);
			j += ft_strlen(value);
			free(value);
			i++;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i ++;
		}
		else
		{
			new[j] = str[i];
			j ++;
			i ++;
		}
	}
	free(str);
	return (new);
}

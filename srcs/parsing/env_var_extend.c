/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_extend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:22:33 by mbico             #+#    #+#             */
/*   Updated: 2024/05/29 20:15:04 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_hasdollars(char *str)
{
	while(str && *str)
	{
		if (*str == '$')
			return (TRUE);
		str ++;
	}
	return (FALSE);
}

static t_bool	ft_insingle(char *str, int index)
{
	int	i;
	int	quote;

	i = 0;
	quote = FALSE;
	while(i < index)
	{
		if (str[i] == '\'')
			quote = !quote;
		i ++;
	}
	return (quote);
}

static int	ft_strlen_extend(char *str, char **env)	
{
	int		i;
	char	*value;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$' && !ft_insingle(str, i))
		{
			value = get_env_value(env, str + i + 1);
			len += ft_strlen(value);
			while(str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '$'))
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

char	*extender(char *str, char **env)
{
	int		i;
	int		j;
	char	*value;
	char	*new;
	t_bool	single_quote;

	new = ft_calloc(ft_strlen_extend(str, env) + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && !ft_insingle(str, i))
		{
			value = get_env_value(env, str + i + 1);
			if (value)
				new = ft_strcat(new, value);
			j += ft_strlen(value);
			free(value);
			while(str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '$'))
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

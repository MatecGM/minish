/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_extend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:22:33 by mbico             #+#    #+#             */
/*   Updated: 2024/05/22 13:45:32 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strlen_extend(char *str, char **env)	
{
	int		i;
	char	*value;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			value = get_env_value(env, str + i + 1);
			len += ft_strlen(value);
			while(str[i] && str[i] != ' ')
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

	new = ft_calloc(ft_strlen_extend(str, env), sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			value = get_env_value(env, str + i + 1);
			if (value)
				new = ft_strcat(new, value);
			j += ft_strlen(value);
			free(value);
			while(str[i] && str[i] != ' ')
				i ++;
		}
		else
		{
			new[j] = str[i];
			j ++;
			i ++;	
		}
	}
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:14:17 by mbico             #+#    #+#             */
/*   Updated: 2024/06/27 19:18:07 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_ambiguous_checker(char *str)
{
	int	len;

	if (str[0] != '$')
		return (FALSE);
	len = 1;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len ++;
	if (len == ft_strlen(str))
		return (TRUE);
	return (FALSE);
}

t_bool	ft_hasspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (TRUE);
		i ++;
	}
	return (FALSE);
}

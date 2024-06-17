/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_first_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:11:43 by mbico             #+#    #+#             */
/*   Updated: 2024/06/18 00:15:05 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_quote_first_arg(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '\'' || str[i] == '"')
			return (TRUE);
		i ++;
	}
	return (FALSE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_first_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:11:43 by mbico             #+#    #+#             */
/*   Updated: 2024/07/08 18:28:39 by mbico            ###   ########.fr       */
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

t_bool	ft_inquote(char *str, int index)
{
	int	i;
	int	quote;
	int	doublequote;

	i = 0;
	quote = FALSE;
	doublequote = FALSE;
	while (i < index)
	{
		if (str[i] == '\'' && !doublequote)
			quote = !quote;
		else if (str[i] == '"' && !quote)
			doublequote = !doublequote;
		i ++;
	}
	return (quote || doublequote);
}

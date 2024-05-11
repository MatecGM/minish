/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_extend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:22:33 by mbico             #+#    #+#             */
/*   Updated: 2024/05/11 18:51:09 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len_extend(char **str)
{
	int 	len;
	int		i;

	len = 0;
	*str ++;
	while ()
}

int	prompt_real_len(char *str)
{
	t_quote	quote;
	int		len;

	quote = NO_QUOTE;
	while (*str)
	{
		if (!quote && *str == '\'')
			quote = SINGLE;
		else if (!quote && *str == '"')
			quote = DOUBLE;
		else if ((quote == SINGLE && *str == '\'') 
			|| (quote == DOUBLE && *str == '"'))
			quote = NO_QUOTE;
		if (*str == '$' && quote != SINGLE)
			
		len ++;
		str ++;
	}
}

char	*env_var_extend(char *str)
{
	
	free(str);
}
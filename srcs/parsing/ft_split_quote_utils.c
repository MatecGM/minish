/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:15:05 by mbico             #+#    #+#             */
/*   Updated: 2024/06/25 19:19:07 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**check_splitquote_str(char *str)
{
	char	**cmd;

	if (!str || !str[0])
	{
		cmd = ft_calloc(2, sizeof(char *));
		if (cmd)
			cmd[0] = ft_strdup(str);
		return (cmd);
	}
	return (NULL);
}

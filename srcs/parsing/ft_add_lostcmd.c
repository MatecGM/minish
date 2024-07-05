/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_lostcmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:46:15 by mbico             #+#    #+#             */
/*   Updated: 2024/07/05 18:46:42 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_lostcmd(char **split, char **cmd)
{
	int		i;
	char	*tmp;

	i = 1;
	while (split[i])
	{
		tmp = *cmd;
		if (tmp)
		{
			*cmd = ft_vajoin(tmp, " ", split[i], NULL);
			if (!(*cmd))
			{
				ft_free_tab(split);
				return (1);
			}
			free(tmp);
			free(split[i]);
		}
		else
			*cmd = split[i];
		i ++;
	}
	free(split);
	return (0);
}

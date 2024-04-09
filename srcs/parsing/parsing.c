/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:54:13 by mbico             #+#    #+#             */
/*   Updated: 2024/04/09 19:38:30 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	typage(char *elem)
{
	if (strcmp(elem, "|"))
}

char	**parsing(char *str)
{
	char	**elem;
	char	**ptr;
	t_type	prevtype;

	elem = ft_tokenizer(str);
	if (!elem)
		return (NULL);
	while (*ptr)
	{
		prevtype = typage();
		ptr ++;
	}
	free(str);
}

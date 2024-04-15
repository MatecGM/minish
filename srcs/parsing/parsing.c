/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:54:13 by mbico             #+#    #+#             */
/*   Updated: 2024/04/15 20:05:02 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	typage(const char *elem)
{
	if (strcmp(elem, "|"))
		return (tpipe);
	else if (strcmp(elem, "<"))
		return (tinfile);
	else if (strcmp(elem, "<<"))
		return (theredoc);
	else if (strcmp(elem, ">"))
		return (toutfile);
	else if (strcmp(elem, ">>"))
		return (tappend);
	else
		return (tcommand);
}

char	**parsing(char *str)
{
	char	**elem;
	char	**ptr;
	t_type	prevtype;

	elem = ft_tokenizer(str);
	if (!elem)
		return (NULL);
	ptr = elem;
	prevtype = tfirst;
	while (*ptr)
	{	
		prevtype = typage(elem);
		ptr ++;
	}
	free(str);
}

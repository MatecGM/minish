/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:54:13 by mbico             #+#    #+#             */
/*   Updated: 2024/04/17 19:07:16 by mbico            ###   ########.fr       */
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

void	inpipe(char **ptr)
{
	while(*ptr && typage(*ptr) != tpipe)
	{
		if (**ptr == '<' || **ptr == '>')
			blablaredirection();
		
		ptr ++;
	}
}

char	**parsing(char *str)
{
	char	**elem;
	char	**ptr;

	elem = ft_tokenizer(str);
	if (!elem)
		return (NULL);
	ptr = elem;
	while (*ptr)
	{
		inpipe(ptr);
		if (*ptr)
			ptr++;
	}
	free(str);
}

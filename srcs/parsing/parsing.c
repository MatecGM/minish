/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:54:13 by mbico             #+#    #+#             */
/*   Updated: 2024/05/02 18:18:07 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type typage(char *elem)
{
	if (!ft_strcmp(elem, "<<"))
		return (theredoc);
	else if (!ft_strcmp(elem, ">>"))
		return (tappend);
	else if (!ft_strcmp(elem, "<"))
		return (tinfile);
	else if (!ft_strcmp(elem, ">"))
		return (toutfile);
	return (tnull);
}

void	redirect_filler(t_divpipe *cpipe, char *arg, t_type ltype)
{
	
}

void	inpipe(t_divpipe *cpipe, char **toked, int i)
{
	t_type		ltype;
	t_type		ctype;
	char		*cmd;
	
	ltype = tnull;
	while (strcmp(toked[i], "|"))
	{
		ctype = typage(toked[i]);
		if (ctype == tnull)
		{
			if (ltype == tnull)
				cmd = toked[i];
			else
				redirect_filler(cpipe, toked[i], ltype);
		}
		ltype = ctype;
		i ++;
	}
}

t_divpipe	*ft_parsing(char *input)
{
	char		**toked;
	t_divpipe	*divpipe;
	t_divpipe	*cpipe;
	int			i;
	
	divpipe = NULL;
	toked = ft_tokenizer(input);
	if (!toked)
		return (NULL);
	i = 0;
	while (toked[i])
	{
		cpipe = ft_pipenew;
		ft_pipeadd_back(&divpipe, cpipe);
		inpipe(cpipe, toked, i);
		if (toked[i])
			i ++;
	}
}

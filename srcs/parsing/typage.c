/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:01:42 by mbico             #+#    #+#             */
/*   Updated: 2024/07/10 21:53:47 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	typage(char *elem)
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

t_bool	ft_dollars_only(char *str, int i, t_bool ohd)
{
	return (str[i] == '$' && !(!str[i + 1] || str[i + 1] == '"'
			|| ft_isspace(str[i + 1])) && !ft_insingle(str, i, ohd));
}

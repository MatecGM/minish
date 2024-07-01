/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:01:42 by mbico             #+#    #+#             */
/*   Updated: 2024/07/01 18:06:11 by mbico            ###   ########.fr       */
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

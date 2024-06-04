/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:08:01 by mbico             #+#    #+#             */
/*   Updated: 2024/06/04 19:28:08 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_divpipe	*ft_pipenew(void)
{
	t_divpipe	*l;

	l = malloc(sizeof(t_divpipe));
	if (l == NULL)
		return (NULL);
	l->next = NULL;
	l->redirect = NULL;
	l->cmd = NULL;
	l->cmd_path = NULL;
	return (l);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:08:01 by mbico             #+#    #+#             */
/*   Updated: 2024/06/14 20:19:14 by mbico            ###   ########.fr       */
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
	l->child_pid = 0;
	return (l);
}

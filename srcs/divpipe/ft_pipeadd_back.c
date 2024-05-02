/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:28:13 by mbico             #+#    #+#             */
/*   Updated: 2024/05/02 18:13:48 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipeadd_back(t_divpipe **l, t_divpipe *new)
{
	t_divpipe	*tmp;

	if (*l == NULL)
	{
		*l = new;
		return ;
	}
	tmp = *l;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

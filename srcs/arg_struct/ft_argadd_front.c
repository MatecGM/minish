/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:22:54 by mbico             #+#    #+#             */
/*   Updated: 2024/04/05 20:48:39 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_argadd_front(t_arg **arg, t_arg *new)
{
	t_arg	*tmp;

	tmp = new;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = *arg;
	*arg = new;
}

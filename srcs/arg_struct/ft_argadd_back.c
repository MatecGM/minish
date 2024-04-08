/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:28:13 by mbico             #+#    #+#             */
/*   Updated: 2024/04/05 20:48:19 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_argadd_back(t_arg **arg, t_arg *new)
{
	t_arg	*tmp;

	if (*arg == NULL)
	{
		*arg = new;
		return ;
	}
	tmp = *arg;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

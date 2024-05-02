/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:28:13 by mbico             #+#    #+#             */
/*   Updated: 2024/05/02 17:40:18 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redadd_back(t_redirect **red, t_redirect *new)
{
	t_redirect	*tmp;

	if (*red == NULL)
	{
		*red = new;
		return ;
	}
	tmp = *red;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

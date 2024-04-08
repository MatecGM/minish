/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:27:09 by mbico             #+#    #+#             */
/*   Updated: 2024/04/05 20:46:34 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_argclear(t_arg **arg, void (*del)(void *))
{
	if (arg && *arg && del)
	{
		if (arg[0]->next)
			ft_lstclear(&arg[0]->next, del);
		ft_lstdelone(*arg, del);
		*arg = NULL;
	}
	else if (arg)
		*arg = NULL;
}

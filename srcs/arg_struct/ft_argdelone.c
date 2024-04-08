/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:56:04 by mbico             #+#    #+#             */
/*   Updated: 2024/04/05 20:45:22 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_argdelone(t_arg *arg, void (*del)(void *))
{
	if (!arg || !del)
		return ;
	del(arg->content);
	arg->next = NULL;
	free(arg);
}

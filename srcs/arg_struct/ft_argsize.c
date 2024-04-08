/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:02:40 by fparis            #+#    #+#             */
/*   Updated: 2024/04/05 20:29:15 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_argsize(t_arg *arg)
{
	int		len;
	t_arg	*ptr;

	len = 0;
	ptr = arg;
	while (ptr)
	{
		len++;
		ptr = ptr->next;
	}
	return (len);
}

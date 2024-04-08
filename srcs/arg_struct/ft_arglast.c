/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arglast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:31:02 by fparis            #+#    #+#             */
/*   Updated: 2024/04/05 20:40:10 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*ft_arglast(t_arg *arg)
{
	t_arg	*ptr;

	if (arg == NULL)
		return (NULL);
	ptr = arg;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

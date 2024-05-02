/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:08:01 by mbico             #+#    #+#             */
/*   Updated: 2024/05/02 17:41:11 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_divpipe	*ft_pipenew(void)
{
	t_divpipe	*l;

	l = malloc(sizeof(t_divpipe));
	if (l == NULL)
		return (NULL);
	return (l);
}

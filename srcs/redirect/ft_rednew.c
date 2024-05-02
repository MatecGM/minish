/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rednew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:08:01 by mbico             #+#    #+#             */
/*   Updated: 2024/05/02 17:38:44 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect	*ft_rednew(t_type type, char *arg)
{
	t_redirect	*l;

	l = malloc(sizeof(t_redirect));
	if (l == NULL)
		return (NULL);
	l->type = type;
	l->arg = arg;
	l->next = NULL;
	return (l);
}

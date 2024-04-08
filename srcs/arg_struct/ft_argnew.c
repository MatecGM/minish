/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:49:23 by fparis            #+#    #+#             */
/*   Updated: 2024/04/05 20:38:59 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*ft_argnew(char *name, t_type type, void *content)
{
	t_arg	*arg;

	arg = ft_calloc(sizeof(t_list), 1);
	if (!arg)
		return (NULL);
	arg->name = name;
	arg->type = type;
	arg->content = content;
	arg->next = NULL;
	return (arg);
}

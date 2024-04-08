/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:22:54 by mbico             #+#    #+#             */
/*   Updated: 2024/04/08 16:35:15 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envadd_front(t_env **env, t_env *new)
{
	t_env	*tmp;

	tmp = new;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = *env;
	*env = new;
}

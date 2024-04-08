/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:28:13 by mbico             #+#    #+#             */
/*   Updated: 2024/04/08 16:35:16 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envadd_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (*env == NULL)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

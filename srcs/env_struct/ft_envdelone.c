/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:56:04 by mbico             #+#    #+#             */
/*   Updated: 2024/04/08 16:35:23 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envdelone(t_env *env, void (*del)(void *))
{
	if (!env || !del)
		return ;
	del(env->content);
	env->next = NULL;
	free(env);
}

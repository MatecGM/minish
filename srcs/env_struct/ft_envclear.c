/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:27:09 by mbico             #+#    #+#             */
/*   Updated: 2024/06/18 00:13:57 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envclear(t_env **env, void (*del)(void *))
{
	if (env && *env && del)
	{
		if (env[0]->next)
			ft_envclear(&env[0]->next, del);
		ft_envdelone(*env, del);
		*env = NULL;
	}
	else if (env)
		*env = NULL;
}

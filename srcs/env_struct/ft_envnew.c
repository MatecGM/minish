/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:49:23 by fparis            #+#    #+#             */
/*   Updated: 2024/04/08 17:50:12 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_envnew(char *name, t_type type, void *content)
{
	t_env	*env;

	env = ft_calloc(sizeof(t_list), 1);
	if (!env)
		return (NULL);
	env->name = name;
	env->content = content;
	env->next = NULL;
	return (env);
}

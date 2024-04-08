/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:31:02 by fparis            #+#    #+#             */
/*   Updated: 2024/04/08 16:35:31 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_envlast(t_env *env)
{
	t_env	*ptr;

	if (env == NULL)
		return (NULL);
	ptr = env;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

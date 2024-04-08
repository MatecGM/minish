/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:02:40 by fparis            #+#    #+#             */
/*   Updated: 2024/04/08 16:35:40 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_envsize(t_env *env)
{
	int		len;
	t_env	*ptr;

	len = 0;
	ptr = env;
	while (ptr)
	{
		len++;
		ptr = ptr->next;
	}
	return (len);
}

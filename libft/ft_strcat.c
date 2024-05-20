/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:29:04 by mbico             #+#    #+#             */
/*   Updated: 2024/05/20 22:15:34 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	int	i;
	int	j;
	
	if (!src)
		return (dst);
	i = 0;
	j = 0;
	while(dst[i])
		i ++;
	while(src[j])
	{
		dst[i] = src[j];
		i ++;
		j ++;
	}
	return (dst);
}

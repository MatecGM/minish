/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freered.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:38:36 by fparis            #+#    #+#             */
/*   Updated: 2024/06/13 18:57:48 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freered(t_redirect *redirect)
{
	if (!redirect)
		return ;
	if (redirect->next)
		ft_freered(redirect->next);
	if (redirect->arg)
		free(redirect->arg);
	if (redirect->heredoc_name)
		free(redirect->heredoc_name);
	free(redirect);
}
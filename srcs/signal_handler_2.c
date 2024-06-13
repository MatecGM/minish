/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:22:22 by fparis            #+#    #+#             */
/*   Updated: 2024/06/13 18:37:25 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_static_minish(t_minish *to_set)
{
	static t_minish	*s_minish = NULL;

	if (!to_set && s_minish)
		exit_free(s_minish, g_signal);
	else if (to_set)
		s_minish = to_set;
}

void	signal_heredoc(int signal)
{
	if (!g_signal)
		g_signal = signal;
	if (signal == SIGINT)
		manage_static_minish(NULL);
}

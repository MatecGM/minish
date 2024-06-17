/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:51:05 by fparis            #+#    #+#             */
/*   Updated: 2024/06/18 00:22:21 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t	g_signal = 0;

int	interactive_mode(t_bool change, int new_value)
{
	static int	is_interactive_mode;

	if (change)
		is_interactive_mode = new_value;
	return (is_interactive_mode);
}

int	check_signal(void)
{
	int	signal;

	signal = g_signal;
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		if (interactive_mode(FALSE, 0))
			rl_redisplay();
	}
	g_signal = 0;
	return (signal);
}

void	signal_handler(int signal)
{
	if (!g_signal)
		g_signal = signal;
	if (interactive_mode(FALSE, 1))
		check_signal();
}

int	init_signal_handler(void)
{
	g_signal = 0;
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGINT, signal_handler) == SIG_ERR)
		return (-1);
	return (0);
}

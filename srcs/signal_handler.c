/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:51:05 by fparis            #+#    #+#             */
/*   Updated: 2024/05/11 16:52:12 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal;

int	interactive_mode(t_bool change, int new_value)
{
	static int	is_interactive_mode;

	if (change)
		is_interactive_mode = new_value;
	return (is_interactive_mode);
}

void	check_signal()
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
	if (signal == SIGQUIT)
	{
		if (!interactive_mode(FALSE, 0))
			ft_putstr_fd("test\n", 1);
	}
}

void	signal_handler(int signal)
{
	if (!g_signal)
		g_signal = signal;
	check_signal();
}

int	init_signal_handler()
{
	g_signal = 0;
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR || signal(SIGINT, signal_handler) == SIG_ERR)
		return (-1);
	return (0);
}

int	get_current_signal()
{
	return (g_signal);
}

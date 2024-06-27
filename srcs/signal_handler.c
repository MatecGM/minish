/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:51:05 by fparis            #+#    #+#             */
/*   Updated: 2024/06/27 20:42:36 by mbico            ###   ########.fr       */
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

int	get_exit_status(int new_value, t_minish *minish)
{
	static int	new_exit_status = 0;

	if (!new_value && minish && new_exit_status)
	{
		minish->exit_status = new_exit_status;
		new_exit_status = 0;
		return (0);
	}
	if (new_value)
		new_exit_status = new_value;
	return (new_exit_status);
}

int	check_signal(t_minish *minish)
{
	int	signal;

	signal = g_signal;
	if (minish && signal == SIGINT)
		minish->exit_status = 130;
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
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
	printf("\n");
	// if (interactive_mode(FALSE, 1))
	// {
	// 	if (check_signal(NULL) == SIGINT)
	// 		get_exit_status(SIGINT, NULL);
	// }
}

int	init_signal_handler(void)
{
	g_signal = 0;
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGINT, signal_handler) == SIG_ERR)
		return (-1);
	return (0);
}

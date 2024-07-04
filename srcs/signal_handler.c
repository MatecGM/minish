/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:51:05 by fparis            #+#    #+#             */
/*   Updated: 2024/07/04 17:55:48 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t	g_signal = 0;

int	interactive_mode(t_bool change, int new_value)
{
	static int	is_interactive_mode;

	if (change)
		is_interactive_mode = new_value;
	if (change && is_interactive_mode)
		signal(SIGQUIT, SIG_IGN);
	else if (change)
		signal(SIGQUIT, signal_handler);
	return (is_interactive_mode);
}

void	get_exit_status(int new_value, t_minish *minish)
{
	static t_minish	*saved = NULL;

	if (!new_value && minish)
	{
		saved = minish;
		return ;
	}
	if (saved && new_value)
		saved->exit_status = new_value;
	return ;
}

int	check_signal(t_minish *minish)
{
	int	signal;

	signal = g_signal;
	if (minish && signal == SIGINT)
		minish->exit_status = 130;
	if (minish && signal == SIGQUIT)
		minish->exit_status = 131;
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
	{
		if (check_signal(NULL) == SIGINT)
			get_exit_status(130, NULL);
	}
}

int	init_signal_handler(void)
{
	g_signal = 0;
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGINT, signal_handler) == SIG_ERR)
		return (-1);
	return (0);
}

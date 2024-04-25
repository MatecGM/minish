/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:51:05 by fparis            #+#    #+#             */
/*   Updated: 2024/04/25 19:33:24 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal;

int	block_signal(int signal, int sig_block)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, signal);
	sigprocmask(sig_block, &sigset, NULL);
	return (0);
}

int	interactive_mode(t_bool change, int new_value)
{
	static int	is_interactive_mode;

	if (change)
	{
		is_interactive_mode = new_value;
		// if (new_value)
		// 	block_signal(SIGQUIT, SIG_BLOCK);
	}
	return (is_interactive_mode);
}

void	signal_handler(int signal)
{
	//printf("%d recu!\n", signal);
	if (!g_signal)
		g_signal = signal;
	check_signal();
}

void	check_signal()
{
	int	signal;

	signal = g_signal;
	if (signal == SIGINT)
	{
		g_signal = 0;
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		if (interactive_mode(FALSE, 0))
			rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		g_signal = 0;
		if (!interactive_mode(FALSE, 0))
			print_error("Quit (core dumped)", NULL, NULL);
		else
		{
			block_signal(SIGQUIT, SIG_BLOCK);
		}
	}
}

int	init_signal_handler()
{
	struct sigaction	act;

	block_signal(SIGQUIT, SIG_BLOCK);
	g_signal = 0;
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &signal_handler;
	if (sigaction(SIGINT, &act, NULL) || sigaction(SIGQUIT, &act, NULL))
		return (-1);
	return (0);
}

int	get_current_signal()
{
	return (g_signal);
}

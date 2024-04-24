/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:51:05 by fparis            #+#    #+#             */
/*   Updated: 2024/04/24 03:58:33 by fparis           ###   ########.fr       */
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

void	signal_handler(int signal)
{
	g_signal = signal;
	if (signal == SIGINT)
	{
		g_signal = 0;
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		if (interactive_mode(FALSE, 0))
			rl_redisplay();
	}
}

void	init_signal_handler()
{
	struct sigaction	act;

	g_signal = 0;
	ft_bzero(&act, sizeof(act));
	act.sa_handler = &signal_handler;
	sigaction(SIGINT, &act, NULL);
}

void	check_signal()
{
	// if (g_signal == SIGINT)
	// {
	// 	printf("\n");
	// 	rl_on_new_line();
	// 	rl_replace_line("", 0);
	// 	rl_redisplay();
	// 	g_signal = 0;
	// }
}

int	get_current_signal()
{
	return (g_signal);
}

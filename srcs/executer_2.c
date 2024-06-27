/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:03:27 by mbico             #+#    #+#             */
/*   Updated: 2024/06/27 18:54:29 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all_pipe(t_minish *minish)
{
	t_divpipe	*tmp_pipe;
	int			status;

	tmp_pipe = minish->divpipe;
	while (tmp_pipe)
	{
		if (tmp_pipe->child_pid)
		{
			waitpid(tmp_pipe->child_pid, &status, 0);
			if (WIFEXITED(status))
				minish->exit_status = WEXITSTATUS(status);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
				print_error("Quit (core dumped)", NULL, NULL);
		}
		tmp_pipe = tmp_pipe->next;
	}
	check_signal(minish);
}

int	get_good_fd(int pipread, int fd[2], int pip[2], t_divpipe *divpipe)
{
	if (fd[0] == -1 && pipread != -1)
		fd[0] = pipread;
	if (fd[1] == -1 && pip[1] != -1 && divpipe->next)
		fd[1] = pip[1];
	return (pip[0]);
}

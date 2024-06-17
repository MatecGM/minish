/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 20:03:27 by mbico             #+#    #+#             */
/*   Updated: 2024/06/17 23:02:47 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    wait_all_pipe(t_minish *minish)
{
    t_divpipe	*tmp_pipe;
    int	        status;
    
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
}

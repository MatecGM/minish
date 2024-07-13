/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minish.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:47:22 by fparis            #+#    #+#             */
/*   Updated: 2024/07/13 20:51:16 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_all_heredoc(t_minish *minish)
{
	t_divpipe	*tmp_pipe;
	t_redirect	*tmp_red;

	if (!minish->divpipe)
		return ;
	tmp_pipe = minish->divpipe;
	while (tmp_pipe)
	{
		tmp_red = tmp_pipe->redirect;
		while (tmp_red)
		{
			if (tmp_red->heredoc_name)
			{
				unlink(tmp_red->heredoc_name);
				free(tmp_red->heredoc_name);
				tmp_red->heredoc_name = NULL;
			}
			tmp_red = tmp_red->next;
		}
		tmp_pipe = tmp_pipe->next;
	}
}

void	close_all_fd(void)
{
	int	i;

	i = 2;
	while (i++ < 1023)
		close(i);
}

void	free_minish(t_minish *minish)
{
	if (!minish)
		return ;
	close_all_fd();
	if (minish->to_free)
		free(minish->to_free);
	if (minish->env)
		ft_free_tab(minish->env);
	minish->env = NULL;
	if (minish->divpipe)
		ft_free_pipe(minish->divpipe);
	minish->divpipe = NULL;
	rl_clear_history();
}

void	exit_free(t_minish *minish, int exit_code)
{
	unlink_all_heredoc(minish);
	free_minish(minish);
	if (!exit_code)
		exit_code = minish->exit_status;
	exit(exit_code);
}

void	exit_free_fork(t_minish *minish, int exit_code)
{
	free_minish(minish);
	if (!exit_code)
		exit_code = minish->exit_status;
	exit(exit_code);
}

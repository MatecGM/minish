/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freepipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:51:35 by fparis            #+#    #+#             */
/*   Updated: 2024/06/04 22:56:35 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pipe(t_divpipe *pipe)
{
	if (!pipe)
		return ;
	if (pipe->cmd_path && pipe->cmd_path != pipe->cmd[0])
		free(pipe->cmd_path);
	if (pipe->next)
		ft_free_pipe(pipe->next);
	if (pipe->cmd)
		ft_free_tab(pipe->cmd);
	if (pipe->redirect)
		ft_freered(pipe->redirect);
	free(pipe);
}

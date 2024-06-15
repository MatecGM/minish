/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:58:31 by mbico             #+#    #+#             */
/*   Updated: 2024/06/14 22:07:32 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_infile(char *arg, t_redirect *red, int *fd, t_minish *minish)
{
	if (fd[0] != -1)
		close(fd[0]);
	if (!minish)
		return ;
	fd[0] = open(arg, O_RDONLY);
}

void	ft_outfile(char *arg, t_redirect *red, int *fd, t_minish *minish)
{
	if (fd[1] != -1)
		close(fd[1]);
	if (!minish)
		return ;
	fd[1] = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	ft_heredoc(char *arg, t_redirect *red, int *fd, t_minish *minish)
{
	char	*name;

	if (!minish)                                              
		return ;
	name = create_heredoc(arg, minish, red);
	//if (!name)
	if (fd[0] != -1)
		close(fd[0]);
	fd[0] = open(name, O_RDONLY);
	free(name);
}

void	ft_outappend(char *arg, t_redirect *red, int *fd, t_minish *minish)
{
	if (fd[1] != -1)
		close(fd[1]);
	if (!minish)
		return ;
	fd[1] = open(arg, O_WRONLY | O_CREAT, 0644);
}

void	ft_redirection(t_redirect *red, int *fd, t_minish *minish)
{
	const void (*fred[4])(char *, t_redirect *, int *, t_minish *) = {ft_infile, 
		ft_outfile, ft_heredoc, ft_outappend};
	t_redirect	*ptr;

	ptr = red;
	while (ptr)
	{
		fred[ptr->type - 2](ptr->arg, ptr, fd, minish);
		ptr = ptr->next;
	}
}

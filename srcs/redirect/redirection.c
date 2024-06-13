/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:58:31 by mbico             #+#    #+#             */
/*   Updated: 2024/06/13 19:36:02 by fparis           ###   ########.fr       */
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

void	ft_redirection(t_redirect *red, int *fd, int *pip)
{
	const void (*fred[4])(char *, t_redirect *, int *, t_minish *) = {ft_infile, ft_outfile, ft_heredoc, ft_outappend};
	t_redirect	*ptr;

	ptr = red;
	while (ptr)
	{
		fred[ptr->type - 2](ptr->arg, ptr, fd, minish);
		ptr = ptr->next;
	}
	if (fd[0] == -1 && pip[0] != -1)
		fd[0] = pip[0];
	else if (fd[0] == -1)
		fd[0] = 0;
	if (fd[1] == -1 && pip[1] != -1)
		fd[1] = pip[1];
	else if (fd[1] == -1)
		fd[1] = 1;
}

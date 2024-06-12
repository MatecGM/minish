/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:58:31 by mbico             #+#    #+#             */
/*   Updated: 2024/06/12 18:37:37 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_infile(char *arg, t_bool quote, int *fd)
{
	if (fd[0] != -1)
		close(fd[0]);
	fd[0] = open(arg, O_RDONLY);
}

void	ft_outfile(char *arg, t_bool quote, int *fd)
{
	if (fd[1] != -1)
		close(fd[1]);
	fd[1] = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	ft_heredoc(char *arg, t_bool quote, int *fd)
{
	char	*name;

	name = create_heredoc(arg);
	//if (!name)
	if (fd[0] != -1)
		close(fd[0]);
	fd[0] = open(name, O_RDONLY);
	free(name);
}

void	ft_outappend(char *arg, t_bool quote, int *fd)
{
	if (fd[1] != -1)
		close(fd[1]);
	fd[1] = open(arg, O_WRONLY | O_CREAT, 0644);
}

void	ft_redirection(t_redirect *red, int *fd, int *pip)
{
	const void (*fred[4])(char *, t_bool, int *) = {ft_infile, ft_outfile, ft_heredoc, ft_outappend};
	t_redirect	*ptr;

	ptr = red;
	while (ptr)
	{
		fred[ptr->type - 2](ptr->arg, ptr->quote, fd);
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

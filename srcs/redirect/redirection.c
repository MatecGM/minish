/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:58:31 by mbico             #+#    #+#             */
/*   Updated: 2024/06/10 17:49:13 by mbico            ###   ########.fr       */
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
}

void	ft_outappend(char *arg, t_bool quote, int *fd)
{
	if (fd[1] != -1)
		close(fd[1]);
	fd[1] = open(arg, O_WRONLY | O_CREAT, 0644);
}

void	ft_redirection(t_redirect *red)
{
	void (*fred[4])(char *, t_bool, int *) = {ft_infile, ft_outfile, ft_heredoc, ft_outappend};
	int	fd[2];
	t_redirect	*ptr;

	ptr = red;
	fd[0] = -1;
	fd[1] = -1;
	while (ptr)
	{
		fred[ptr->type - 2](ptr->arg, ptr->quote, fd);
		ptr = ptr->next;
	}

}

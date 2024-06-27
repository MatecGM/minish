/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:58:31 by mbico             #+#    #+#             */
/*   Updated: 2024/06/27 19:19:56 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const int	ft_infile(char *arg, t_redirect *red, int *fd, t_minish *minish)
{
	char	*extend;

	extend = extender(ft_strdup(arg), minish, FALSE);
	if (!extend)
		return (0);
	if (ft_ambiguous_checker(arg) && ft_hasspace(extend))
	{
		print_error("minishell: ", arg, ": ambiguous redirect");
		free(extend);
		fd[0] = -2;
		return (1);
	}
	if (fd[0] != -1)
		close(fd[0]);
	if (!minish)
		return (0);
	fd[0] = open(arg, O_RDONLY);
	free(extend);
	return (1);
}

const int	ft_outfile(char *arg, t_redirect *red, int *fd, t_minish *minish)
{
	char	*extend;

	extend = extender(ft_strdup(arg), minish, FALSE);
	if (!extend)
		return (0);
	if (ft_ambiguous_checker(arg) && ft_hasspace(extend))
	{
		print_error("minishell: ", arg, ": ambiguous redirect");
		free(extend);
		fd[1] = -2;
		return (1);
	}
	if (fd[1] != -1)
		close(fd[1]);
	if (!minish)
		return (0);
	fd[1] = open(extend, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(extend);
	return (1);
}

const int	ft_heredoc(char *arg, t_redirect *red, int *fd, t_minish *minish)
{
	char	*name;

	if (!minish)
		return (0);
	name = create_heredoc(arg, minish, red);
	if (!name)
		return (0);
	if (fd[0] != -1)
		close(fd[0]);
	fd[0] = open(name, O_RDONLY);
	return (1);
}

const int	ft_outappend(char *arg, t_redirect *red, int *fd, t_minish *minish)
{
	char	*extend;

	extend = extender(ft_strdup(arg), minish, FALSE);
	if (!extend)
		return (0);
	if (ft_ambiguous_checker(arg) && ft_hasspace(extend))
	{
		print_error("minishell: ", arg, ": ambiguous redirect");
		free(extend);
		fd[1] = -2;
		return (1);
	}
	if (fd[1] != -1)
		close(fd[1]);
	if (!minish)
		return (0);
	fd[1] = open(extend, O_WRONLY | O_CREAT | O_APPEND, 0666);
	free(extend);
	return (1);
}

void	ft_redirection(t_redirect *red, int *fd, t_minish *minish)
{
	const int	(*fred[4])(char *, t_redirect *, int *, t_minish *)
		= {ft_infile, ft_outfile, ft_heredoc, ft_outappend};
	t_redirect	*ptr;

	ptr = red;
	while (ptr)
	{
		if (!(fd[0] == -2 || fd[1] == -2))
			fred[ptr->type - 2](ptr->arg, ptr, fd, minish);
		if (g_signal)
			return ;
		ptr = ptr->next;
	}
}

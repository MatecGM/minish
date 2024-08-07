/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:46:10 by fparis            #+#    #+#             */
/*   Updated: 2024/07/08 18:37:37 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*try_new_name(char *name)
{
	int		i;
	char	*old_name;

	old_name = NULL;
	i = 1;
	while (name[i] == 'Z')
		i++;
	if (name[i])
		name[i]++;
	else
	{
		i = 1;
		while (name[i])
		{
			name[i] = 'A';
			i++;
		}
		old_name = name;
		name = ft_strjoin(name, "A");
		free(old_name);
	}
	return (name);
}

char	*get_heredoc_name(void)
{
	char	*name;

	name = ft_calloc(3, sizeof(char));
	if (!name)
		return (NULL);
	name[0] = '.';
	name[1] = 'A';
	while (access(name, F_OK) == 0)
	{
		name = try_new_name(name);
		if (!name)
			return (NULL);
	}
	return (name);
}

int	write_user_entry(int fd, char *heredoc_EOF,
			t_redirect *red, t_minish *minish)
{
	char	*line;

	line = readline("> ");
	while (line && ft_strcmp(line, heredoc_EOF))
	{
		if (!red->quote)
			line = extender(line, minish, TRUE);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
		line = readline("> ");
	}
	if (!line)
	{
		ft_putstr_fd("minish: warning: here-document delimited by", 2);
		ft_putstr_fd(" end-of-file (wanted `", 2);
		ft_putstr_fd(heredoc_EOF, 2);
		ft_putstr_fd("')\n", 2);
	}
	else
		free(line);
	return (1);
}

int	create_heredoc_fork(int fd, char *heredoc_EOF,
		t_minish *minish, t_redirect *red)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (0);
	if (!pid)
	{
		if (signal(SIGINT, signal_heredoc) == SIG_ERR)
			exit_free(minish, -1);
		manage_static_minish(minish);
		write_user_entry(fd, heredoc_EOF, red, minish);
		exit_free_fork(minish, 0);
	}
	waitpid(pid, NULL, 0);
	return (1);
}

char	*create_heredoc(char *heredoc_EOF, t_minish *minish, t_redirect *red)
{
	int		heredoc_fd;
	char	*heredoc_name;

	heredoc_name = get_heredoc_name();
	if (!heredoc_name || signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (NULL);
	red->heredoc_name = heredoc_name;
	heredoc_fd = open(heredoc_name, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (heredoc_fd == -1)
	{
		free(heredoc_name);
		return (NULL);
	}
	if (!create_heredoc_fork(heredoc_fd, heredoc_EOF, minish, red))
	{
		close(heredoc_fd);
		free(heredoc_name);
		return (NULL);
	}
	close(heredoc_fd);
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)
		return (NULL);
	return (heredoc_name);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:46:47 by fparis            #+#    #+#             */
/*   Updated: 2024/07/04 17:54:14 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char	*cmd)
{
	if (!strcmp(cmd, "export") || !strcmp(cmd, "echo") || !strcmp(cmd, "cd")
		|| !strcmp(cmd, "pwd") || !strcmp(cmd, "unset") || !strcmp(cmd, "env")
		|| !strcmp(cmd, "exit"))
		return (1);
	return (0);
}

t_divpipe	*try_builtins(t_divpipe	*divpipe, t_minish *minish, int fd)
{
	if (fd == -1)
		fd = 1;
	if (!strcmp(divpipe->cmd[0], "export"))
		ft_export(divpipe->cmd, minish, fd);
	else if (!strcmp(divpipe->cmd[0], "echo"))
		ft_echo(divpipe->cmd, minish, fd);
	else if (!strcmp(divpipe->cmd[0], "cd"))
		ft_cd(divpipe->cmd, minish, fd);
	else if (!strcmp(divpipe->cmd[0], "pwd"))
		ft_pwd(divpipe->cmd, minish, fd);
	else if (!strcmp(divpipe->cmd[0], "unset"))
		ft_unset(divpipe->cmd, minish);
	else if (!strcmp(divpipe->cmd[0], "env"))
		ft_env(divpipe->cmd, minish->env, minish, fd);
	else if (!strcmp(divpipe->cmd[0], "exit"))
		ft_exit(divpipe->cmd, minish);
	else
		return (NULL);
	return (divpipe);
}

void	exec_fork(t_divpipe	*divpipe, t_minish *minish, int *fd)
{
	if (fd[0] != -1)
		dup2(fd[0], 0);
	if (fd[1] != -1)
		dup2(fd[1], 1);
	close_all_fd();
	if (execve(divpipe->cmd_path, divpipe->cmd, minish->env) == -1)
		perror("minish");
	exit_free_fork(minish, 1);
}

void	ft_execpipes(t_divpipe *divpipe, t_minish *minish)
{
	int	fd[2];
	int	pip[2];
	int	pipread;

	pip[0] = -1;
	pip[1] = -1;
	pipread = -1;
	while (divpipe)
	{
		if (divpipe->next)
			if (pipe(pip) == -1)
				exit_free(minish, 1);
		fd[0] = -1;
		fd[1] = -1;
		ft_redirection(divpipe->redirect, fd, minish);
		if (check_signal(minish))
			break ;
		pipread = get_good_fd(pipread, fd, pip, divpipe);
		if (!(fd[0] == -2 || fd[1] == -2))
			executer(divpipe, minish, fd);
		if (divpipe->next)
			close(pip[1]);
		divpipe = divpipe->next;
	}
	wait_all_pipe(minish);
}

t_divpipe	*executer(t_divpipe	*divpipe, t_minish *minish, int *fd)
{
	int	child_pid;

	if (!divpipe->cmd || !divpipe->cmd[0] || !divpipe->cmd[0][0])
		return (divpipe);
	if (try_builtins(divpipe, minish, fd[1]))
		return (divpipe);
	if (!divpipe->cmd_path)
	{
		print_error(divpipe->cmd[0], ": command not found", NULL);
		minish->exit_status = 127;
		return (NULL);
	}
	child_pid = fork();
	if (child_pid == 0)
		exec_fork(divpipe, minish, fd);
	divpipe->child_pid = child_pid;
	return (divpipe);
}

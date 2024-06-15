/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:46:47 by fparis            #+#    #+#             */
/*   Updated: 2024/06/15 18:29:08 by mbico            ###   ########.fr       */
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
		ft_exit(divpipe->cmd, minish, fd);
	else if (!strcmp(divpipe->cmd[0], "heredoc"))
		create_heredoc("EOF", minish, divpipe->redirect);
	else
		return (NULL);
	return (divpipe);
}

void	exec_fork(t_divpipe	*divpipe, t_minish *minish, int *fd)
{
	
	if (fd[0] != -1)
		dup2(fd[0],0);
	if (fd[1] != -1)
		dup2(fd[1],1);
	close(fd[0]);
	close(fd[1]);
	signal(SIGQUIT, SIG_DFL);
	if (execve(divpipe->cmd_path, divpipe->cmd, minish->env) == -1)
	{
		perror("minish");
		exit_free(minish, 1);
	}
}

void	ft_execpipes(t_divpipe	*divpipe, t_minish *minish)
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
			pipe(pip);
		fd[0] = -1;
		fd[1] = -1;
		ft_redirection(divpipe->redirect, fd, minish);
		if (check_signal())
			break;
		if (fd[0] == -1 && pipread != -1)
			fd[0] = pipread;
		if (fd[1] == -1 && pip[1] != -1 && divpipe->next)
			fd[1] = pip[1];
		executer(divpipe, minish, fd);
		if (divpipe->next)
			close(pip[1]);
		pipread = pip[0];
		if (check_signal())
			break;
		divpipe = divpipe->next;
	}
	wait_all_pipe(minish);
}


t_divpipe	*executer(t_divpipe	*divpipe, t_minish *minish, int *fd)
{
	int	child_pid;

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:46:47 by fparis            #+#    #+#             */
/*   Updated: 2024/06/12 18:42:12 by mbico            ###   ########.fr       */
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

t_divpipe	*try_builtins(t_divpipe	*divpipe, t_minish *minish)
{
	if (!strcmp(divpipe->cmd[0], "export"))
		ft_export(divpipe->cmd, minish);
	else if (!strcmp(divpipe->cmd[0], "echo"))
		ft_echo(divpipe->cmd, minish);
	else if (!strcmp(divpipe->cmd[0], "cd"))
		ft_cd(divpipe->cmd, minish);
	else if (!strcmp(divpipe->cmd[0], "pwd"))
		ft_pwd(divpipe->cmd, minish);
	else if (!strcmp(divpipe->cmd[0], "unset"))
		ft_unset(divpipe->cmd, minish);
	else if (!strcmp(divpipe->cmd[0], "env"))
		ft_env(divpipe->cmd, minish->env, minish);
	else if (!strcmp(divpipe->cmd[0], "exit"))
		ft_exit(divpipe->cmd, minish);
	else
		return (NULL);
	return (divpipe);
}

void	exec_fork(t_divpipe	*divpipe, t_minish *minish, int *fd)
{
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	ft_printf("%d\n", fd[0]);
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

	pip[0] = -1;
	pip[1] = -1;
	while (divpipe)
	{
		fd[0] = -1;
		fd[1] = -1;
		ft_redirection(divpipe->redirect, fd, pip);
		executer(divpipe, minish, fd);
		if (pip[0] != -1)
			close(pip[0]);
		if (pip[1] != -1)
			close(pip[1]);
		if (divpipe->next)
			pipe(pip);
		divpipe = divpipe->next;
	}
}


t_divpipe	*executer(t_divpipe	*divpipe, t_minish *minish, int *fd)
{
	int	child_pid;
	int	status;

	if (try_builtins(divpipe, minish))
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
	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
		minish->exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
 		print_error("Quit (core dumped)", NULL, NULL);
	return (divpipe);
}

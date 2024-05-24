/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:46:47 by fparis            #+#    #+#             */
/*   Updated: 2024/05/24 22:07:14 by fparis           ###   ########.fr       */
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

t_divpipe	*try_builtins(t_divpipe	*divpipe, char ***env)
{
	if (!strcmp(divpipe->cmd[0], "export"))
		ft_export(divpipe->cmd, env);
	else if (!strcmp(divpipe->cmd[0], "echo"))
		ft_echo(divpipe->cmd);
	else if (!strcmp(divpipe->cmd[0], "cd"))
		ft_cd(divpipe->cmd);
	else if (!strcmp(divpipe->cmd[0], "pwd"))
		ft_pwd(divpipe->cmd);
	else if (!strcmp(divpipe->cmd[0], "unset"))
		ft_unset(divpipe->cmd, env);
	else if (!strcmp(divpipe->cmd[0], "env"))
		ft_env(divpipe->cmd, *env);
	else
		return (NULL);
	return (divpipe);
}

t_divpipe	*executer(t_divpipe	*divpipe, char ***env)
{
	int	child_pid;

	if (try_builtins(divpipe, env))
		return (divpipe);
	if (!divpipe->cmd_path)
	{
		print_error(divpipe->cmd[0], ": command not found", NULL);
		return (NULL);
	}
	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(divpipe->cmd_path, divpipe->cmd, *env) == -1)
			return (NULL); //exit free
	}
	waitpid(child_pid, NULL, 0);
	return (divpipe);
}

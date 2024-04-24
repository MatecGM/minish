/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:57:34 by fparis            #+#    #+#             */
/*   Updated: 2024/04/24 03:49:02 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_beautiful_header()
{
	char	*line;
	int		fd;
	int		fd_stdin;

	printf ("\033c\033[0;35m");
	fd = open("beautiful header", O_RDONLY);
	fd_stdin = dup(0);
	dup2(fd, 0);
	line = readline("");
	while (line)
		line = readline("");
	printf("\033[0m\n\n\n\n");
	dup2(fd_stdin, 0);
	close(fd);
}

void	parse(char *str, char ***env)
{
	int		i;
	char	**splitted;
	char	*tmp;
	int		pid;

	i = 0;
	splitted = ft_split_quote(str);
	if (!strcmp(splitted[0], "export"))
		ft_export(splitted, env);
	else if (!strcmp(splitted[0], "echo"))
		ft_echo(splitted);
	else if (!strcmp(splitted[0], "cd"))
		ft_cd(splitted);
	else if (!strcmp(splitted[0], "pwd"))
		ft_pwd(splitted);
	else if (!strcmp(splitted[0], "unset"))
		ft_unset(splitted, env);
	else if (!strcmp(splitted[0], "env"))
		ft_env(splitted, *env);
	else
	{
		tmp = ft_strjoin("/bin/", splitted[0]);
		pid = fork();
		if (!pid)
		{
			execve(tmp, splitted, *env);
			exit (0);
		}
		waitpid(pid, NULL, 0);
		free(tmp);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	char	**new_env;

	//mettre la variable d'env SHLVL en + 1 + CREER PWD SI EXISTE PAS
	new_env = dup_env_tab(env);
	print_beautiful_header();
	init_signal_handler();
	str = NULL;
	while (1)
	{
		interactive_mode(TRUE, 1);
		str = readline("ඞ-> ");
		if (str && str[0])
		{
			add_history(str);
			interactive_mode(TRUE, 0);
			parse(str, &new_env);
		}
		else if (!str)
			break ;
	}
	printf("\ncfini\n");
}

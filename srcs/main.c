/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:57:34 by fparis            #+#    #+#             */
/*   Updated: 2024/05/20 20:11:40 by mbico            ###   ########.fr       */
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
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("\033[0m\n\n\n\n");
	close(fd);
}

// void	parse(char *str, char ***env)
// {
// 	int		exit_status;
// 	char	**splitted;
// 	char	*tmp;
// 	int		pid;

// 	splitted = ft_split_quote(str);
// 	if (!strcmp(splitted[0], "export"))
// 		ft_export(splitted, env);
// 	else if (!strcmp(splitted[0], "echo"))
// 		ft_echo(splitted);
// 	else if (!strcmp(splitted[0], "cd"))
// 		ft_cd(splitted);
// 	else if (!strcmp(splitted[0], "pwd"))
// 		ft_pwd(splitted);
// 	else if (!strcmp(splitted[0], "unset"))
// 		ft_unset(splitted, env);
// 	else if (!strcmp(splitted[0], "env"))
// 		ft_env(splitted, *env);
// 	else
// 	{
// 		tmp = ft_strjoin("/bin/", splitted[0]);
// 		pid = fork();
// 		if (!pid)
// 		{
// 			signal(SIGQUIT, SIG_DFL);
// 			execve(tmp, splitted, *env);
// 			exit (0);
// 		}
// 		waitpid(pid, &exit_status, 0);
// 		free(tmp);
// 		if (WIFSIGNALED(exit_status) && WTERMSIG(exit_status) == SIGQUIT)
// 			print_error("Quit (core dumped)", NULL, NULL);
// 	}
// }

int	main(int argc, char **argv, char **env)
{
	t_divpipe	*divpipe;
	int			i;
	char	**new_env;
	char	*str;

	//mettre la variable d'env SHLVL en + 1 + CREER PWD SI EXISTE PAS
	if (init_signal_handler())
		exit(1);
	new_env = dup_env_tab(env);
	print_beautiful_header();
	str = NULL;
	while (1)
	{
		interactive_mode(TRUE, 1);
		str = readline("\U00000D9E-> ");
		if (str && str[0])
		{
			add_history(str);
			interactive_mode(TRUE, 0);
			divpipe = ft_parsing(str, new_env);
			
			ft_printf("\n===================\n");
			while(divpipe)
			{
				i = 0;
				ft_printf("cmd = ");
				while (divpipe->cmd[i])
				{
					ft_printf("%s ", divpipe->cmd[i]);
					i ++;
				}
				ft_printf("\nredirection :\n");
				while (divpipe->redirect)
				{
					ft_printf("type = %d, arg = %s, quote = %d\n", divpipe->redirect->type, divpipe->redirect->arg, divpipe->redirect->quote);
					divpipe->redirect = divpipe->redirect->next;
				}
				divpipe = divpipe->next;
				ft_printf("===================\n");
			}

		}
		else if (!str)
			break ;
	}
	printf("exit\n");
	












	// char	*str;
	// char	**new_env;

	// //mettre la variable d'env SHLVL en + 1 + CREER PWD SI EXISTE PAS
	// if (init_signal_handler())
	// 	exit(1);
	// new_env = dup_env_tab(env);
	// print_beautiful_header();
	// str = NULL;
	// while (1)
	// {
	// 	interactive_mode(TRUE, 1);
	// 	str = readline("ඞ-> ");
	// 	if (str && str[0])
	// 	{
	// 		add_history(str);
	// 		interactive_mode(TRUE, 0);
	// 		parse(str, &new_env);
	// 	}
	// 	else if (!str)
	// 		break ;
	// }
	// printf("exit\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 00:23:18 by fparis            #+#    #+#             */
/*   Updated: 2024/07/09 19:50:55 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_beautiful_header(void)
{
	char	*line;
	int		fd;

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

void	init_minish(t_minish *minish, char **env)
{
	ft_bzero(minish, sizeof(t_minish));
	if (init_signal_handler())
		exit(1);
	minish->env = dup_env_tab(env);
	if (!minish->env)
		exit(1);
	print_beautiful_header();
	update_shlvl(minish);
	update_pwd(minish, "PWD=");
}

void	get_input(t_minish *minish, char *str)
{
	t_divpipe	*tmp_pipe;

	add_history(str);
	interactive_mode(TRUE, 0);
	minish->divpipe = ft_parsing(str, minish);
	free(str);
	if (!minish->divpipe)
		exit_free(minish, 1);
	if (!put_paths(minish->divpipe, minish->env))
		exit_free(minish, 1);
	tmp_pipe = minish->divpipe;
	minish->in_pipe = minish->divpipe->next != NULL;
	update_underscore(minish);
	if (!minish->synt_err)
		ft_execpipes(tmp_pipe, minish);
	unlink_all_heredoc(minish);
	if (minish->divpipe)
		ft_free_pipe(minish->divpipe);
	minish->divpipe = NULL;
	minish->synt_err = FALSE;
}

int	main(__attribute__((unused)) int argc,
		__attribute__((unused)) char **argv, char **env)
{
	t_minish	minish;
	char		*str;

	init_minish(&minish, env);
	str = NULL;
	while (1)
	{
		get_exit_status(0, &minish);
		interactive_mode(TRUE, 1);
		str = readline("\001\U00000D9E\002-> ");
		if (str && str[0])
			get_input(&minish, str);
		else if (!str)
			break ;
	}
	ft_putstr_fd("exit\n", 2);
	exit_free(&minish, 0);
}

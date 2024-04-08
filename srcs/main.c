/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:57:34 by fparis            #+#    #+#             */
/*   Updated: 2024/04/08 18:39:18 by fparis           ###   ########.fr       */
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
	printf("\033[0;37m\n\n\n\n");
	dup2(fd_stdin, 0);
	close(fd);
}

void	parse(char *str)
{
	int		i;
	char	**splitted;

	i = 0;
	splitted = ft_tokenizer(str);
	while (splitted && splitted[i])
	{
		printf("-%s-\n", splitted[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*str;

	print_beautiful_header();
	while (1)
	{
		str = readline("ඞ-> ");
		if (str && str[0])
			add_history(str);
		parse(str);
	}
}

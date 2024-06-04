/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minish.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:47:22 by fparis            #+#    #+#             */
/*   Updated: 2024/06/04 22:32:17 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_minish(t_minish *minish)
{
	if (!minish)
		return ;
	if (minish->env)
		ft_free_tab(minish->env);
	minish->env = NULL;
	if (minish->divpipe)
		ft_free_pipe(minish->divpipe);
	minish->divpipe = NULL;
}

void	exit_free(t_minish *minish, int exit_code)
{
	free_minish(minish);
	exit(exit_code);
}

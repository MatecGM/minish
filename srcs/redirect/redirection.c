/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:58:31 by mbico             #+#    #+#             */
/*   Updated: 2024/06/05 18:00:18 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_infile(char *arg, t_bool quote)
{
	ft_printf("infile\n");
}

void	ft_outfile(char *arg, t_bool quote)
{
	ft_printf("outfile\n");
}

void	ft_heredoc(char *arg, t_bool quote)
{
	ft_printf("heredoc\n");
}

void	ft_outappend(char *arg, t_bool quote)
{
	ft_printf("outappend\n");
}

void	ft_redirection(t_redirect *red)
{
	void (*fred[4])(char *, t_bool) = {ft_infile, ft_outfile, ft_heredoc, ft_outappend};
	t_redirect	*ptr;

	ptr = red;
	while (ptr)
	{
		fred[ptr->type-2](ptr->arg, ptr->quote);
		ptr = ptr->next;
	}
}

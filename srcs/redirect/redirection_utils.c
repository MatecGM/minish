/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:14:17 by mbico             #+#    #+#             */
/*   Updated: 2024/07/09 19:43:46 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_ambiguous_checker(char *str)
{
	size_t	len;

	if (str[0] != '$')
		return (FALSE);
	len = 1;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len ++;
	if (len == ft_strlen(str))
		return (TRUE);
	return (FALSE);
}

t_bool	ft_hasspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			return (TRUE);
		i ++;
	}
	return (FALSE);
}

void	check_access_red(int *fd, char *name, t_minish *minish)
{
	if (*fd != -1)
		return ;
	if (access(name, F_OK) == -1)
		print_error("minish: ", name, ": No such file or directory");
	else
		print_error("minish: ", name, ": Permission denied");
	*fd = -2;
	minish->exit_status = 1;
}

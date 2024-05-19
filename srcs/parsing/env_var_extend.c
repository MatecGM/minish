/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_extend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:22:33 by mbico             #+#    #+#             */
/*   Updated: 2024/05/19 16:07:14 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**extender(char **toked)
{
	t_type	ltype;

	ltype = tnull;
	while (*toked)
	{
		ltype = typage(*toked);
		free(*toked);
		toked ++;
	}
}

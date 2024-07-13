/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:11:29 by mbico             #+#    #+#             */
/*   Updated: 2024/07/14 01:15:47 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_chardup(char c, int i)
{
	char	*str;

	str = ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (i > 0)
	{
		str[i - 1] = c;
		i --;
	}
	return (str);
}

t_bool	ft_strisspace(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (FALSE);
		str ++;
	}
	return (TRUE);
}

void	ft_syntax_error(int i,	t_minish *minish, char **toked, t_bool pip)
{
	char	*err;

	if (!minish->synt_err && (ft_strlen(toked[i]) > 2
			&& (toked[i][0] == '<' || toked[i][0] == '>')))
	{
		err = ft_chardup(toked[i][0], ft_strlen(toked[i]) - 2);
		print_error("minishell: syntax error near unexpected token `", err, "'");
		free(err);
		minish->synt_err = TRUE;
	}
	else if (!minish->synt_err && ((toked[i][0] == '|'
			&& ft_strlen(toked[i]) > 1)
		|| (toked[i][0] == '|' && pip == TRUE)))
	{
		ft_putstr_fd("minish: syntax error near unexpected token `|'\n", 2);
		minish->synt_err = TRUE;
	}
}

void	ft_syntax_checker(char **toked, t_minish *minish)
{
	int		i;
	t_bool	pip;

	i = 0;
	pip = FALSE;
	while (toked[i])
	{
		ft_syntax_error(i, minish, toked, pip);
		if (toked[i][0] == '|')
			pip = TRUE;
		else if (!ft_strisspace(toked[i]))
			pip = FALSE;
		i ++;
	}
}

t_bool	ft_hasdollars(char *str)
{
	while (str && *str)
	{
		if (*str == '$')
			return (TRUE);
		str ++;
	}
	return (FALSE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:11:29 by mbico             #+#    #+#             */
/*   Updated: 2024/06/27 18:48:49 by mbico            ###   ########.fr       */
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

void	ft_syntax_checker(char **toked, t_minish *minish)
{
	int		i;
	t_type	type;
	char	*err;
	t_bool	pip;

	i = 0;
	pip = FALSE;
	while (toked[i])
	{
		if (!minish->synt_err && (ft_strlen(toked[i]) > 2 && (toked[i][0] == '<'
			|| toked[i][0] == '>')))
		{
			err = ft_chardup(toked[i][0], ft_strlen(toked[i]) - 2);
			print_error("minishell: syntax error near unexpected `", err, "'");
			free(err);
			minish->synt_err = TRUE;
		}
		if (!minish->synt_err && ((toked[i][0] == '|' && ft_strlen(toked[i]) > 1)
			|| (toked[i][0] == '|' && pip == TRUE)))
		{
			ft_putstr_fd("minishell: syntax error near unexpected `|'\n", 2);
			minish->synt_err = TRUE;
		}
		if (toked[i][0] == '|')
			pip = TRUE;
		else if (!ft_strisspace(toked[i]))
			pip = FALSE;
		i ++;
	}
}

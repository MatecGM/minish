/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:44:59 by mbico             #+#    #+#             */
/*   Updated: 2024/07/08 19:10:38 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_delimiter(char *str, int index)
{
	if ((str[index] == '|' || str[index] == '>' || str[index] == '<')
		&& !ft_inquote(str, index))
		return (TRUE);
	return (FALSE);
}

static int	countel(char *str)
{
	int		nb;
	int		i;

	nb = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] && !is_delimiter(str, i))
			nb++;
		while (str[i] && !is_delimiter(str, i))
			i++;
		if (str[i] && is_delimiter(str, i))
			nb++;
		while (str[i] && is_delimiter(str, i))
			i++;
	}
	return (nb);
}

int	split_tab(char *str, int i, int *i_tab, char **tab)
{
	t_bool	type;
	int		end;
	int		j;

	type = is_delimiter(str, i);
	end = i;
	while (str[end] && is_delimiter(str, end) == type)
		end++;
	tab[*i_tab] = ft_calloc((end - i) + 1, sizeof(char));
	if (!tab[*i_tab])
		return (-1);
	j = 0;
	while (i < end)
	{
		tab[*i_tab][j] = str[i];
		i++;
		j++;
	}
	*i_tab += 1;
	return (i);
}

static void	free_all_tab(char **tab, char *str)
{
	int	i;

	if (str)
		free(str);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**ft_tokenizer(char *str)
{
	int		len;
	char	**tab;
	int		i;
	int		i_tab;

	len = countel(str);
	tab = ft_calloc((len + 1), sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	i_tab = 0;
	while (str[i])
	{
		i = split_tab(str, i, &i_tab, tab);
		if (i == -1)
		{
			free_all_tab(tab, str);
			return (NULL);
		}
	}
	return (tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:44:59 by mbico             #+#    #+#             */
/*   Updated: 2024/06/18 00:15:20 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_delimiter(char chara)
{
	if (chara == '|' || chara == '>' || chara == '<')
		return (TRUE);
	return (FALSE);
}

static int	countel(char *str)
{
	int		nb;
	char	*ptr;

	nb = 0;
	ptr = str;
	while (*ptr)
	{
		if (*ptr && !is_delimiter(*ptr))
			nb++;
		while (*ptr && !is_delimiter(*ptr))
			ptr++;
		if (*ptr && is_delimiter(*ptr))
			nb++;
		while (*ptr && is_delimiter(*ptr))
			ptr++;
	}
	return (nb);
}

int	split_tab(char *str, int i, int *i_tab, char **tab)
{
	t_bool	type;
	int		end;
	int		j;

	type = is_delimiter(str[i]);
	end = i;
	while (str[end] && is_delimiter(str[end]) == type)
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

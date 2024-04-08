/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:44:59 by mbico             #+#    #+#             */
/*   Updated: 2024/04/08 18:50:03 by fparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_delimiter(char chara)
{	
	if (chara == '|' || chara == '>' || chara == '<' || chara == '&')
		return (TRUE);
	return (FALSE);
}

static int	countel(char *str)
{
	int		nb;
	char	*ptr;

	nb = 0;
	ptr = str;
	while(*ptr)
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
	int	type;
	int end;
	int	i2;

	type = 0;
	if (is_delimiter(str[i]))
		type = 1;
	end = i;
	while (str[end] && is_delimiter(str[end]) == type)
		end++;
	tab[*i_tab] = malloc((end - i) * sizeof(char));
	if (!tab[*i_tab])
		return (-1);
	i2 = 0;
	while (i < end)
	{
		tab[*i_tab][i2] = str[i];
		i++;
		i2++;
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
	tab = malloc((len + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab[len] = NULL;
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
	free(str);
	return (tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:30:55 by mbico             #+#    #+#             */
/*   Updated: 2024/05/07 16:14:36 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **splitted_char)
{
	int	i;

	i = 0;
	while (splitted_char && splitted_char[i])
	{
		free(splitted_char[i]);
		i ++;
	}
	free(splitted_char);
}

char	**ft_realloc(char **tab)
{
	int		len;
	char	**dst;
	int		i;

	len = 0;
	while (tab && tab[len])
		len++;
	dst = ft_calloc(sizeof(char *), len + 2);
	if (!dst)
	{
		ft_free_tab(tab);
		return (NULL);
	}
	i = 0;
	while (tab && dst && tab[i])
	{
		dst[i] = tab[i];
		i++;
	}
	if (tab)
		free(tab);
	return (dst);
}

int	ft_quote_len(char *str)
{
	t_bool	quote;
	t_bool	single;
	int		len;

	quote = FALSE;
	single = FALSE;
	len = 0;
	while (*str == ' ')
		str ++;
	while (*str && !(*str == ' ' && !quote))
	{
		if (*str == '\'' && !quote)
			single = TRUE;
		else if (*str == '"' && !quote)
			single = FALSE;
		if ((*str == '\'' && single) || (*str == '"' && !single))
			quote = !quote;
		else
			len ++;
		str ++;
	}
	return (len);
}

char	*ft_word_filler(char *src, char *dst)
{
	t_bool	quote;
	t_bool	single;
	int		i;

	quote = FALSE;
	single = FALSE;
	i = 0;
	while (*src == ' ')
		src ++;
	while (dst && *src && !(*src == ' ' && !quote))
	{
		if (*src == '\'' && !quote)
			single = TRUE;
		else if (*src == '"' && !quote)
			single = FALSE;
		if ((*src == '\'' && single) || (*src == '"' && !single))
			quote = !quote;
		else
			dst[i++] = *src;
		src ++;
	}
	if (!*src && quote)
		ft_putstr_fd("Error: unclosed quote\n", 2);
	return (src);
}

char	**ft_split_quote(char *str)
{
	char	**cmd;
	int		j;
	int		len;

	cmd = NULL;
	j = 0;
	while (*str)
	{
		len = ft_quote_len(str);
		cmd = ft_realloc(cmd);
		if (!cmd)
			return (NULL);
		cmd[j] = ft_calloc(sizeof(char), len + 1);
		str = ft_word_filler(str, cmd[j]);
		if (!cmd[j] || !str)
		{
			ft_free_tab(cmd);
			return (NULL);
		}
		if (*str)
			str ++;
		j++;
	}
	return (cmd);
}

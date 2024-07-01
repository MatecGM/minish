/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:54:13 by mbico             #+#    #+#             */
/*   Updated: 2024/07/01 18:05:59 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_lostcmd(char **split, char **cmd)
{
	int		i;
	char	*tmp;

	i = 1;
	while (split[i])
	{
		tmp = *cmd;
		if (tmp)
		{
			*cmd = ft_vajoin(tmp, " ", split[i], NULL);
			if (!(*cmd))
			{
				ft_free_tab(split);
				return (1);
			}
			free(tmp);
			free(split[i]);
		}
		else
			*cmd = split[i];
		i ++;
	}
	free(split);
	return (0);
}

int	redirect_filler(t_divpipe *cpipe, char *arg, t_type ltype, char **cmd)
{
	t_redirect	*new;
	char		**split;

	split = ft_split_quote(arg);
	if (!split)
		return (1);
	new = ft_rednew(ltype, split[0]);
	if (!new)
	{
		ft_free_tab(split);
		return (1);
	}
	new->quote = ft_quote_first_arg(arg);
	ft_redadd_back(&(cpipe->redirect), new);
	if (ft_add_lostcmd(split, cmd))
		return (1);
	return (0);
}

void	ft_stock_cmd_in_minish(char *cmd, t_divpipe *cpipe, t_minish *minish)
{
	if (ft_hasdollars(cmd))
		cmd = extender(cmd, minish, FALSE);
	cpipe->cmd = ft_split_quote(cmd);
	free(cmd);
	if (!cpipe->cmd)
		exit_free(minish, 1);
}

int	inpipe(t_divpipe *cpipe, char **toked, int i, t_minish *minish)
{
	t_type		ltype;
	t_type		ctype;
	char		*cmd;

	ltype = tnull;
	cmd = NULL;
	while (toked[i] && ft_strcmp(toked[i], "|"))
	{
		ctype = typage(toked[i]);
		if (ctype == tnull)
		{
			if (ltype == tnull)
			{
				cmd = ft_strdup(toked[i]);
				if (!cmd)
					exit_free(minish, 1);
			}
			else if (redirect_filler(cpipe, toked[i], ltype, &cmd))
				exit_free(minish, 1);
		}
		ltype = ctype;
		i ++;
	}
	ft_stock_cmd_in_minish(cmd, cpipe, minish);
	return (i);
}

t_divpipe	*ft_parsing(char *input, t_minish *minish)
{
	char		**toked;
	t_divpipe	*divpipe;
	t_divpipe	*cpipe;
	int			i;

	divpipe = NULL;
	toked = ft_tokenizer(input);
	ft_syntax_checker(toked, minish);
	if (!toked)
		return (NULL);
	i = 0;
	while (toked[i])
	{
		cpipe = ft_pipenew();
		if (!cpipe)
			break ;
		cpipe->redirect = NULL;
		ft_pipeadd_back(&divpipe, cpipe);
		i = inpipe(cpipe, toked, i, minish);
		if (toked[i])
			i ++;
	}
	ft_free_tab(toked);
	return (divpipe);
}

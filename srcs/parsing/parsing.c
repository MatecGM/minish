/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:54:13 by mbico             #+#    #+#             */
/*   Updated: 2024/06/10 13:57:04 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type typage(char *elem)
{
	if (!ft_strcmp(elem, "<<"))
		return (theredoc);
	else if (!ft_strcmp(elem, ">>"))
		return (tappend);
	else if (!ft_strcmp(elem, "<"))
		return (tinfile);
	else if (!ft_strcmp(elem, ">"))
		return (toutfile);
	return (tnull);
}

void	redirect_filler(t_divpipe *cpipe, char *arg, t_type ltype, char **cmd)
{
	t_redirect	*new;
	char		**split;
	int			i;
	char		*tmp;

	split = ft_split_quote(arg);
	new = ft_rednew(ltype, split[0]); //a gerer
	new->quote = ft_quote_first_arg(arg);
	ft_redadd_back(&(cpipe->redirect), new);
	i = 1;
	while(split[i])
	{
		tmp = *cmd;
		if (tmp)
		{
			*cmd = ft_vajoin(tmp, " ", split[i], NULL);
			free(tmp);
			free(split[i]);
		}
		else
			*cmd = split[i];
		i ++;
	}
	free(split);

}

int	inpipe(t_divpipe *cpipe, char **toked, int i, char **env)
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
				cmd = ft_strdup(toked[i]);
			else
				redirect_filler(cpipe, toked[i], ltype, &cmd);
		}
		ltype = ctype;
		i ++;
	}
	if (ft_hasdollars(cmd))
		cmd = extender(cmd, env);
	cpipe->cmd = ft_split_quote(cmd);
	free(cmd);
	return (i);
}

t_divpipe	*ft_parsing(char *input, char **env)
{
	char		**toked;
	t_divpipe	*divpipe;
	t_divpipe	*cpipe;
	int			i;

	divpipe = NULL;
	toked = ft_tokenizer(input);
	if (!toked)
		return (NULL);
	i = 0;
	while (toked[i])
	{
		cpipe = ft_pipenew();
		if (!cpipe)
			break;
		cpipe->redirect = NULL;
		ft_pipeadd_back(&divpipe, cpipe);
		i = inpipe(cpipe, toked, i, env);
		if (toked[i])
			i ++;
	}
	ft_free_tab(toked);
	return (divpipe);
}

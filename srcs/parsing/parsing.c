/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:54:13 by mbico             #+#    #+#             */
/*   Updated: 2024/06/22 21:44:58 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	typage(char *elem)
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
	while (split[i])
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
				cmd = ft_strdup(toked[i]);
			else
				redirect_filler(cpipe, toked[i], ltype, &cmd);
		}
		ltype = ctype;
		i ++;
	}
	if (ft_hasdollars(cmd))
		cmd = extender(cmd, minish, FALSE);
	cpipe->cmd = ft_split_quote(cmd);
	free(cmd);
	return (i);
}

char	*ft_chardup(char c, int i)
{
	char *str;

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

t_bool ft_strisspace(char *str)
{
	ft_printf("%s\n", str);
	while (*str)
	{
		if (!ft_isspace(*str))
			return (FALSE); 
		str ++;
	}
	return (TRUE);
}

void	ft_syntax_checker(char **toked)
{
	int		i;
	t_type	type;
	char	*err;
	t_bool	pip;
	
	i = 0;
	pip = FALSE;
	while (toked[i])
	{
		if (ft_strlen(toked[i]) > 2 && (toked[i][0] == '<' || toked[i][0] == '>'))
		{
			err = ft_chardup(toked[i][0], ft_strlen(toked[i]) - 2);
			print_error("minishell: syntax error near unexpected `", err, "'");
			free(err);
		}
		if ((toked[i][0] == '|' && ft_strlen(toked[i]) > 1) || (toked[i][0] == '|' && pip == TRUE))
			ft_putstr_fd("minishell: syntax error near unexpected `|'\n", 2);
		if (toked[i][0] == '|')
			pip = TRUE;
		else if (!ft_strisspace(toked[i]))
			pip = FALSE;
		i ++;
	}
}

t_divpipe	*ft_parsing(char *input, t_minish *minish)
{
	char		**toked;
	t_divpipe	*divpipe;
	t_divpipe	*cpipe;
	int			i;

	divpipe = NULL;
	toked = ft_tokenizer(input);
	ft_syntax_checker(toked);
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

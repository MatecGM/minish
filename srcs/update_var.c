/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbico <mbico@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:50:46 by fparis            #+#    #+#             */
/*   Updated: 2024/06/19 19:53:00 by mbico            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_underscore(t_minish *minish)
{
	char	*new_underscore;
	int		i;

	i = 0;
	if (minish->in_pipe)
		return ;
	while (minish->divpipe->cmd && minish->divpipe->cmd[i])
	{
		new_underscore = minish->divpipe->cmd[i];
		i++;
	}
	if (!minish->divpipe->cmd || !minish->divpipe->cmd[0])
		new_underscore = "";
	new_underscore = ft_strjoin("_=", new_underscore);
	minish->to_free = new_underscore;
	add_var(minish, new_underscore);
	minish->to_free = NULL;
	free(new_underscore);
}

void	update_pwd(t_minish *minish, char *name)
{
	char	*path;
	char	*new_pwd;

	path = getcwd(NULL, 0);
	if (!path)
	{
		if (errno == ENOENT)
		{
			print_error("minish: The current working",
				"directory has been unlinked", NULL);
			return ;
		}
		exit_free(minish, 1);
	}
	new_pwd = ft_strjoin(name, path);
	free(path);
	minish->to_free = new_pwd;
	add_var(minish, new_pwd);
	minish->to_free = NULL;
	free(new_pwd);
}

int	get_new_shlvl(char *old_lvl)
{
	int	new_lvl;
	int	i;

	i = 0;
	new_lvl = 0;
	if (old_lvl[0] == '-')
		i++;
	while (old_lvl[i])
	{
		if (old_lvl[i] < '0' || old_lvl[i] > '9')
			return (1);
		new_lvl = new_lvl * 10 + (old_lvl[i] - '0');
		i++;
	}
	new_lvl += 1;
	if (new_lvl < 0 || old_lvl[0] == '-')
		return (0);
	else if (new_lvl >= 1000)
	{
		print_error("minish: warning: shell level",
			" (>= 1000) too high, resetting to 1", NULL);
		return (1);
	}
	return (new_lvl);
}

void	update_shlvl(t_minish *minish)
{
	char	*old_lvl;
	char	*new_lvl;
	char	*new_var;

	old_lvl = get_env_value(minish->env, "SHLVL=");
	if (!old_lvl)
	{
		add_var(minish, "SHLVL=1");
		return ;
	}
	new_lvl = ft_itoa(get_new_shlvl(old_lvl));
	free(old_lvl);
	if (!new_lvl)
		exit_free(minish, 1);
	new_var = ft_strjoin("SHLVL=", new_lvl);
	free(new_lvl);
	if (!new_var)
		exit_free(minish, 1);
	minish->to_free = new_var;
	add_var(minish, new_var);
	minish->to_free = NULL;
	free(new_var);
}

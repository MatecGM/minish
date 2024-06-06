/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fparis <fparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:50:46 by fparis            #+#    #+#             */
/*   Updated: 2024/06/06 20:41:31 by fparis           ###   ########.fr       */
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
	while (minish->divpipe->cmd[i])
	{
		new_underscore = minish->divpipe->cmd[i];
		i++;
	}
	new_underscore = ft_strjoin("_=", new_underscore);
	add_var(minish, new_underscore);
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
	add_var(minish, new_pwd);
	free(new_pwd); //pas protected
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
	new_lvl = ft_itoa(ft_atoi(old_lvl) + 1);
	if (!new_lvl)
		exit_free(minish, 1);
	free(old_lvl);
	new_var = ft_strjoin("SHLVL=", new_lvl);
	free(new_lvl);
	if (!new_var)
		exit_free(minish, 1);
	add_var(minish, new_var);
	free(new_var); //pas protected;
}

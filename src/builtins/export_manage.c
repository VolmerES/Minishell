/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:08:39 by david             #+#    #+#             */
/*   Updated: 2024/10/19 19:46:55 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	manage_export(t_msh *c, int num_command)
{
	char	**var_split;
	int		i;

	i = 0;
	while (c->cmds[num_command]->args[i]
		&& c->cmds[num_command]->args[i][0] != '=')
	{
		if (ft_strchr(c->cmds[num_command]->args[i], '='))
		{
			var_split = ft_split(c->cmds[num_command]->args[i], '=');
			if (!var_split)
				exit(1);
			if (ft_check_syntax(var_split[0], c) == 0)
			{
				update_env(c, ft_search_env(c->envp, var_split[0]), \
				ft_strdup(c->cmds[num_command]->args[i]));
				c->last_out = 0;
			}
			else
				c->last_out = 1;
			ft_free_matrix(var_split);
		}
		i++;
	}
}

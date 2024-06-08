/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:08:39 by david             #+#    #+#             */
/*   Updated: 2024/06/08 17:43:36 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	manage_export(t_msh *commands, int num_command)
{
	char	**var_split;
	int		i;

	i= 0;
	while (commands->cmds[num_command]->args[i])
	{
		if (ft_strchr(commands->cmds[num_command]->args[i], '='))
		{
			var_split = ft_split(commands->cmds[num_command]->args[i], '=');
			if (!var_split)
				exit(1);
			ft_check_syntax(var_split[0], commands);
			update_env(commands, ft_search_env(commands->envp, var_split[0]), ft_strdup(commands->cmds[num_command]->args[i]));
			ft_free_matrix(var_split);
		}
		i++;
	}
}

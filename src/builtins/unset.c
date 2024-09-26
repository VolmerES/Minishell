/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:11:18 by david             #+#    #+#             */
/*   Updated: 2024/08/06 19:26:33 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void check_path_unset(t_msh *commands, int index)
{
	if(ft_strncmp(commands->envp[index], "PATH", 4) == 0)
	{
		ft_free_matrix(commands->path);
		commands->path = NULL;
	}
}

int unset_builtin(t_msh *commands, int i)
{
	int index;
	int j;

	j = 0;
	while (commands->cmds[i]->args && commands->cmds[i]->args[j])
	{
		index = ft_search_env(commands->envp, commands->cmds[i]->args[j]);
		if (index != -1)
		{
			check_path_unset(commands, index);
			free(commands->envp[index]);
			while (commands->envp[index] != NULL)
			{
				commands->envp[index] = commands->envp[index + 1];
				index++;
			}
		}
		j++;
	}
	return (0);
}

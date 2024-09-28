/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:11:18 by david             #+#    #+#             */
/*   Updated: 2024/09/28 19:31:11 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	void	check_path_unset(t_msh *commands, int index)
{
	if (ft_strncmp(commands->envp[index], "PATH", 4) == 0)
	{
		ft_free_matrix(commands->path);
		commands->path = NULL;
	}
}

void	move_and_free(t_msh *commands, int var)
{
	if (var != -1)
	{
		free(commands->envp[var]);
		while (commands->envp[var] != NULL)
		{
			commands->envp[var] = commands->envp[var + 1];
			var++;
		}
	}
}

int	unset_builtin(t_msh *commands, int i)
{
	int	index;
	int	j;

	j = 0;
	while (commands->cmds[i]->args && commands->cmds[i]->args[j])
	{
		index = ft_search_env(commands->envp, commands->cmds[i]->args[j]);
		if (index != -1)
		{
			check_path_unset(commands, index);
			move_and_free(commands, index);
		}
		j++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:11:18 by david             #+#    #+#             */
/*   Updated: 2024/04/24 20:51:44 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	unset_builtin(t_msh *commands, int i)
{
	int index;
	int j;

	j = 0;
	while (commands->cmds[i]->args[j])
	{
		index = ft_search_env(commands->envp, commands->cmds[i]->args[j]);
		// if (index != -1 && )
		// 	commands->envp = ft_removevariable(commands->envp, index);
		j++;
	}
}
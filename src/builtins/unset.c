/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:11:18 by david             #+#    #+#             */
/*   Updated: 2024/04/27 15:17:59 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void unset_builtin(t_msh *commands, int i)
{
	int index;
	int j;

	j = 0;
	while (commands->cmds[i]->args[j])
	{
		index = ft_search_env(commands->envp, commands->cmds[i]->args[j]);
		if (index != -1)
		{
			free(commands->envp[i]);
			while (commands->envp[i] != NULL)
			{
				commands->envp[i] = commands->envp[i + 1];
				i++;
			}
		}
		j++;
	}
}
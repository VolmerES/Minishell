/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:11:18 by david             #+#    #+#             */
/*   Updated: 2024/06/08 17:55:42 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int unset_builtin(t_msh *commands, int i)
{
	int index;
	int j;

	j = 0;
	while (commands->cmds[i]->args[j])
	{
		index = ft_search_env(commands->envp, commands->cmds[i]->args[j]);
		if (index != -1)
		{
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
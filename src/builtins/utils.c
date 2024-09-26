/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:45:38 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/08/06 19:00:04 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_num_args(t_msh *commands, int i)
{
	int	j;

	j = 0;
	while (commands->cmds[i]->args && commands->cmds[i]->args[j])
		j++;
	return (j);
}

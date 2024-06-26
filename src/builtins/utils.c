/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:45:38 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/04/13 12:13:16 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int check_num_args(t_msh *commands, int i)
{
	int j;

	j = 0;
	while (commands->cmds[i]->args[j])
		j++;
	return (j);
}

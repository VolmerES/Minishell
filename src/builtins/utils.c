/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:45:38 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/03/25 16:46:25 by ldiaz-ra         ###   ########.fr       */
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:42:29 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/05/18 19:25:25 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	executor_manage(t_msh *commands)
{
	int	i;

	i = 0;
	if (commands->parser.cmd_index == 1)
	{
		if (is_builtins(commands, i))
			bd_one_command(commands);
		else
			one_command(commands);
	}
	else
		multi_command(commands);
}

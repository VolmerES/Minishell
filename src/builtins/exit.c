/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:25:02 by david             #+#    #+#             */
/*   Updated: 2024/06/08 19:04:26 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_builtin(t_msh *commands, int cmd_i)
{
	printf("exit\n");
	if (check_num_args(commands, cmd_i) > 1)
	{
		commands->last_out = 1;
		if(!ft_isdigit(ft_atoi(commands->cmds[cmd_i]->args[0])))
		{
			printf("exit: %s: numeric argument required\n", commands->cmds[cmd_i]->args[0]);
			exit(2);
		}
		printf("exit: too many arguments\n");
		return ;
	}
	else
	{

	}
	exit(commands->last_out);
}

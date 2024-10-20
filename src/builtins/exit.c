/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:25:02 by david             #+#    #+#             */
/*   Updated: 2024/10/19 23:05:23 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	void	check_arg(char *arg, t_msh *commands)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			printf("Minishell: %s: numeric argument required\n", arg);
			close(commands->cp_stdin);
			close(commands->cp_stdout);
			exit(2);
		}
		i++;
	}
}

void	exit_builtin(t_msh *commands, int cmd_i)
{
	printf("exit\n");
	commands->last_out = 0;
	if (check_num_args(commands, cmd_i) > 1)
	{
		commands->last_out = 1;
		check_arg(commands->cmds[cmd_i]->args[0], commands);
		printf("exit: too many arguments\n");
		return ;
	}
	else if (check_num_args(commands, cmd_i) == 1)
	{
		check_arg(commands->cmds[cmd_i]->args[0], commands);
		exit(ft_atoi(commands->cmds[cmd_i]->args[0]) % 256);
	}
	close(commands->cp_stdin);
	close(commands->cp_stdout);
	exit(commands->last_out);
}

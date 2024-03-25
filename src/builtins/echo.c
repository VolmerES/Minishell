/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:43:17 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/03/25 18:30:50 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int check_flag(t_msh *commands, int i)
{
	int j;
	int len_arg;

	j = 1;
	len_arg = ft_strlen(commands->cmds[i]->args[0]);
	if (commands->cmds[i]->args[0][0] == '-')
	{
		while (commands->cmds[i]->args[0][j] == 'n')
			j++;
	}
	return (j == len_arg);
}
print_inline(t_msh *commands, int i)
{
	int j;

	j = 1;
	
}

int	echo_builtin(t_msh *commands, int i)
{
	int	num_arg;
	int	bool_flag;

	num_arg = check_num_args(commands, i);
	bool_flag = 0;
	if (num_arg > 1)
		bool_flag = check_flag(commands, i);
	if (bool_flag)
		print_inline(commands, i);
	else
		print_ln();
	return (0);
}

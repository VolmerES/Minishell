/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:43:17 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/08/17 11:18:20 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	void	print_echo(t_msh *commands, int i, int j, int n_flag)
{
	while (commands->cmds[i]->args && commands->cmds[i]->args[j])
	{
		printf("%s", commands->cmds[i]->args[j]);
		if (commands->cmds[i]->args[j + 1])
			printf(" ");
		j++;
	}
	if (!n_flag)
		printf("\n");
}

int	check_break(t_msh *commands, int i, int j)
{
	int	k;

	k = 1;
	while (commands->cmds[i]->args[j][k] != '\0')
	{
		if (commands->cmds[i]->args[j][k] != 'n')
			return (1);
		k++;
	}
	return (0);
}

int	echo_builtin(t_msh *commands, int i)
{
	int	n_flag;
	int	j;

	n_flag = 0;
	j = 0;
	while (commands->cmds[i]->args && commands->cmds[i]->args[j])
	{
		if (commands->cmds[i]->args[j][0] == '-' && \
		ft_strlen(commands->cmds[i]->args[j]) > 1)
		{
			if (check_break(commands, i, j))
				break ;
			j++;
			n_flag = 1;
		}
		else
			break ;
	}
	print_echo(commands, i, j, n_flag);
	return (0);
}

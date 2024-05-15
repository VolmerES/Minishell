/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:17:34 by david             #+#    #+#             */
/*   Updated: 2024/05/15 18:00:09 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	multi_command(t_msh *commands)
{
	int	new[2];
	int	fd[2];
	int	counter;

	if (pipe(fd) < 0)
		exit_(0);
	// first_child(commands, fd, &commands->cmds[0]);
	close(fd[1]);
	counter = 1;
	while (counter < (commands->parser.cmd_index - 1))
	{
		if (pipe(new) < 0)
			exit_(0);
		mid_child(commands, fd, new, &commands->cmds[counter]);
		close(fd[0]);
		close(new[1]);
		fd[0] = new[0];
		counter++;
	}
	last_child(commands, fd, &commands->cmds[commands->parser.cmd_index - 1]);
	close(fd[0]);
	wait_childs(commands);
	
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:17:34 by david             #+#    #+#             */
/*   Updated: 2024/05/18 16:47:56 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	wait_childs(t_msh *commands)
{
	pid_t	current_pid;
	int		status;
	
	while (1)
	{
		current_pid = waitpid(-1, &status, 0);
		if (current_pid <= 0)
			break ;
		if (current_pid == commands->last_pid)
			commands->last_out = WEXITSTATUS(status);
	}
}

void	multi_command(t_msh *commands)
{
	int	new[2];
	int	fd[2];
	int	counter;

	if (pipe(fd) < 0)
		exit_(0);
	first_child(commands, fd);
	close(fd[1]);
	counter = 1;
	while (counter < (commands->parser.cmd_index - 1))
	{
		printf("counter: %d\n", counter);
		if (pipe(new) < 0)
			exit_(0);
		mid_child(commands, fd, new, counter);
		close(fd[0]);
		close(new[1]);
		fd[0] = new[0];
		counter++;
	}
	last_child(commands, fd);
	close(fd[0]);
	wait_childs(commands);
}

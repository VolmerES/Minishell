/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:17:34 by david             #+#    #+#             */
/*   Updated: 2024/10/19 19:48:25 by ldiaz-ra         ###   ########.fr       */
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

	open_her_docs(commands);
	if (pipe(fd) < 0)
		exit_(0);
	first_child(commands, fd);
	close(fd[1]);
	counter = 0;
	while (++counter < (commands->parser.cmd_index - 1))
	{
		if (pipe(new) < 0)
			exit_(0);
		mid_child(commands, fd, new, counter);
		close(fd[0]);
		close(new[1]);
		fd[0] = new[0];
	}
	last_child(commands, fd);
	close(fd[0]);
	wait_childs(commands);
}

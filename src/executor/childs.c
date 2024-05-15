/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:32:02 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/05/15 17:57:46 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	first_child(t_msh *commands, int *fd)
{
	int	fd_in;
	int	fd_out;

	commands->last_pid = fork();
	if (commands->last_pid == 0)
	{
		// signals_here_doc();
		close(fd[0]);
		fd_in = open_files(commands, 0);
		if (fd_in < 0)
			exit(1);
		// fd_out = open_outfile(cmds->outfiles, cmds->outfiles_count, fd[1]);
		if (fd_out < 0)
			exit(1);
		// child_aux(commands, cmds, fd_in, fd_out);
	}
	else if (commands->last_pid < 0)
		exit_(1);
}
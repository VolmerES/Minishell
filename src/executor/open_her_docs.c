/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_her_docs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:51:17 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/10/05 20:09:38 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	void	return_child(t_msh *commands)
{
	int i;
	int i_infile;

	i = 0;
	
	
	while (i < commands->parser.cmd_index)
	{
		i_infile = 0;
		while(commands->cmds[i]->infile[i_infile] && commands->cmds[i]->infile[i_infile]->type == INFILE_HERE_DOC)
		{
			commands->cmds[i]->infile[i_infile]->fd_herdoc = her_doc(commands->cmds[i]->infile[i_infile]->filename);
			i_infile++;
		}
		i++;
	}
	exit(0);
}

void	open_her_docs(t_msh *commands)
{
	int status;
	pid_t	her_docs;

	her_docs = fork();
	if (her_docs == 0)
		return_child(commands);
	waitpid(her_docs, &status, 0);
	
}

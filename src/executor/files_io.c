/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:28:33 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/10/05 20:04:10 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	void	msg_error(char *filename)
{
	char	*join;

	join = ft_strjoin("Minishell-42: ", filename);
	perror(join);
	free(join);
}

static int	file_check(int fd, int pipe, int predetermined)
{
	if (fd > 0)
	{
		if (pipe > 0)
			close(pipe);
		return (fd);
	}
	if (pipe > 0)
		return (pipe);
	return (predetermined);
}

int	open_files(t_msh *c, int cmd_i, int pipe)
{
	int		infd;
	int		i;

	infd = -1;
	i = -1;
	if (c->cmds[cmd_i]->infile)
	{
		while (c->cmds[cmd_i]->infile[++i])
		{
			if (c->cmds[cmd_i]->infile[i]->type == INFILE_NORMAL)
				infd = open(c->cmds[cmd_i]->infile[i]->filename, O_RDONLY);
			else if (c->parser.cmd_index == 1)
				infd = open(her_doc(c->cmds[cmd_i]->infile[i]->filename), \
				O_RDONLY);
			else
				infd = open(c->cmds[cmd_i]->infile[i]->filename, O_RDONLY);
			if (infd < 0)
				return (msg_error(c->cmds[cmd_i]->infile[i]->filename), -1);
		}
	}
	return (file_check(infd, pipe, STDIN_FILENO));
}

int	out_files(t_msh *c, int cmd_i, int pipe)
{
	int		outfd;
	int		i;

	outfd = -1;
	i = -1;
	if (c->cmds[cmd_i]->outfile)
	{
		while (c->cmds[cmd_i]->outfile[++i])
		{
			if (c->cmds[cmd_i]->outfile[i]->type == OUTFILE_TRUNC)
				outfd = open(c->cmds[cmd_i]->outfile[i]->filename, \
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
			else
				outfd = open(c->cmds[cmd_i]->outfile[i]->filename, \
				O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (outfd < 0)
				return (msg_error(c->cmds[cmd_i]->outfile[i]->filename), -1);
		}
	}
	return (file_check(outfd, pipe, STDOUT_FILENO));
}

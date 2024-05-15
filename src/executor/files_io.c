/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:28:33 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/05/15 17:57:44 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int open_files(t_msh *commands, int cmd_i)
{
    int infd;
    int i;

    infd = -1;
    i = 0;
    if (commands->cmds[cmd_i]->infile)
    {
        while (commands->cmds[cmd_i]->infile[i])
        {
            if (commands->cmds[cmd_i]->infile[i]->type == INFILE_NORMAL)
                infd = open(commands->cmds[cmd_i]->infile[i]->filename, O_RDONLY);
            if (infd < 0)
            {
                perror("open");
                return (-1);
            }
            i++;
        }
    }
    return (infd);
}

int out_files(t_msh *commands, int cmd_i)
{
    int outfd;
    int i;

    outfd = -1;
    i = 0;
    if (commands->cmds[cmd_i]->outfile)
    {
        while (commands->cmds[cmd_i]->outfile[i])
        {
            if (commands->cmds[cmd_i]->outfile[i]->type == OUTFILE_TRUNC)
                outfd = open(commands->cmds[cmd_i]->outfile[i]->filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
            else
                outfd = open(commands->cmds[cmd_i]->outfile[i]->filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
            if (outfd < 0)
                perror("open");
            i++;
        }
    }
    return (outfd);
}

static int	file_check(int fd, int pipe, int predetermined, int count)
{
	if (fd > 0)
	{
		if (pipe > 0)
			close(pipe);
		return (fd);
	}
	if (pipe > 0)
		return (pipe);
	if (count == 0)
		return (predetermined);
	return (-1);
}
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

static	void	return_child(t_msh *commands, int fd[2], t_counters count)
{
	char	*herdoc_file;

	close(fd[0]);
	ft_heredoc_signal_handler();
	herdoc_file = her_doc(commands->cmds[count.i]->infile[count.j]->filename);
	if (herdoc_file)
		write(fd[1], herdoc_file, ft_strlen(herdoc_file) + 1);
	free(herdoc_file);
	close(fd[1]);
	exit(0);
}

void	proc_f(t_msh *commands, int fd[2], t_counters count, pid_t pid)
{
	char	herdoc_file[256];
	ssize_t	bytes_read;

	close(fd[1]);
	bytes_read = read(fd[0], herdoc_file, sizeof(herdoc_file));
	if (bytes_read > 0)
	{
		free(commands->cmds[count.i]->infile[count.j]->filename);
		commands->cmds[count.i]->infile[count.j]->filename = \
		ft_strdup(herdoc_file);
	}
	waitpid(pid, &count.k, 0);
	commands->last_out = WEXITSTATUS(count.k);
	close(fd[0]);
	if (commands->last_out != 0)
		return ;
}

static	void	handle_heredoc(t_msh *commands, int fd[2], t_counters counters)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		return_child(commands, fd, counters);
	else if (pid > 0)
		proc_f(commands, fd, counters, pid);
	else
		exit_(FORK_);
}

void	open_her_docs(t_msh *commands)
{
	int			fd[2];
	t_counters	counters;

	counters.i = -1;
	if (pipe(fd) < 0)
		exit_(PIPE_);
	while (commands->cmds[++counters.i])
	{
		counters.j = -1;
		while (commands->cmds[counters.i]->infile && \
		commands->cmds[counters.i]->infile[++counters.j])
		{
			if (commands->cmds[counters.i]->infile[counters.j]->type \
			== INFILE_HERE_DOC)
				handle_heredoc(commands, fd, counters);
		}
	}
}

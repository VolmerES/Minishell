/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_her_docs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:51:17 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/10/19 18:10:05 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
extern int	g_signal_control;

static	void	return_child(t_msh *commands, t_counters count)
{
	ft_heredoc_signal_handler();
	her_doc(commands->cmds[count.i]->infile[count.j]->name_herdoc, \
	commands->cmds[count.i]->infile[count.j]->filename);
	exit(0);
}

void	proc_f(t_msh *commands, t_counters count)
{
	pid_t pid;

	pid = fork();
	if(pid == 0)
		return_child(commands, count);
	else
	{
		waitpid(pid, &count.k, 0);
		commands->last_out = WEXITSTATUS(count.k);
	}
}

static	void	handle_heredoc(t_msh *c, t_counters counters)
{
	char	*file;
	char	**args;
	int		fd;

	file = check_file(c->cmds[counters.i]->infile[counters.j]->filename);
	fd = open(file, O_WRONLY | O_CREAT, 0777);
	if (fd < 0)
	{
		free(file);
		exit_(2);
	}
	c->cmds[counters.i]->infile[counters.j]->name_herdoc = ft_strdup(file);
	if (!c->cmds[counters.i]->args)
	{
		args = malloc(sizeof(char *) * 2);
		args[0] = ft_strdup(file);
		args[1] = NULL;
		c->cmds[counters.i]->args = args;
	}
	free(file);
	close(fd);
	if (g_signal_control != 130)
		proc_f(c, counters);
}

void	open_her_docs(t_msh *commands)
{
	t_counters	counters;

	counters.i = -1;
	while (commands->cmds[++counters.i])
	{
		counters.j = -1;
		while (commands->cmds[counters.i]->infile && \
		commands->cmds[counters.i]->infile[++counters.j])
		{
			if (commands->cmds[counters.i]->infile[counters.j]->type \
			== INFILE_HERE_DOC)
				handle_heredoc(commands, counters);
		}
	}
}

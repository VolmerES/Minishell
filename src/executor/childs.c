/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:32:02 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/10/05 19:43:07 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	child_aux(t_msh *commands, int cmd_i, int fd_in, int fd_out)
{
	char	*path;

	if (commands->cmds[cmd_i]->cmd_main)
		commands->cmds[cmd_i]->full_cmd = add_to_arg(\
		commands->cmds[cmd_i]->args, commands->cmds[cmd_i]->cmd_main);
	if (commands->cmds[cmd_i]->cmd_main)
		path = check_path(commands->path, commands->cmds[cmd_i]->cmd_main);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	if (fd_in != 0)
		close(fd_in);
	if (fd_out != 1 && fd_out != 2)
		close(fd_out);
	if (!commands->cmds[cmd_i]->cmd_main)
		exit(0);
	if (is_builtins(commands, cmd_i))
		ft_builtins(commands, cmd_i);
	else
	{
		if (path)
			execve(path, commands->cmds[cmd_i]->full_cmd, commands->envp);
		exit_err(commands, cmd_i);
	}
	exit(commands->last_out);
}

void	first_child(t_msh *commands, int *fd)
{
	int	fd_in;
	int	fd_out;

	commands->last_pid = fork();
	if (commands->last_pid == 0)
	{
		close(fd[0]);
		fd_in = open_files(commands, 0, fd[0]);
		if (fd_in < 0)
			exit(1);
		fd_out = out_files(commands, 0, fd[1]);
		if (fd_out < 0)
			exit(1);
		child_aux(commands, 0, fd_in, fd_out);
	}
	else if (commands->last_pid < 0)
		exit_(1);
}

void	mid_child(t_msh *commands, int *fd, int *new, int cmd_i)
{
	int	fd_in;
	int	fd_out;

	commands->last_pid = fork();
	if (commands->last_pid == 0)
	{
		close(new[0]);
		fd_in = open_files(commands, cmd_i, fd[0]);
		if (fd_in < 0)
			exit(1);
		fd_out = out_files(commands, cmd_i, new[1]);
		if (fd_out < 0)
			exit(1);
		child_aux(commands, cmd_i, fd_in, fd_out);
	}
	else if (commands->last_pid < 0)
		exit_(1);
}

void	last_child(t_msh *commands, int *fd)
{
	int	fd_in;
	int	fd_out;

	commands->last_pid = fork();
	if (commands->last_pid == 0)
	{
		fd_in = open_files(commands, commands->parser.cmd_index - 1, fd[0]);
		if (fd_in < 0)
			exit(1);
		fd_out = out_files(commands, commands->parser.cmd_index - 1, -1);
		if (fd_out < 0)
			exit(1);
		child_aux(commands, commands->parser.cmd_index - 1, fd_in, fd_out);
	}
	else if (commands->last_pid < 0)
		exit_(1);
}

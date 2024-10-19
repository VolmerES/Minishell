/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:39:36 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/10/19 20:42:20 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	bd_one_command(t_msh *commands)
{
	int	infd;
	int	outfd;

	infd = open_files(commands, 0, -1);
	if (infd < 0)
		return (commands->last_out = 1);
	outfd = out_files(commands, 0, -1);
	if (outfd < 0)
		return (commands->last_out = 1);
	commands->cp_stdin = dup(STDIN_FILENO);
	commands->cp_stdout = dup(STDOUT_FILENO);
	dup2(infd, STDIN_FILENO);
	dup2(outfd, STDOUT_FILENO);
	ft_builtins(commands, 0);
	if (infd != 0)
		close(infd);
	if (outfd != 1 || outfd != 2)
		close(outfd);
	dup2(commands->cp_stdin, STDIN_FILENO);
	dup2(commands->cp_stdout, STDOUT_FILENO);
	close(commands->cp_stdin);
	close(commands->cp_stdout);
	return (0);
}

void	child_one_command(t_msh *commands)
{
	int		infd;
	int		outfd;
	char	*path;

	infd = open_files(commands, 0, -1);
	if (infd < 0)
		exit(1);
	outfd = out_files(commands, 0, -1);
	if (outfd < 0)
		exit(1);
	dup2(infd, STDIN_FILENO);
	dup2(outfd, STDOUT_FILENO);
	if (!commands->cmds[0]->cmd_main)
	{
		if (infd != STDIN_FILENO)
			close(infd);
		if (outfd != STDOUT_FILENO)
			close(outfd);
		exit(0);
	}
	path = check_path(commands->path, commands->cmds[0]->cmd_main);
	if (path)
		execve(path, commands->cmds[0]->full_cmd, commands->envp);
	exit_err(commands, 0);
}

void	one_command(t_msh *commands)
{
	pid_t	pid;
	int		status;

	if (commands->cmds[0]->cmd_main)
		commands->cmds[0]->full_cmd = add_to_arg(\
		commands->cmds[0]->args, commands->cmds[0]->cmd_main);
	open_her_docs(commands);
	pid = fork();
	if (pid < 0)
		exit_(1);
	if (pid == 0 && commands->last_out != 130)
		child_one_command(commands);
	else if (pid == 0)
		exit(130);
	waitpid(pid, &status, 0);
	commands->last_out = WEXITSTATUS(status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:39:36 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/09/21 17:45:55 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    bd_one_command(t_msh *commands)
{
    int infd;
    int outfd;

	infd = open_files(commands, 0, -1);
	if (infd < 0){
		commands->last_out = 1;
		return;
	}
    outfd = out_files(commands, 0, -1);
	if (outfd < 0){
		commands->last_out = 1;
		return;
	}
	dup2(infd, STDIN_FILENO);
	dup2(outfd, STDOUT_FILENO);
    ft_builtins(commands, 0);
    dup2(commands->cp_stdin, STDIN_FILENO);
    dup2(commands->cp_stdout, STDOUT_FILENO);
}

void   child_one_command(t_msh *commands)
{
    int infd;
    int outfd;
    char *path;

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

void    one_command(t_msh *commands)
{
    pid_t	pid;
	int		status;

	if (commands->cmds[0]->cmd_main)
		commands->cmds[0]->full_cmd = add_to_arg(commands->cmds[0]->args, commands->cmds[0]->cmd_main);
	pid = fork();
	if (pid < 0)
		exit_(1);
	if (pid == 0)
		child_one_command(commands);
	waitpid(pid, &status, 0);
    commands->last_out = WEXITSTATUS(status);
}

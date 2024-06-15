/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:39:36 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/06/15 16:43:25 by ldiaz-ra         ###   ########.fr       */
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
	commands->cp_stdin_last = dup2(infd, STDIN_FILENO);
	commands->cp_stdout_last = dup2(outfd, STDOUT_FILENO);
    ft_builtins(commands, 0);
    fflush(stdout);//! quitar
    dup2(commands->cp_stdin, commands->cp_stdin_last);
    dup2(commands->cp_stdout, commands->cp_stdout_last);
}

void   child_one_command(t_msh *commands)
{
    int infd;
    int outfd;
    char *path;

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
    path = check_path(commands->path, commands->cmds[0]->cmd_main);
    execve(path, commands->cmds[0]->full_cmd, commands->envp);
    exit_err(commands, 0);
}

void    one_command(t_msh *commands)
{
    pid_t	pid;
	int		status;

	commands->cmds[0]->full_cmd = add_to_arg(commands->cmds[0]->args, commands->cmds[0]->cmd_main);
	pid = fork();
	if (pid < 0)
		exit_(1);
	if (pid == 0)
		child_one_command(commands);
	waitpid(pid, &status, 0);
	ft_free_matrix(commands->cmds[0]->full_cmd);
	commands->last_out = WEXITSTATUS(status);
}

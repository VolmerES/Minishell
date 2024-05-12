/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:39:36 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/05/12 16:02:44 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int open_files(t_msh *commands)
{
    int infd;
    int i;

    infd = -1;
    i = 0;
    if (commands->cmds[0]->infile)
    {
        while (commands->cmds[0]->infile[i])
        {
            if (commands->cmds[0]->infile[i]->type == INFILE_NORMAL)
                infd = open(commands->cmds[0]->infile[i]->filename, O_RDONLY);
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

int out_files(t_msh *commands)
{
    int outfd;
    int i;

    outfd = -1;
    i = 0;
    if (commands->cmds[0]->outfile)
    {
        while (commands->cmds[0]->outfile[i])
        {
            if (commands->cmds[0]->outfile[i]->type == OUTFILE_TRUNC)
                outfd = open(commands->cmds[0]->outfile[i]->filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
            else
                outfd = open(commands->cmds[0]->outfile[i]->filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
            if (outfd < 0)
                perror("open");
            i++;
        }
    }
    return (outfd);
}

void    bd_one_command(t_msh *commands)
{
    int infd;
    int outfd;

    if (commands->cmds[0]->infile != NULL)
    {
        infd = open_files(commands);
        if (infd < 0)
            return;
        commands->cp_stdin_last = dup2(infd, STDIN_FILENO);
        close(infd);
    }
    if (commands->cmds[0]->outfile != NULL)
    {
        outfd = out_files(commands);
        if (outfd < 0)
            return;
        commands->cp_stdout_last = dup2(outfd, STDOUT_FILENO);
        close(outfd);
    }
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

    if (commands->cmds[0]->infile != NULL)
    {
        infd = open_files(commands);
        if (infd < 0)
            return;
        dup2(infd, STDIN_FILENO);
        close(infd);
    }
    if (commands->cmds[0]->outfile != NULL)
    {
        outfd = out_files(commands);
        if (outfd < 0)
            return;
        dup2(outfd, STDOUT_FILENO);
        close(outfd);
    }
    path = check_path(commands->path, commands->cmds[0]->cmd_main);
    execve(path, commands->cmds[0]->full_cmd, commands->envp);
    perror("execve");
}

void    one_command(t_msh *commands)
{
    pid_t	pid;
	int		status;

	commands->cmds[0]->full_cmd = add_to_arg(commands->cmds[0]->args, commands->cmds[0]->cmd_main);
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
		child_one_command(commands);
	waitpid(pid, &status, 0);
	//todo WEXITSTATUS(status); gestionar el status
}

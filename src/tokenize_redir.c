/* ************************************************************************** */
/*                                                                            */
/*   tokenize_redir.c                                     :::      ::::::::   */
/*                                     			   		:+:      :+:    :+:   */
/*   By: juan <juan@student.42.fr>                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:50:45 by jdelorme          #+#    #+#             */
/*   Updated: 2024/04/15 13:02:49 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_is_command(t_msh *commands, int *i, int *j)
{
	int	start;

	start = *j;
	while (commands->cmds[*i]->cmd[*j] != '\0'
		&& commands->cmds[*i]->cmd[*j] != ' '
		&& commands->cmds[*i]->cmd[*j] != '<'
		&& commands->cmds[*i]->cmd[*j] != '>')
	{
		(*j)++;
	}
	commands->cmds[*i]->cmd_main = ft_substr(commands->cmds[*i]->cmd, start, *j
			- start);
	printf("\033[34mMain commands: %s\033[0m\n", commands->cmds[*i]->cmd_main);
	while (commands->cmds[*i]->cmd[*j] != '<'
		&& commands->cmds[*i]->cmd[*j] != '>'
		&& commands->cmds[*i]->cmd[*j] != '\0')
	{
		ft_arguments(commands, i, j);
		*j += 1;
	}
}

void	ft_is_outfile_trunc(t_msh *commands, int *i, int *j)
{
	t_file	*outfile;
	char	*filename;
	int		start;

	outfile = malloc(sizeof(t_file));
	filename = "";
	while (commands->cmds[*i]->cmd[*j] != '>'
		&& commands->cmds[*i]->cmd[*j] != '\0')
		(*j)++;
	if (commands->cmds[*i]->cmd[*j] == '>')
		(*j)++;
	while (commands->cmds[*i]->cmd[*j] == ' ')
		(*j)++;
	start = *j;
	while (commands->cmds[*i]->cmd[*j] != '\0'
		&& commands->cmds[*i]->cmd[*j] != ' ')
		(*j)++;
	filename = ft_substr(commands->cmds[*i]->cmd, start, *j - start);
	outfile->filename = filename;
	outfile->type = OUTFILE_TRUNC;
	commands->cmds[*i]->outfile = outfile;
	printf("\033[34mOutfile Type Trunc: %s\033[0m\n", outfile->filename);
}

void	ft_is_outfile_append(t_msh *commands, int *i, int *j)
{
	t_file	*outfile;
	char	*filename;
	int		start;
	char	*ccmd;

	ccmd = commands->cmds[*i]->cmd;
	outfile = malloc(sizeof(t_file));
	while (ccmd[*j] != '\0')
	{
		if (ccmd[*j] == '>' && ccmd[*j + 1] == '>')
			break ;
		(*j)++;
	}
	if (ccmd[*j] == '>' && ccmd[*j + 1] == '>')
		(*j) += 2;
	while (ccmd[*j] == ' ')
		(*j)++;
	start = *j;
	while (ccmd[*j] != '\0' && ccmd[*j] != ' ' && ccmd[*j] != '>')
		(*j)++;
	filename = ft_substr(ccmd, start, *j - start);
	outfile->filename = filename;
	outfile->type = OUTFILE_APPEND;
	commands->cmds[*i]->outfile = outfile;
	printf("\033[34mOutfile Type Append: %s\n", outfile->filename);
}

void	ft_is_infile(t_msh *commands, int *i, int *j)
{
	t_file	*infile;
	char	*filename;
	int		start;

	infile = malloc(sizeof(t_file));
	filename = "";
	while (commands->cmds[*i]->cmd[*j] != '<'
		&& commands->cmds[*i]->cmd[*j] != '\0')
		(*j)++;
	if (commands->cmds[*i]->cmd[*j] == '<')
		(*j)++;
	while (commands->cmds[*i]->cmd[*j] == ' ')
		(*j)++;
	start = *j;
	while (commands->cmds[*i]->cmd[*j] != '\0'
		&& commands->cmds[*i]->cmd[*j] != ' '
		&& commands->cmds[*i]->cmd[*j] != '<')
		(*j)++;
	filename = ft_substr(commands->cmds[*i]->cmd, start, *j - start);
	infile->filename = filename;
	infile->type = INFILE_NORMAL;
	commands->cmds[*i]->infile = infile;
	printf("\033[34mInfile Type Normal: %s\033[0m\n", infile->filename);
}

void	ft_is_infile_here_doc(t_msh *commands, int *i, int *j)
{
	t_file	*infile;
	char	*filename;
	int		start;
	char	*ccmd;

	ccmd = commands->cmds[*i]->cmd;
	infile = malloc(sizeof(t_file));
	while (ccmd[*j] != '\0')
	{
		if (ccmd[*j] == '<' && ccmd[*j + 1] == '<')
			break ;
		(*j)++;
	}
	if (ccmd[*j] == '<' && ccmd[*j + 1] == '<')
		(*j) += 2;
	while (ccmd[*j] == ' ')
		(*j)++;
	start = *j;
	while (ccmd[*j] != '\0' && ccmd[*j] != ' ' && ccmd[*j] != '<')
		(*j)++;
	filename = ft_substr(ccmd, start, *j - start);
	infile->filename = filename;
	infile->type = INFILE_HERE_DOC;
	commands->cmds[*i]->infile = infile;
	printf("\033[34mInfile Type Here_doc: %s\033[0m\n", infile->filename);
}

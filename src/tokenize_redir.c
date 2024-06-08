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
	int squotes;
	int dquotes;

	dquotes = 0;
	squotes = 0;
	while (commands->cmds[*i]->cmd[*j] == SPACE)
		(*j)++;
	start = *j;
	while (commands->cmds[*i]->cmd[*j] != '\0'
        && (squotes == 1 || dquotes == 1 || (commands->cmds[*i]->cmd[*j] != ' '
        && commands->cmds[*i]->cmd[*j] != '<'
        && commands->cmds[*i]->cmd[*j] != '>')))
	{
        if (commands->cmds[*i]->cmd[*j] == SQUOTES)
            squotes = !squotes;
		if (commands->cmds[*i]->cmd[*j] == DQUOTES)
			dquotes = !dquotes;
        (*j)++;
    }
	commands->cmds[*i]->cmd_main = ft_substr(commands->cmds[*i]->cmd, start, *j
			- start);
	while (commands->cmds[*i]->cmd[*j] == SPACE)
		(*j)++;
	printf("\033[34mMain commands: [%s]\033[0m\n", commands->cmds[*i]->cmd_main);
	while (commands->cmds[*i]->cmd[*j] != '<'
		&& commands->cmds[*i]->cmd[*j] != '>'
		&& commands->cmds[*i]->cmd[*j] != '\0')
	{
		ft_arguments(commands, i, j);
		 *j += 1; //revisar porque aca hace un desborde de buffer de la memoria
	}
	commands->cmds[*i]->args[commands->parser.k] = NULL;
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
		&& commands->cmds[*i]->cmd[*j] != ' '
		&& commands->cmds[*i]->cmd[*j] != '>')
		(*j)++;
	filename = ft_substr(commands->cmds[*i]->cmd, start, *j - start);
	outfile->filename = filename;
	outfile->type = OUTFILE_TRUNC;
	int outfile_count = 0;
	while (commands->cmds[*i]->outfile && commands->cmds[*i]->outfile[outfile_count])
		outfile_count++;
	commands->cmds[*i]->outfile = ft_realloc(commands->cmds[*i]->outfile, sizeof(t_file *) * outfile_count, sizeof(t_file *) * (outfile_count + 2));
	commands->cmds[*i]->outfile[outfile_count] = outfile;
	commands->cmds[*i]->outfile[outfile_count + 1] = NULL;

	printf("\033[34mOutfile Type Trunc: %s\033[0m\n", outfile->filename);
}

void	ft_is_outfile_append(t_msh *commands, int *i, int *j)
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
	if (commands->cmds[*i]->cmd[*j] == '>')
		(*j)++;
	while (commands->cmds[*i]->cmd[*j] == ' ')
		(*j)++;
	start = *j;
	while (commands->cmds[*i]->cmd[*j] != '\0'
		&& commands->cmds[*i]->cmd[*j] != ' '
		&& commands->cmds[*i]->cmd[*j] != '>')
		(*j)++;
	filename = ft_substr(commands->cmds[*i]->cmd, start, *j - start);
	outfile->filename = filename;
	outfile->type = OUTFILE_APPEND;
	int outfile_count = 0;
	while (commands->cmds[*i]->outfile && commands->cmds[*i]->outfile[outfile_count])
		outfile_count++;
	commands->cmds[*i]->outfile = ft_realloc(commands->cmds[*i]->outfile, sizeof(t_file *) * outfile_count, sizeof(t_file *) * (outfile_count + 2));
	commands->cmds[*i]->outfile[outfile_count] = outfile;
	commands->cmds[*i]->outfile[outfile_count + 1] = NULL;

	printf("\033[34mOutfile Type Append: %s\033[0m\n", outfile->filename);
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
	int infile_count = 0;
	while (commands->cmds[*i]->infile && commands->cmds[*i]->infile[infile_count])
		infile_count++;
	commands->cmds[*i]->infile = ft_realloc(commands->cmds[*i]->infile, sizeof(t_file *) * infile_count, sizeof(t_file *) * (infile_count + 2));
	commands->cmds[*i]->infile[infile_count] = infile;
	commands->cmds[*i]->infile[infile_count + 1] = NULL;
	printf("\033[34mInfile Type Normal: %s\033[0m\n", infile->filename);
}

void	ft_is_infile_here_doc(t_msh *commands, int *i, int *j)
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
	infile->type = INFILE_HERE_DOC;
	int infile_count = 0;
	while (commands->cmds[*i]->infile && commands->cmds[*i]->infile[infile_count])
		infile_count++;
	commands->cmds[*i]->infile = ft_realloc(commands->cmds[*i]->infile, sizeof(t_file *) * infile_count, sizeof(t_file *) * (infile_count + 2));
	commands->cmds[*i]->infile[infile_count] = infile;
	commands->cmds[*i]->infile[infile_count + 1] = NULL;

	printf("\033[34mInfile Type Here Doc: %s\033[0m\n", infile->filename);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:54:39 by jdelorme          #+#    #+#             */
/*   Updated: 2024/10/09 12:12:18 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_two_clean_filename(char *filename)
{
	int	*quotes;

	quotes = ft_find_quotes(filename, 0);
	ft_rm_quotes(&filename, quotes);
	free(quotes);
	return (filename);
}

char	*parse_infile(t_msh *commands, int *i, int *j)
{
	int		start;
	char	*filename;

	while (commands->cmds[*i]->cmd[*j] != '<'
		&& commands->cmds[*i]->cmd[*j] != '\0')
		(*j)++;
	if (commands->cmds[*i]->cmd[*j] == '<')
		(*j)++;
	while (commands->cmds[*i]->cmd[*j] == ' ')
		(*j)++;
	start = *j;
	while (commands->cmds[*i]->cmd[*j] != '\0'
		&& commands->cmds[*i]->cmd[*j] != ' ')
		(*j)++;
	filename = ft_substr(commands->cmds[*i]->cmd, start, *j - start);
	filename = ft_two_clean_filename(filename);
	return (filename);
}

void	add_infile_to_command(t_msh *commands, int *i, char *filename)
{
	t_file	*infile;
	int		infile_count;

	infile_count = 0;
	infile = malloc(sizeof(t_file));
	if (!(infile))
		return ;
	infile->filename = filename;
	infile->type = INFILE_NORMAL;
	while (commands->cmds[*i]->infile
		&& commands->cmds[*i]->infile[infile_count])
		infile_count++;
	commands->cmds[*i]->infile = ft_realloc
		(commands->cmds[*i]->infile, sizeof(t_file *) * (infile_count + 1),
			sizeof(t_file *) * (infile_count + 2));
	if (!commands->cmds[*i]->infile)
	{
		free (infile);
		return ;
	}
	commands->cmds[*i]->infile[infile_count] = infile;
	commands->cmds[*i]->infile[infile_count + 1] = NULL;
	printf("\033[34mInfile Type Normal: %s\033[0m\n", infile->filename);
}

void	ft_is_infile(t_msh *commands, int *i, int *j)
{
	char	*filename;

	filename = parse_infile(commands, i, j);
	add_infile_to_command(commands, i, filename);
}

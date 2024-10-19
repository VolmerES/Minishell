/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_trunc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:52:03 by jdelorme          #+#    #+#             */
/*   Updated: 2024/10/19 18:00:38 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*extract_filename(t_msh *commands, int *i, int *j)
{
	int	start;

	while (commands->cmds[*i]->cmd[*j] == '>'
		|| commands->cmds[*i]->cmd[*j] == ' ')
		(*j)++;
	start = *j;
	while (commands->cmds[*i]->cmd[*j] != '\0'
		&& commands->cmds[*i]->cmd[*j] != ' '
		&& commands->cmds[*i]->cmd[*j] != '>')
		(*j)++;
	return (ft_substr(commands->cmds[*i]->cmd, start, *j - start));
}

char	*clean_filename(char *filename)
{
	int	*quotes;

	quotes = ft_find_quotes(filename, 0);
	ft_rm_quotes(&filename, quotes);
	free(quotes);
	return (filename);
}

void	ft_is_outfile_trunc(t_msh *commands, int *i, int *j)
{
	t_file	*outfile;
	char	*filename;
	int		outfile_count;

	outfile = malloc(sizeof(t_file));
	filename = extract_filename(commands, i, j);
	filename = clean_filename(filename);
	outfile->filename = filename;
	outfile->type = OUTFILE_TRUNC;
	outfile_count = 0;
	while (commands->cmds[*i]->outfile
		&& commands->cmds[*i]->outfile[outfile_count])
		outfile_count++;
	commands->cmds[*i]->outfile = ft_realloc(commands->cmds[*i]->outfile,
			sizeof(t_file *) * (outfile_count + 1),
			sizeof(t_file *) * (outfile_count + 2));
	commands->cmds[*i]->outfile[outfile_count] = outfile;
	commands->cmds[*i]->outfile[outfile_count + 1] = NULL;
}

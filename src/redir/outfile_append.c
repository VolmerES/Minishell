/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:53:38 by jdelorme          #+#    #+#             */
/*   Updated: 2024/10/08 19:54:02 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *extract_filename_append(t_msh *commands, int *i, int *j)
{
	int start;

	while (commands->cmds[*i]->cmd[*j] == '>' || commands->cmds[*i]->cmd[*j] == ' ')
		(*j)++;
	start = *j;

	while (commands->cmds[*i]->cmd[*j] != '\0' && commands->cmds[*i]->cmd[*j] != ' ' && commands->cmds[*i]->cmd[*j] != '>')
		(*j)++;
	char *filename = ft_substr(commands->cmds[*i]->cmd, start, *j - start);

	return filename;
}

char *clean_filename_append(char *filename)
{
	int *quotes = ft_find_quotes(filename, 0);
	ft_rm_quotes(&filename, quotes);
	free(quotes);
	return filename;
}

void ft_is_outfile_append(t_msh *commands, int *i, int *j)
{
	t_file *outfile = malloc(sizeof(t_file));
	char *filename = extract_filename_append(commands, i, j);
	filename = clean_filename_append(filename);

	outfile->filename = filename;
	outfile->type = OUTFILE_APPEND;
	int outfile_count = 0;
	while (commands->cmds[*i]->outfile && commands->cmds[*i]->outfile[outfile_count])
		outfile_count++;
	commands->cmds[*i]->outfile = ft_realloc(commands->cmds[*i]->outfile, sizeof(t_file *) * (outfile_count + 1), sizeof(t_file *) * (outfile_count + 2));
	commands->cmds[*i]->outfile[outfile_count] = outfile;
	commands->cmds[*i]->outfile[outfile_count + 1] = NULL;
	printf("\033[34mOutfile Type Append: %s\033[0m\n", outfile->filename);
}
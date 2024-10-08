/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:55:29 by jdelorme          #+#    #+#             */
/*   Updated: 2024/10/08 20:05:12 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *extract_delimiter_name(const char *cmd, int *j) 
{
	// Se elimina la llamada a ft_find_quotes aquí ya que no coincide con su definición esperada.
	int start = *j;
	while (cmd[*j] != '\0' && cmd[*j] != ' ' && cmd[*j] != '<')
		(*j)++;
	char *filename = ft_substr(cmd, start, *j - start);
	// Se ajusta la llamada a ft_rm_quotes para que solo tome el argumento esperado.
	int *quotes = ft_find_quotes(filename, 0);
	ft_rm_quotes(&filename, quotes);
	free(quotes);
	return filename;
}

// Función modificada para usar la nueva función auxiliar
char *parse_here_doc_filename(t_msh *commands, int *i, int *j)
{
	char *filename;
	// Avanza hasta encontrar el inicio del nombre del archivo
	while (commands->cmds[*i]->cmd[*j] != '<' && commands->cmds[*i]->cmd[*j] != '\0')
		(*j)++;
	if (commands->cmds[*i]->cmd[*j] == '<')
		(*j) += 2; // Salta ambos '<'
	while (commands->cmds[*i]->cmd[*j] == ' ')
		(*j)++;

	// Utiliza la nueva función para extraer el nombre del archivo delimitador
	filename = extract_delimiter_name(commands->cmds[*i]->cmd, j);

	return filename;
}

void add_here_doc_to_command(t_msh *commands, int *i, char *filename)
{
	t_file *infile;
	int infile_count;
	
	infile_count = 0;
	infile = malloc(sizeof(t_file));
	infile->filename = filename;
	infile->type = INFILE_HERE_DOC;
	while (commands->cmds[*i]->infile && commands->cmds[*i]->infile[infile_count])
		infile_count++;
	commands->cmds[*i]->infile = ft_realloc(commands->cmds[*i]->infile, sizeof(t_file *) * (infile_count + 1), sizeof(t_file *) * (infile_count + 2));
	commands->cmds[*i]->infile[infile_count] = infile;
	commands->cmds[*i]->infile[infile_count + 1] = NULL;
	if (infile->filename[0] == '\0') 
	{
		infile->filename = ft_strdup("EOF");
		printf("No end of file specified, using default EOF\n");
	} 
	else 
	{
		printf("\033[34mInfile Type Here Doc: [%s]\033[0m\n", infile->filename);
	}
}

void ft_is_infile_here_doc(t_msh *commands, int *i, int *j)
{
	char *filename;

	filename = parse_here_doc_filename(commands, i, j);
	add_here_doc_to_command(commands, i, filename);
}
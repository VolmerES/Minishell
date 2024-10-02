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
	int	squotes;
	int	dquotes;

	dquotes = 0;
	squotes = 0;
	while (commands->cmds[*i]->cmd[*j] == SPACE)
		(*j)++;
	if (commands->cmds[*i]->cmd_main == NULL)
	{
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
		if (commands->cmds[*i]->cmd[*j - 1] == SPACE && squotes == 0 && dquotes == 0)
			(*j)--;
		commands->cmds[*i]->cmd_main = ft_substr(commands->cmds[*i]->cmd, start, *j - start);
		printf("\033[34mMain command: [%s]\033[0m\n", commands->cmds[*i]->cmd_main);
	}
	while (commands->cmds[*i]->cmd[*j] == SPACE)
		(*j)++;
	while (commands->cmds[*i]->cmd[*j] != '<'
		&& commands->cmds[*i]->cmd[*j] != '>'
		&& commands->cmds[*i]->cmd[*j] != '\0'
		&& commands->cmds[*i]->cmd[*j] != ' ')
	{
		ft_arguments(commands, i, j);
	}
	if (commands->cmds[*i]->args)
		commands->cmds[*i]->args[commands->parser.k] = NULL;
}

void	ft_is_outfile_trunc(t_msh *commands, int *i, int *j)
{
	t_file	*outfile;
	char	*filename;
	int		start;

	outfile = malloc(sizeof(t_file));
	while (commands->cmds[*i]->cmd[*j] != '>' && commands->cmds[*i]->cmd[*j] != '\0')
		(*j)++;
	if (commands->cmds[*i]->cmd[*j] == '>')
		(*j)++;
	while (commands->cmds[*i]->cmd[*j] == ' ')
		(*j)++;
	start = *j;
	while (commands->cmds[*i]->cmd[*j] != '\0' && commands->cmds[*i]->cmd[*j] != ' ' && commands->cmds[*i]->cmd[*j] != '>')
		(*j)++;
	filename = ft_substr(commands->cmds[*i]->cmd, start, *j - start);

	// Verificar y eliminar comillas del inicio y del final si están presentes
	if ((filename[0] == '\"' && filename[strlen(filename) - 1] == '\"') || (filename[0] == '\'' && filename[strlen(filename) - 1] == '\''))
	{
		// Caso especial para comillas dobles dentro de comillas simples
		if (filename[0] == '\'' && filename[1] == '\"' && filename[strlen(filename) - 2] == '\"' && filename[strlen(filename) - 1] == '\'')
		{
			// Eliminar solo las comillas simples externas
			char *temp = filename;
			filename = ft_substr(filename, 1, strlen(filename) - 2);
			free(temp); // Liberar la memoria del string original
		}
		else
		{
			// Eliminar las comillas externas
			char *temp = filename;
			filename = ft_substr(filename, 1, strlen(filename) - 2);
			free(temp); // Liberar la memoria del string original
		}
	}

	outfile->filename = filename;
	outfile->type = OUTFILE_TRUNC;
	int outfile_count = 0;
	while (commands->cmds[*i]->outfile && commands->cmds[*i]->outfile[outfile_count])
		outfile_count++;
	commands->cmds[*i]->outfile = ft_realloc(commands->cmds[*i]->outfile, sizeof(t_file *) * (outfile_count + 1), sizeof(t_file *) * (outfile_count + 2));
	commands->cmds[*i]->outfile[outfile_count] = outfile;
	commands->cmds[*i]->outfile[outfile_count + 1] = NULL;

	printf("\033[34mOutfile Type Trunc: %s\033[0m\n", outfile->filename);
}

void	ft_is_outfile_append(t_msh *commands, int *i, int *j)
{
	t_file	*outfile;
	char	*filename;
	int		start;
	int     in_quotes = 0; // Indicador de comillas
	char    quote_char = '\0'; // Carácter de comilla detectado

	outfile = malloc(sizeof(t_file));
	while (commands->cmds[*i]->cmd[*j] != '>' && commands->cmds[*i]->cmd[*j] != '\0')
		(*j)++;
	if (commands->cmds[*i]->cmd[*j] == '>')
		(*j)++;
	if (commands->cmds[*i]->cmd[*j] == '>')
		(*j)++;
	while (commands->cmds[*i]->cmd[*j] == ' ')
		(*j)++;
	start = *j;
	// Detectar comillas al inicio del nombre del archivo
	if (commands->cmds[*i]->cmd[*j] == '\"' || commands->cmds[*i]->cmd[*j] == '\'') {
		in_quotes = 1;
		quote_char = commands->cmds[*i]->cmd[*j]; // Guardar el carácter de comilla detectado
		start++; // Comenzar después de la comilla inicial
		(*j)++; // Saltar la comilla inicial
	}
	// Continuar hasta encontrar el final del nombre del archivo
	while (commands->cmds[*i]->cmd[*j] != '\0' &&
		   ((in_quotes && commands->cmds[*i]->cmd[*j] != quote_char) ||
			(!in_quotes && commands->cmds[*i]->cmd[*j] != ' ' && commands->cmds[*i]->cmd[*j] != '>')))
		(*j)++;
	// Extraer el nombre del archivo
	filename = ft_substr(commands->cmds[*i]->cmd, start, *j - start);
	// Si terminamos dentro de comillas, ajustar el índice *j
	if (in_quotes && commands->cmds[*i]->cmd[*j] == quote_char) {
		(*j)++; // Saltar la comilla final
	}

	// Modificación para conservar comillas simples dentro de comillas dobles
	if (quote_char == '\"') {
		// Si el nombre del archivo estaba encerrado en comillas dobles, eliminar solo las comillas dobles externas
		char *temp = filename;
		filename = ft_substr(filename, 0, strlen(filename)); // Conservar el contenido incluyendo comillas simples internas
		free(temp); // Liberar la memoria del string original
	} else {
		// Procesamiento original para eliminar comillas al inicio y al final si son las únicas presentes
		if ((filename[0] == '\"' || filename[0] == '\'') && filename[strlen(filename) - 1] == filename[0]) {
			if (strchr(filename + 1, filename[0]) == strrchr(filename, filename[0])) {
				char *temp = filename;
				filename = ft_substr(filename, 1, strlen(filename) - 2);
				free(temp); // Liberar la memoria del string original
			}
		}
	}

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

void	ft_is_infile(t_msh *commands, int *i, int *j)
{
    t_file	*infile;
    char	*filename;
    int		start;
    int     in_quotes = 0; // Indicador de comillas

    infile = malloc(sizeof(t_file));
    if (!infile) return; // Comprobación de error de malloc
    while (commands->cmds[*i]->cmd[*j] != '<' && commands->cmds[*i]->cmd[*j] != '\0')
        (*j)++;
    if (commands->cmds[*i]->cmd[*j] == '<')
        (*j)++;
    while (commands->cmds[*i]->cmd[*j] == ' ')
        (*j)++;
    start = *j;
    if (commands->cmds[*i]->cmd[*j] == '\"' || commands->cmds[*i]->cmd[*j] == '\'') {
        in_quotes = 1;
        start++;
        (*j)++;
    }
    while (commands->cmds[*i]->cmd[*j] != '\0' &&
           ((in_quotes && commands->cmds[*i]->cmd[*j] != commands->cmds[*i]->cmd[start - 1]) ||
            (!in_quotes && commands->cmds[*i]->cmd[*j] != ' ' && commands->cmds[*i]->cmd[*j] != '<')))
        (*j)++;
    filename = ft_substr(commands->cmds[*i]->cmd, start, *j - start);
    if (in_quotes && (commands->cmds[*i]->cmd[*j] == '\"' || commands->cmds[*i]->cmd[*j] == '\'')) {
        (*j)++;
    }
    if ((filename[0] == '\"' || filename[0] == '\'') && (filename[strlen(filename) - 1] == '\"' || filename[strlen(filename) - 1] == '\'')) {
        char *temp = filename;
        filename = ft_substr(filename, 1, strlen(filename) - 2);
        free(temp);
    }

    infile->filename = filename;
    infile->type = INFILE_NORMAL;
    int infile_count = 0;
    while (commands->cmds[*i]->infile && commands->cmds[*i]->infile[infile_count])
        infile_count++;
    commands->cmds[*i]->infile = ft_realloc(commands->cmds[*i]->infile, sizeof(t_file *) * (infile_count + 1), sizeof(t_file *) * (infile_count + 2));
    if (!commands->cmds[*i]->infile) { // Comprobación de error de realloc
        free(infile->filename);
        free(infile);
        return;
    }
    commands->cmds[*i]->infile[infile_count] = infile;
    commands->cmds[*i]->infile[infile_count + 1] = NULL;

    printf("\033[34mInfile Type Normal: %s\033[0m\n", infile->filename);
}
void	ft_is_infile_here_doc(t_msh *commands, int *i, int *j)
{
	t_file	*infile;
	char	*filename;
	int		start;
	int     in_quotes = 0; // Indicador de comillas

	infile = malloc(sizeof(t_file));
	while (commands->cmds[*i]->cmd[*j] != '<' && commands->cmds[*i]->cmd[*j] != '\0')
		(*j)++;
	if (commands->cmds[*i]->cmd[*j] == '<')
		(*j)++;
	if (commands->cmds[*i]->cmd[*j] == '<')
		(*j)++;
	while (commands->cmds[*i]->cmd[*j] == ' ')
		(*j)++;
	start = *j;
	// Detectar comillas al inicio del nombre del archivo
	if (commands->cmds[*i]->cmd[*j] == '\"' || commands->cmds[*i]->cmd[*j] == '\'') {
		in_quotes = 1;
		start++; // Comenzar después de la comilla inicial
		(*j)++; // Saltar la comilla inicial
	}
	// Continuar hasta encontrar el final del nombre del archivo
	while (commands->cmds[*i]->cmd[*j] != '\0' &&
		   ((in_quotes && commands->cmds[*i]->cmd[*j] != '\"' && commands->cmds[*i]->cmd[*j] != '\'') ||
			(!in_quotes && commands->cmds[*i]->cmd[*j] != ' ' && commands->cmds[*i]->cmd[*j] != '<')))
		(*j)++;
	// Extraer el nombre del archivo
	filename = ft_substr(commands->cmds[*i]->cmd, start, *j - start);
	// Si terminamos dentro de comillas, ajustar el índice *j 
	if (in_quotes && (commands->cmds[*i]->cmd[*j] == '\"' || commands->cmds[*i]->cmd[*j] == '\'')) {
		(*j)++; // Saltar la comilla final
	}

	// Verificar y eliminar comillas del inicio y del final si están presentes
	if ((filename[0] == '\"' && filename[strlen(filename) - 1] == '\"') || (filename[0] == '\'' && filename[strlen(filename) - 1] == '\''))
	{
		// Caso especial para comillas dobles dentro de comillas simples
		if (filename[0] == '\'' && filename[1] == '\"' && filename[strlen(filename) - 2] == '\"' && filename[strlen(filename) - 1] == '\'')
		{
			// Eliminar solo las comillas simples externas
			char *temp = filename;
			filename = ft_substr(filename, 1, strlen(filename) - 2);
			free(temp); // Liberar la memoria del string original
		}
		else
		{
			// Eliminar las comillas externas
			char *temp = filename;
			filename = ft_substr(filename, 1, strlen(filename) - 2);
			free(temp); // Liberar la memoria del string original
		}
	}
	infile->filename = filename;
	infile->type = INFILE_HERE_DOC;
	int infile_count = 0;
	while (commands->cmds[*i]->infile && commands->cmds[*i]->infile[infile_count])
		infile_count++;
	commands->cmds[*i]->infile = ft_realloc(commands->cmds[*i]->infile, sizeof(t_file *) * (infile_count + 1), sizeof(t_file *) * (infile_count + 2));
	commands->cmds[*i]->infile[infile_count] = infile;
	commands->cmds[*i]->infile[infile_count + 1] = NULL;
	if (infile->filename[0] == '\0')
	{
		infile->filename = ft_strdup("EOF");
		printf("No end of file specified, using default EOF\n");
		return;
	}

	printf("\033[34mInfile Type Here Doc: [%s]\033[0m\n", infile->filename);
}

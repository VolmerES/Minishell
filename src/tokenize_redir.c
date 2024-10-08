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

int	ft_locate_next_quote(int i, char *input, char quote)
{
	while (input && input[i] && input[i] != quote)
		i++;
	return (i);
}
int	ft_has_quotes(char *str, int i)
{
	i--;
	while (str && str[++i] != '\0')
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
	return (0);
}

int	*ft_find_quotes(char *str, int i)
{
	int	*quotes;

	quotes = ft_calloc(sizeof(int), 2);
	while (str[i] != '\0' && str[i] != '\"' && str[i] != '\'')
		i++;
	quotes[0] = i;
	if (str[i] && str[i + 1])
	{
		quotes[1] = ft_locate_next_quote(i + 1, str, str[i]);
		if (str[quotes[1]] == '\0')
			quotes[1] = -1;
	}
	else
		quotes[1] = -1;
	return (quotes);
}

static void	ft_remove_quotes(char **str, int *pos)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (pos[0] == -1 || pos[1] == -1)
		return ;
	result = ft_calloc(sizeof(char), ft_strlen(*str) - 2 + 1);
	while (i < pos[0])
		result[j++] = (*str)[i++];
	i++;
	while (i < pos[1])
		result[j++] = (*str)[i++];
	i++;
	while ((*str)[i] != '\0')
		result[j++] = (*str)[i++];
	result[j] = '\0';
	free(*str);
	*str = result;
}

void	ft_rm_quotes(char **str, int *quotes)
{
	char	*result;
	int		*quotes2;

	if (ft_has_quotes(*str, 0) == 0)
		return ;
	result = ft_strdup(*str);
	free(*str);
	ft_remove_quotes(&result, quotes);
	while (ft_has_quotes(result, quotes[1] - 1) == 1)
	{
		quotes2 = ft_find_quotes(result, quotes[1] - 1);
		ft_remove_quotes(&result, quotes2);
		free(quotes);
		quotes = quotes2;
	}
	*str = result;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	ft_update_quote_flags(char c, int *squotes, int *dquotes)
{
	if (c == SQUOTES)
		*squotes = !(*squotes);
	if (c == DQUOTES)
		*dquotes = !(*dquotes);
}

void	ft_set_main_command(t_msh *commands, int *i, int *j)
{
	int	start;
	int	squotes;
	int	dquotes;

	squotes = 0;
	dquotes = 0;
	while (commands->cmds[*i]->cmd[*j] == SPACE)
		(*j)++;
	if (commands->cmds[*i]->cmd_main == NULL)
	{
		start = *j;
		while (commands->cmds[*i]->cmd[*j] != '\0'
			   && (squotes == 1 || dquotes == 1
			   || (commands->cmds[*i]->cmd[*j] != ' '
			   && commands->cmds[*i]->cmd[*j] != '<'
			   && commands->cmds[*i]->cmd[*j] != '>')))
		{
			ft_update_quote_flags(commands->cmds[*i]->cmd[*j], &squotes, &dquotes);
			(*j)++;
		}
		if (commands->cmds[*i]->cmd[*j - 1] == SPACE && squotes == 0 && dquotes == 0)
			(*j)--;
		commands->cmds[*i]->cmd_main = ft_substr(commands->cmds[*i]->cmd, start, *j - start);
		printf("\033[34mMain command: [%s]\033[0m\n", commands->cmds[*i]->cmd_main);
	}
}

void ft_is_command(t_msh *commands, int *i, int *j)
{
	ft_set_main_command(commands, i, j);
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
/************************************************************************************************************** */
//OUTFILE TRUNC

char *extract_filename(t_msh *commands, int *i, int *j)
{
	int start;
	while (commands->cmds[*i]->cmd[*j] == '>' || commands->cmds[*i]->cmd[*j] == ' ')
		(*j)++;
	start = *j;
	while (commands->cmds[*i]->cmd[*j] != '\0' && commands->cmds[*i]->cmd[*j] != ' ' && commands->cmds[*i]->cmd[*j] != '>')
		(*j)++;
	return ft_substr(commands->cmds[*i]->cmd, start, *j - start);
}

char *clean_filename(char *filename)
{
	int *quotes = ft_find_quotes(filename, 0);
	ft_rm_quotes(&filename, quotes);
	return filename;
}

void ft_is_outfile_trunc(t_msh *commands, int *i, int *j)
{
	t_file *outfile = malloc(sizeof(t_file));
	char *filename = extract_filename(commands, i, j);
	filename = clean_filename(filename);

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
/************************************************************************************************************** */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//OUTFILE APPEND
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
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/************************************************************************************************************** */
//INFILE
char *ft_two_clean_filename(char *filename) 
{
	int *quotes = ft_find_quotes(filename, 0);
	ft_rm_quotes(&filename, quotes);
	return filename;
}

char *parse_infile(t_msh *commands, int *i, int *j) 
{
	int start;
	char *filename;
	while (commands->cmds[*i]->cmd[*j] != '<' && commands->cmds[*i]->cmd[*j] != '\0')
		(*j)++;
	if (commands->cmds[*i]->cmd[*j] == '<')
		(*j)++;
	while (commands->cmds[*i]->cmd[*j] == ' ')
		(*j)++;
	start = *j;
	while (commands->cmds[*i]->cmd[*j] != '\0' && commands->cmds[*i]->cmd[*j] != ' ')
		(*j)++;
	filename = ft_substr(commands->cmds[*i]->cmd, start, *j - start);
	filename = ft_two_clean_filename(filename);
	return filename;
}

void add_infile_to_command(t_msh *commands, int *i, char *filename) {
	t_file *infile;
	int infile_count = 0;
	if (!(infile = malloc(sizeof(t_file))))
		return;

	infile->filename = filename;
	infile->type = INFILE_NORMAL;
	while (commands->cmds[*i]->infile && commands->cmds[*i]->infile[infile_count]) infile_count++;
	commands->cmds[*i]->infile = ft_realloc(commands->cmds[*i]->infile, sizeof(t_file *) * (infile_count + 1), sizeof(t_file *) * (infile_count + 2));
	if (!commands->cmds[*i]->infile) {
		free(infile);
		return;
	}
	commands->cmds[*i]->infile[infile_count] = infile;
	commands->cmds[*i]->infile[infile_count + 1] = NULL;
	printf("\033[34mInfile Type Normal: %s\033[0m\n", infile->filename);
}

void ft_is_infile(t_msh *commands, int *i, int *j) {
	char *filename = parse_infile(commands, i, j);
	add_infile_to_command(commands, i, filename);
}
/************************************************************************************************************** */
//HERE DOC
// Nueva función para extraer el nombre del archivo delimitador


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
	return filename;
}

// Función modificada para usar la nueva función auxiliar
char *parse_here_doc_filename(t_msh *commands, int *i, int *j) {
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

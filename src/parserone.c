/* ************************************************************************** */
/*                                                                            */
/*   minishell.h                                          :::      ::::::::   */
/*                                     					:+:      :+:    :+:   */
/*   By: juan <juan@student.42.fr>                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:50:45 by jdelorme          #+#    #+#             */
/*   Updated: 2024/04/15 13:10:34 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_allocate_commands(t_msh *commands)
{
	int	i;
	int	pipes;

	pipes = ft_count_pipes(commands);
	commands->cmds = malloc(sizeof(t_cmd *) * (pipes + 1));
	if (commands->cmds == NULL)
	{
		fprintf(stderr, "Error al asignar memoria para los comandos\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < pipes)
	{
		commands->cmds[i] = malloc(sizeof(t_cmd) * 1);
		set_null(commands, i);
		if (!commands->cmds[i])
			exit_(2);
		i++;
	}
	commands->cmds[i] = NULL;
}

void	ft_process_character(t_msh *commands)
{
	char	current_char;
	int		*index;

	current_char = commands->input[commands->parser.index];
	index = &(commands->parser.index);
	if (current_char == DQUOTES && !commands->parser.in_single_quotes)
		commands->parser.in_quotes = !(commands->parser.in_quotes);
	else if (current_char == SQUOTES && !commands->parser.in_quotes)
		commands->parser.in_single_quotes = \
		!(commands->parser.in_single_quotes);
	if (current_char == PIPE
		&& !commands->parser.in_quotes
		&& !commands->parser.in_single_quotes)
	{
		ft_add_command(commands, &(commands->parser.start),
			index, &(commands->parser.cmd_index));
	}
	(*index)++;
}

void	ft_add_command(t_msh *commands, int *start, int *index, int *cmd_index)
{
	char *tmp; //! strndup
	commands->cmds[*cmd_index]->cmd = strndup(&commands->input[*start], *index
			- *start);
	tmp = ft_strtrim(commands->cmds[*cmd_index]->cmd, " ");
	free(commands->cmds[*cmd_index]->cmd);
	commands->cmds[*cmd_index]->cmd = tmp;
	if (commands->cmds[*cmd_index]->cmd == NULL)
	{
		fprintf(stderr,
			"Error al asignar memoria para el string del comando\n");
		exit(EXIT_FAILURE);
	}
	(*cmd_index)++;
	*start = *index + 1;
}

void	ft_print_commands(t_msh *commands)
{
	int	i;

	i = 0;
	while (commands->cmds[i] != NULL)
	{
		printf("Comando %d: %s\n", i, commands->cmds[i]->cmd);
		i++;
	}
}

void	ft_parse_input(t_msh *commands)
{
	commands->parser.index = 0;
	commands->parser.start = 0;
	commands->parser.in_quotes = 0;
	commands->parser.cmd_index = 0;
	commands->parser.in_single_quotes = 0;
	ft_allocate_commands(commands);
	while (commands->input[commands->parser.index] != '\0')
		ft_process_character(commands);
	ft_add_command(commands, &(commands->parser.start),
		&(commands->parser.index), &(commands->parser.cmd_index));
	commands->cmds[commands->parser.cmd_index] = NULL;
	ft_print_commands(commands);
}

#include "../inc/minishell.h"

void	ft_allocate_commands(t_msh *commands)
{
	commands->cmds = malloc(sizeof(t_cmd *) * MAX_COMMANDS);
	if (commands->cmds == NULL)
	{
		fprintf(stderr, "Error al asignar memoria para los comandos\n");
		exit(EXIT_FAILURE);
	}
}

void	ft_process_character(t_msh *commands)
{
	if (commands->input[commands->parser.index] == DQUOTES && (commands->parser.index == 0
			|| commands->input[commands->parser.index - 1] != BACKSLASH))
		commands->parser.in_quotes = !(commands->parser.in_quotes);
	else if (commands->input[commands->parser.index] == SQUOTES && (commands->parser.index == 0
			|| commands->input[commands->parser.index - 1] != BACKSLASH))
		commands->parser.in_single_quotes = !(commands->parser.in_single_quotes);
	else if (commands->input[commands->parser.index] == PIPE && !(commands->parser.in_quotes)
		&& !(commands->parser.in_single_quotes))
		ft_add_command(commands, &(commands->parser.start), &(commands->parser.index), &(commands->parser.cmd_index));
	(commands->parser.index)++;
}

void	ft_add_command(t_msh *commands, int *start, int *index, int *cmd_index)
{
	commands->cmds[*cmd_index] = malloc(sizeof(t_cmd));
	if (commands->cmds[*cmd_index] == NULL)
	{
		fprintf(stderr, "Error al asignar memoria para el comando\n");
		exit(EXIT_FAILURE);
	}
	commands->cmds[*cmd_index]->cmd = strndup(&commands->input[*start], *index
			- *start);
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
	for (int i = 0; commands->cmds[i] != NULL; i++)
		printf("Comando %d: %s\n", i, commands->cmds[i]->cmd);
}
/**/
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
	ft_add_command(commands, &(commands->parser.start), &(commands->parser.index), &(commands->parser.cmd_index));
	commands->cmds[commands->parser.cmd_index + 1] = NULL;
	ft_print_commands(commands);
}
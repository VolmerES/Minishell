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

void	ft_process_character(t_msh *commands, int *index, int *start,
		int *in_quotes, int *cmd_index, int *in_single_quotes)
{
	if (commands->input[*index] == DQUOTES && (*index == 0
			|| commands->input[*index - 1] != BACKSLASH))
		*in_quotes = !*in_quotes;
	else if (commands->input[*index] == SQUOTES && (*index == 0
			|| commands->input[*index - 1] != BACKSLASH))
		*in_single_quotes = !*in_single_quotes;
	else if (commands->input[*index] == PIPE && !*in_quotes
		&& !*in_single_quotes)
		ft_add_command(commands, start, index, cmd_index);
	(*index)++;
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
	int index = 0;
	int start = 0;
	int in_quotes = 0;
	int cmd_index = 0;
	int in_single_quotes = 0;

	ft_allocate_commands(commands);
	while (commands->input[index] != '\0')
		ft_process_character(commands, &index, &start, &in_quotes, &cmd_index,
			&in_single_quotes);
	ft_add_command(commands, &start, &index, &cmd_index);
	commands->cmds[cmd_index + 1] = NULL;
	ft_print_commands(commands);
}
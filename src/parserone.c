#include "../inc/minishell.h"

void allocate_commands(t_msh *commands)
{
    commands->cmds = malloc(sizeof(t_cmd *) * MAX_COMMANDS);
    if (commands->cmds == NULL)
    {
        fprintf(stderr, "Error al asignar memoria para los comandos\n");
        exit(EXIT_FAILURE);
    }
}

void process_character(t_msh *commands, int *index, int *start, int *in_quotes, int *cmd_index,  int *in_single_quotes)
{
    if (commands->input[*index] == DQUOTES && (*index == 0 || commands->input[*index - 1] != BACKSLASH))
        *in_quotes = !*in_quotes;
    else if (commands->input[*index] == SQUOTES && (*index == 0 || commands->input[*index - 1] != BACKSLASH))
        *in_single_quotes = !*in_single_quotes;
    else if (commands->input[*index] == PIPE && !*in_quotes && !*in_single_quotes)
        add_command(commands, start, index, cmd_index);
    (*index)++;
}

void add_command(t_msh *commands, int *start, int *index, int *cmd_index)
{
    commands->cmds[*cmd_index] = malloc(sizeof(t_cmd));
    if (commands->cmds[*cmd_index] == NULL)
    {
        fprintf(stderr, "Error al asignar memoria para el comando\n");
        exit(EXIT_FAILURE);
    }
    commands->cmds[*cmd_index]->cmd = strndup(&commands->input[*start], *index - *start);
    if (commands->cmds[*cmd_index]->cmd == NULL)
    {
        fprintf(stderr, "Error al asignar memoria para el string del comando\n");
        exit(EXIT_FAILURE);
    }
    (*cmd_index)++;
    *start = *index + 1;
}

void print_commands(t_msh *commands)
{
    for (int i = 0; commands->cmds[i] != NULL; i++)
        printf("Comando %d: %s\n", i, commands->cmds[i]->cmd);
}

void ft_parse_input(t_msh *commands)
{
    int index = 0;
    int start = 0;
    int in_quotes = 0;
    int cmd_index = 0;
    int in_single_quotes = 0;

    allocate_commands(commands);
    while (commands->input[index] != '\0')
        process_character(commands, &index, &start, &in_quotes, &cmd_index, &in_single_quotes);
    add_command(commands, &start, &index, &cmd_index);
    commands->cmds[cmd_index + 1] = NULL;
    print_commands(commands);
}
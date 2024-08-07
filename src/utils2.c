#include "../inc/minishell.h"

void	set_null(t_msh *commands, int index)
{
	commands->cmds[index]->infile = NULL;
	commands->cmds[index]->outfile = NULL;
	commands->cmds[index]->cmd_main = NULL;
	commands->cmds[index]->cmd = NULL;
	commands->cmds[index]->args = NULL;
	commands->cmds[index]->full_cmd = NULL;
}
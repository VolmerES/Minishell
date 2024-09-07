	#include "../inc/minishell.h"

	static void free_aux(t_msh *commands, int count)
	{
		int i;

		i = 0;
		while (commands->cmds[count]->infile[i])
		{
			if (commands->cmds[count]->infile[i]->filename)
			{
				free(commands->cmds[count]->infile[i]->filename);
				commands->cmds[count]->infile[i]->filename = NULL;
			}
			i++;
		}
		free(commands->cmds[count]->infile);
		commands->cmds[count]->infile = NULL;
	}

	void free_struct(t_msh *commands)
	{
		int count;

		count = 0;
		while (count < commands->parser.cmd_index)
		{
			if (commands->cmds[count]->args)
				ft_free_matrix(commands->cmds[count]->args);
			if (commands->cmds[count]->full_cmd)
				ft_free_matrix(commands->cmds[count]->full_cmd);
			if (commands->cmds[count]->cmd_main)
				free(commands->cmds[count]->cmd_main);
			if (commands->cmds[count]->infile)
				free_aux(commands, count);
			if (commands->cmds[count]->outfile)
				free_aux(commands, count);
			free(commands->cmds[count]->cmd);
			free(commands->cmds[count]);
			count++;
		}
		free(commands->cmds);
		// if (commands->evar)
		// 	free(commands->evar);
		free(commands->input);
	}

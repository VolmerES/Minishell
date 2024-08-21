	#include "../inc/minishell.h"

	static void free_aux(t_file **list)
	{
		int i;

		i = 0;
		while (list[i])
		{
			if (list[i]->filename)
			{
				free(list[i]->filename);
				list[i]->filename = NULL;
			}
			i++;
		}
		free(list);
		list = NULL;
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
				free_aux(commands->cmds[count]->infile);
			if (commands->cmds[count]->outfile)
				free_aux(commands->cmds[count]->outfile);
			free(commands->cmds[count]->cmd);
			free(commands->cmds[count]);
			count++;
		}
		free(commands->cmds);
		// if (commands->evar)
		// 	free(commands->evar);
		free(commands->input);
	}

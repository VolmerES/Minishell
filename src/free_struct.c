	#include "../inc/minishell.h"

	static void free_infile(t_msh *commands, int count)
	{
		int i;

		i = 0;
		while (commands->cmds[count]->infile[i])
		{
			if (commands->cmds[count]->infile[i]->filename)
			{
				free(commands->cmds[count]->infile[i]->filename);
				commands->cmds[count]->infile[i]->filename = NULL;
				free(commands->cmds[count]->infile[i]);
				commands->cmds[count]->infile[i] = NULL;
			}
			i++;
		}
		free(commands->cmds[count]->infile);
		commands->cmds[count]->infile = NULL;
	}

	static void free_outfile(t_msh *commands, int count)
	{
		int i;

		i = 0;
		while (commands->cmds[count]->outfile[i])
		{
			if (commands->cmds[count]->outfile[i]->filename)
			{
				free(commands->cmds[count]->outfile[i]->filename);
				commands->cmds[count]->outfile[i]->filename = NULL;
				free(commands->cmds[count]->outfile[i]);
				commands->cmds[count]->outfile[i] = NULL;
			}
			i++;
		}
		free(commands->cmds[count]->outfile);
		commands->cmds[count]->outfile = NULL;
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
				free_infile(commands, count);
			if (commands->cmds[count]->outfile)
				free_outfile(commands, count);
			free(commands->cmds[count]->cmd);
			free(commands->cmds[count]);
			count++;
		}
		free(commands->cmds);
		// if (commands->evar)
		// 	free(commands->evar);
		free(commands->input);
	}

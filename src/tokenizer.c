/* ************************************************************************** */
/*                                                                            */
/*   tokenizer.c                                          :::      ::::::::   */
/*                                     					 :+:      :+:    :+:  */
/*   By: juan <juan@student.42.fr>                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:50:45 by jdelorme          #+#    #+#             */
/*   Updated: 2024/03/05 22:50:46 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	increment_j(t_msh *commands, int *i, int *j)
{
	int	squotes;
	int dquotes;

	squotes = 0;
	dquotes = 0;
	while (commands->cmds[*i]->cmd[*j] != '\0'
		&& (squotes == 1 || dquotes == 1 || (commands->cmds[*i]->cmd[*j] != SPACE
		&& commands->cmds[*i]->cmd[*j] != '<'
		&& commands->cmds[*i]->cmd[*j] != '>')))
	{
		if (commands->cmds[*i]->cmd[*j] == SQUOTES)
			squotes = !squotes;
		if (commands->cmds[*i]->cmd[*j] == DQUOTES)
			dquotes = !dquotes;
		(*j)++;
	}
	return (*j);
}

void	ft_arguments(t_msh *commands, int *i, int *j)
{
	int	start;
	int	k;

	k = 0;
	while (commands->cmds[*i]->cmd[*j] == SPACE)
		(*j)++;
	start = *j;
	*j = increment_j(commands, i, j);
	commands->cmds[*i]->args = malloc(sizeof(t_cmd()));
	commands->cmds[*i]->args[k] = ft_substr(commands->cmds[*i]->cmd, start, *j
			- start);
	printf("Argumento: %s\n", commands->cmds[*i]->args[k]);
	commands->cmds[*i]->args = NULL;
}

void	ft_tokenize_command(t_msh *commands, int *i)
{
	int	j;

	j = 0;
	while (commands->cmds[*i]->cmd[j] != '\0')
	{
		if (commands->cmds[*i]->cmd[j] == '<')
		{
			if (commands->cmds[*i]->cmd[j + 1] == '<')
			{
				if (commands->cmds[*i]->cmd[j + 2] == '<' 
				|| commands->cmds[*i]->cmd[j + 2] == '\0'
				|| commands->cmds[*i]->cmd[j + 1] != '<')
					return ;
				ft_is_infile_here_doc(commands, i, &j);
				j = j + 1;
			}
			else if (commands->cmds[*i]->cmd[j + 1] != '<' && commands->cmds[*i]->cmd[j + 2] != '<')
			{
				if (commands->cmds[*i]->cmd[j + 1] == '\0')
					return ;
				ft_is_infile(commands, i, &j);
				j = j + 1;
			}
		}
		else if (commands->cmds[*i]->cmd[j] == '>')
		{
			if (commands->cmds[*i]->cmd[j + 1] == '>')
				ft_is_outfile_append(commands, i, &j);
			else
				ft_is_outfile_trunc(commands, i, &j);
		}
		else
		{
			ft_is_command(commands, i, &j);
		}
	}
}

void	ft_tokenize(t_msh *commands)
{
	int	i;

	i = 0;
	while (commands->cmds[i] != NULL)
	{
		ft_tokenize_command(commands, &i);
		i++;
	}
}

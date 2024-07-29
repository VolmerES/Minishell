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

void ft_free_args(t_msh *commands, int *i)
{
	int j;

	j = 0;
	while (commands->cmds[*i]->args[j] != NULL)
	{
		free(commands->cmds[*i]->args[j]);
		j++;
	}
	free(commands->cmds[*i]->args);
}

void	ft_set_null(t_msh *commands)
{
	int	i;

	i = 0;
	while (commands->cmds[i] != NULL)
	{
		i++;
	}
	i--;
	while (i >= 0)
	{
		commands->cmds[i]->infile = NULL;
		commands->cmds[i]->outfile = NULL;
		commands->cmds[i]->cmd_main = NULL;
		commands->cmds[i]->args = NULL;
		i--;
	}
}

int	increment_j(t_msh *commands, int *i, int *j)
{
	int	squotes;
	int	dquotes;

	squotes = 0;
	dquotes = 0;
	while (commands->cmds[*i]->cmd[*j] != '\0'
		&& (squotes == 1 || dquotes == 1
			|| (commands->cmds[*i]->cmd[*j] != SPACE
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

	while (commands->cmds[*i]->cmd[*j] == SPACE)
		(*j)++;
	start = *j;
	*j = increment_j(commands, i, j);
	commands->cmds[*i]->args[commands->parser.k]
		= ft_substr(commands->cmds[*i]->cmd, start, *j
			- start);
	if (commands->cmds[*i]->args[commands->parser.k] == NULL)
	{
		ft_free_args(commands, i);
		exit(1);
	}
	commands->parser.k++;
	ft_erase_arg_quotes(commands, i);
}

void	ft_tokenize_command(t_msh *commands, int *i)
{
	int	j;

	j = 0;
	commands->parser.k = 0;
	commands->cmds[*i]->args = malloc(sizeof(char *) * MAX_COMMANDS); //! revisar memoria
	while (commands->cmds[*i]->cmd[j] != '\0')
	{
		if (commands->cmds[*i]->cmd[j] == '<')
			ft_handle_less_than(commands, i, &j);
		else if (commands->cmds[*i]->cmd[j] == '>')
			ft_handle_greater_than(commands, i, &j);
		else if (commands->cmds[*i]->cmd[j] == SPACE)
			j++;
		else
			ft_handle_else(commands, i, &j);
	}
}

void	ft_tokenize(t_msh *commands)
{
	int	i;

	i = 0;
	ft_set_null(commands);
	while (commands->cmds[i] != NULL)
	{
		ft_tokenize_command(commands, &i);
		i++;
	}
}

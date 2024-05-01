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

void ft_trim_end(char *str)
{
	int i = strlen(str) - 1;
	while (i >= 0 && str[i] == ' ')
	{
		str[i] = '\0';
		i--;
	}
}
void	ft_erase_cmd_quotes(t_msh *commands, int *i)
{
	int	j;
	int	cmd_len;

	j = 0;
	ft_trim_end(commands->cmds[*i]->cmd);
	cmd_len = ft_strlen(commands->cmds[*i]->cmd);
	while (j < cmd_len)
	{
		if (commands->cmds[*i]->cmd_main[j] == SQUOTES || commands->cmds[*i]->cmd_main[j] == DQUOTES)
		{
			ft_memmove(&commands->cmds[*i]->cmd_main[j], &commands->cmds[*i]->cmd_main[j + 1], cmd_len - j - 1);
			commands->cmds[*i]->cmd_main[cmd_len - 1] = '\0';
			cmd_len--;
		}
		else
		{
			j++;
		}
	}
}

void	ft_set_NULL(t_msh *commands, int *i)
{
	int	j;

	j = 0;
	while (commands->cmds[*i]->args[j] != NULL)
		j++;
	commands->cmds[*i]->args[j] = NULL;
}
void	ft_erase_arg_quotes(t_msh *commands, int *i)
{
	int	j;
	int	arg_len;

	ft_erase_cmd_quotes(commands, i);
	j = 0;
	while (commands->cmds[*i]->args[j] != NULL)
	{
		arg_len = ft_strlen(commands->cmds[*i]->args[j]);
		if ((commands->cmds[*i]->args[j][0] == SQUOTES || commands->cmds[*i]->args[j][0] == DQUOTES) &&
			(commands->cmds[*i]->args[j][arg_len - 1] == SQUOTES || commands->cmds[*i]->args[j][arg_len - 1] == DQUOTES))
		{
			ft_memmove(&commands->cmds[*i]->args[j][0], &commands->cmds[*i]->args[j][1], arg_len - 2);
			commands->cmds[*i]->args[j][arg_len - 2] = '\0';
		}
		j++;
	}
	ft_set_NULL(commands, i);
}

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
	commands->cmds[*i]->args[commands->parser.k] = ft_substr(commands->cmds[*i]->cmd, start, *j
			- start);
	//printf("Argumento: %s\n", commands->cmds[*i]->args[k]);
	commands->parser.k++;
}

void	ft_tokenize_command(t_msh *commands, int *i)
{
	int	j;

	j = 0;
	commands->parser.k = 0;
	commands->cmds[*i]->args = malloc(sizeof(t_cmd()));
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
		ft_erase_arg_quotes(commands, &i);
		i++;
	}
}

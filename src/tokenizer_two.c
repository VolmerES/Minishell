/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:11:39 by jdelorme          #+#    #+#             */
/*   Updated: 2024/10/19 18:26:41 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_handle_less_than(t_msh *commands, int *i, int *j)
{
	if (commands->cmds[*i]->cmd[*j + 1] == '<')
	{
		if (commands->cmds[*i]->cmd[*j + 2] == '<'
			|| commands->cmds[*i]->cmd[*j + 1] != '<')
			return ;
		ft_is_infile_here_doc(commands, i, j);
		*j = *j + 1;
	}
	else if (commands->cmds[*i]->cmd[*j + 1] != '<'
		&& commands->cmds[*i]->cmd[*j + 2] != '<')
	{
		if (commands->cmds[*i]->cmd[*j + 1] == '\0')
			return ;
		ft_is_infile(commands, i, j);
		*j = *j + 1;
	}
}

void	ft_handle_greater_than(t_msh *commands, int *i, int *j)
{
	if (commands->cmds[*i]->cmd[*j + 1] == '>')
		ft_is_outfile_append(commands, i, j);
	else
		ft_is_outfile_trunc(commands, i, j);
}

void	ft_handle_else(t_msh *commands, int *i, int *j)
{
	ft_is_command(commands, i, j);
	ft_erase_cmd_quotes(commands, i);
}

int	check_consecutive_chars(char *str, char c)
{
	int	count;

	count = 0;
	while (*str == c)
	{
		count++;
		str++;
		if (count >= 3)
		{
			printf("Syntax error: invalid token '%c'\n", c);
			return (count);
		}
	}
	return (count);
}

int	check_mixed_redir(char *str)
{
	while (*str)
	{
		if ((*str == '<' && *(str + 1) == '>')
			|| (*str == '>' && *(str + 1) == '<'))
		{
			printf("Syntax error: invalid token sequence '%c%c'\n", \
				*str, *(str + 1));
			return (1);
		}
		str++;
	}
	return (0);
}

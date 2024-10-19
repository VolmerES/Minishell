/* ************************************************************************** */
/*                                                                            */
/*   tokenize_redir.c                                     :::      ::::::::   */
/*                                     			   		:+:      :+:    :+:   */
/*   By: juan <juan@student.42.fr>                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:50:45 by jdelorme          #+#    #+#             */
/*   Updated: 2024/04/15 13:02:49 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_update_quote_flags(char c, int *squotes, int *dquotes)
{
	if (c == SQUOTES)
		*squotes = !(*squotes);
	if (c == DQUOTES)
		*dquotes = !(*dquotes);
}

void	ft_set_main_command(t_msh *commands, int *i, int *j)
{
	int		start;
	int		squotes;
	int		dquotes;
	char	c;

	squotes = 0;
	dquotes = 0;
	while (commands->cmds[*i]->cmd[*j] == SPACE)
		(*j)++;
	if (commands->cmds[*i]->cmd_main == NULL)
	{
		start = *j;
		c = commands->cmds[*i]->cmd[*j];
		while (c != '\0' && (squotes == 1 || dquotes == 1
				|| (c != ' ' && c != '<' && c != '>')))
		{
			ft_update_quote_flags(c, &squotes, &dquotes);
			c = commands->cmds[*i]->cmd[++(*j)];
		}
		if (commands->cmds[*i]->cmd[*j - 1] == SPACE
			&& squotes == 0 && dquotes == 0)
			(*j)--;
		commands->cmds[*i]->cmd_main = ft_substr(
				commands->cmds[*i]->cmd, start, *j - start);
	}
}

void	ft_is_command(t_msh *commands, int *i, int *j)
{
	ft_set_main_command(commands, i, j);
	while (commands->cmds[*i]->cmd[*j] == SPACE)
		(*j)++;
	while (commands->cmds[*i]->cmd[*j] != '<'
		&& commands->cmds[*i]->cmd[*j] != '>'
		&& commands->cmds[*i]->cmd[*j] != '\0'
		&& commands->cmds[*i]->cmd[*j] != ' ')
	{
		ft_arguments(commands, i, j);
	}
	if (commands->cmds[*i]->args)
		commands->cmds[*i]->args[commands->parser.k] = NULL;
}

int	ft_count_redir(char *str)
{
	if (check_consecutive_chars(str, '<') >= 3
		|| check_consecutive_chars(str, '>') >= 3)
		return (1);
	if (check_mixed_redir(str))
		return (1);
	return (0);
}

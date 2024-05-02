/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_eraser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:39:20 by jdelorme          #+#    #+#             */
/*   Updated: 2024/05/02 12:07:43 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_trim_end(char *str)
{
	int	i;

	i = strlen(str) - 1;
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
		if (commands->cmds[*i]->cmd_main[j] == SQUOTES
			|| commands->cmds[*i]->cmd_main[j] == DQUOTES)
		{
			ft_memmove(&commands->cmds[*i]->cmd_main[j],
				&commands->cmds[*i]->cmd_main[j + 1], cmd_len - j - 1);
			commands->cmds[*i]->cmd_main[cmd_len - 1] = '\0';
			cmd_len--;
		}
		else
		{
			j++;
		}
	}
}

void	ft_set_null_two(t_msh *commands, int *i)
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

	j = 0;
	while (commands->cmds[*i]->args[j] != NULL)
	{
		arg_len = ft_strlen(commands->cmds[*i]->args[j]);
		if ((commands->cmds[*i]->args[j][0] == SQUOTES
			|| commands->cmds[*i]->args[j][0] == DQUOTES) &&
			(commands->cmds[*i]->args[j][arg_len - 1] == SQUOTES
			|| commands->cmds[*i]->args[j][arg_len - 1] == DQUOTES))
		{
			ft_memmove(&commands->cmds[*i]->args[j][0],
				&commands->cmds[*i]->args[j][1], arg_len - 2);
			commands->cmds[*i]->args[j][arg_len - 2] = '\0';
		}
		j++;
	}
	ft_set_null_two(commands, i);
}

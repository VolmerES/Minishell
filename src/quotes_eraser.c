/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_eraser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:39:20 by jdelorme          #+#    #+#             */
/*   Updated: 2024/06/27 14:32:53 by jdelorme         ###   ########.fr       */
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

void ft_erase_cmd_quotes(t_msh *commands, int *i)
{
	int     j;
	int     k;
	int     cmd_len;
	char    *new_cmd;

	k = 0;
	j = 0;
	cmd_len = ft_strlen(commands->cmds[*i]->cmd_main);
	new_cmd = malloc(sizeof(char) * (cmd_len + 1));
	if (!new_cmd) 
		return;
	while (j < cmd_len)
	{
		if (commands->cmds[*i]->cmd_main[j] != '\'' && commands->cmds[*i]->cmd_main[j] != '\"') // Asumiendo SQUOTES y DQUOTES
		{
			new_cmd[k++] = commands->cmds[*i]->cmd_main[j];
		}
		j++;
	}
	new_cmd[k] = '\0';
	free(commands->cmds[*i]->cmd_main);
	commands->cmds[*i]->cmd_main = new_cmd;
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

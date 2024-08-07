/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_eraser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:39:20 by jdelorme          #+#    #+#             */
/*   Updated: 2024/08/07 19:48:23 by ldiaz-ra         ###   ########.fr       */
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
		if (commands->cmds[*i]->cmd_main[j] != '\'' && commands->cmds[*i]->cmd_main[j] != '\"') 
		{
			new_cmd[k++] = commands->cmds[*i]->cmd_main[j];
		}
		j++;
	}
	new_cmd[k] = '\0';
	free(commands->cmds[*i]->cmd_main);
	commands->cmds[*i]->cmd_main = new_cmd;
}


void	ft_erase_arg_quotes(t_msh *commands, int *i)
{
	int		j;
	int		k;
	int		l;
	char	*arg;
	char	*new_arg;
	char	quote_char;

	j = 0;
	while (commands->cmds[*i]->args && commands->cmds[*i]->args[j] != NULL)
	{
		arg = commands->cmds[*i]->args[j];
		new_arg = malloc(ft_strlen(arg) + 1);
		if (!new_arg)
			return ;
		k = 0;
		l = 0;
		quote_char = '\0';
		if (arg[0] == SQUOTES || arg[0] == DQUOTES)
			quote_char = arg[0];
		while (arg[l] != '\0')
		{
			if (quote_char != '\0' && arg[l] == quote_char)
			{
				if (l == 0)
				{
					l++;
					continue;
				}
				else if (arg[l + 1] == '\0')
				{
					l++;
					continue;
				}
			}
			new_arg[k++] = arg[l++];
		}
		new_arg[k] = '\0';
		free(commands->cmds[*i]->args[j]);
		commands->cmds[*i]->args[j] = ft_strtrim(new_arg, " ");
		free(new_arg);
		j++;
	}
}

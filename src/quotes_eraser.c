/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_eraser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:39:20 by jdelorme          #+#    #+#             */
/*   Updated: 2024/08/21 19:49:24 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_trim_end(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] == ' ')
	{
		str[i] = '\0';
		i--;
	}
}

void	ft_erase_cmd_quotes(t_msh *commands, int *i)
{
	int		j;
	int		k;
	int		cmd_len;
	char	*new_cmd;

	k = 0;
	j = 0;
	cmd_len = ft_strlen(commands->cmds[*i]->cmd_main);
	new_cmd = malloc(sizeof(char) * (cmd_len + 1));
	if (!new_cmd)
		return ;
	while (j < cmd_len)
	{
		if (commands->cmds[*i]->cmd_main[j] != '\'' && \
		commands->cmds[*i]->cmd_main[j] != '\"')
		{
			new_cmd[k++] = commands->cmds[*i]->cmd_main[j];
		}
		j++;
	}
	new_cmd[k] = '\0';
	free(commands->cmds[*i]->cmd_main);
	commands->cmds[*i]->cmd_main = new_cmd;
}

void	ft_erase_arg_quotes(t_msh *commands)
{
	t_counters	count;
	char		*arg;
	char		*new_arg;
	char		quote_char;

	count.j = 0;
	count.i = 0;
	while (commands->cmds && commands->cmds[count.i] != NULL)
	{
		while (commands->cmds[count.i]->args && commands->cmds[count.i]->args[count.j] != NULL)
		{
			arg = commands->cmds[count.i]->args[count.j];
			new_arg = malloc((ft_strlen(arg) + 1 )* sizeof(char));
			if (!new_arg)
				exit_(2);
			count.k = 0;
			count.l = 0;
			quote_char = '\0';
			if (arg[0] == SQUOTES || arg[0] == DQUOTES)
				quote_char = arg[0];
			while (arg[count.l] != '\0')
			{
				if (arg[count.l] == quote_char && (count.l == 0 || arg[count.l + 1] == '\0'))
					count.l++;
				else
					new_arg[count.k++] = arg[count.l++];
			}
			new_arg[count.k] = '\0';
			free(commands->cmds[count.i]->args[count.j]);
			commands->cmds[count.i]->args[count.j] = new_arg;
			if (!commands->cmds[count.i]->args[count.j])
				exit_(2);
			count.j++;
		}
	count.i++;
	}
}


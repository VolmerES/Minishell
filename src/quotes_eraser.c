/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_eraser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:39:20 by jdelorme          #+#    #+#             */
/*   Updated: 2024/10/07 17:10:37 by jdelorme         ###   ########.fr       */
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

static int	copy_chars_without_quotes(char *new_arg, char *arg, int l, int *k)
{
	char	quote_char;

	quote_char = arg[l++];
	while (arg[l] != '\0' && !(arg[l] == quote_char && arg[l - 1] != '\\'))
	{
		new_arg[(*k)++] = arg[l++];
	}
	if (arg[l] != '\0')
		l++;
	return (l);
}

char	*ft_process_quotes(char *arg)
{
	char	*new_arg;
	int		k;
	int		l;

	l = 0;
	k = 0;
	new_arg = malloc((strlen(arg) + 1) * sizeof(char));
	if (!new_arg)
		exit(2);
	while (arg[l] != '\0')
	{
		if ((arg[l] == '\'' || arg[l] == '\"')
			&& (l == 0 || arg[l - 1] != '\\'))
		{
			l = copy_chars_without_quotes(new_arg, arg, l, &k);
		}
		else
		{
			new_arg[k++] = arg[l++];
		}
	}
	new_arg[k] = '\0';
	return (new_arg);
}


void	ft_erase_arg_quotes(t_msh *commands)
{
	t_counters	count;
	char		*new_arg;

	count.i = 0;
	while (commands->cmds && commands->cmds[count.i] != NULL)
	{
		count.j = 0;
		while (commands->cmds[count.i]->args
			&& commands->cmds[count.i]->args[count.j] != NULL)
		{
			new_arg = ft_process_quotes(commands->cmds[count.i]->args[count.j]);
			free(commands->cmds[count.i]->args[count.j]);
			commands->cmds[count.i]->args[count.j] = new_arg;
			if (!commands->cmds[count.i]->args[count.j])
				exit_(2);
			count.j++;
		}
		count.i++;
	}
}

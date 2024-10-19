/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:40:32 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/10/19 19:46:21 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_builtins(t_msh *commands, int i)
{
	if (ft_strcmp(commands->cmds[i]->cmd_main, "cd") == 0)
		cd_builtin(commands, i);
	else if (ft_strcmp(commands->cmds[i]->cmd_main, "pwd") == 0)
		commands->last_out = pwd_builtin(commands);
	else if (ft_strcmp(commands->cmds[i]->cmd_main, "export") == 0)
		export_builtin(commands, i);
	else if (ft_strcmp(commands->cmds[i]->cmd_main, "echo") == 0)
		commands->last_out = echo_builtin(commands, i);
	else if (ft_strcmp(commands->cmds[i]->cmd_main, "unset") == 0)
		commands->last_out = unset_builtin(commands, i);
	else if (ft_strcmp(commands->cmds[i]->cmd_main, "env") == 0)
		commands->last_out = env_builtin(commands);
	else if (ft_strcmp(commands->cmds[i]->cmd_main, "exit") == 0)
		exit_builtin(commands, i);
}

int	is_builtins(t_msh *commands, int i)
{
	if (commands->cmds[i] && commands->cmds[i]->cmd_main)
	{
		if (ft_strcmp(commands->cmds[i]->cmd_main, "cd") == 0)
			return (1);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "pwd") == 0)
			return (1);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "export") == 0)
			return (1);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "echo") == 0)
			return (1);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "unset") == 0)
			return (1);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "env") == 0)
			return (1);
		else if (ft_strcmp(commands->cmds[i]->cmd_main, "exit") == 0)
			return (1);
	}
	return (0);
}

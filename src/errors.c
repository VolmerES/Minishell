/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:26:28 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/06/01 16:34:52 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exit_(t_err_msg error)
{
	if (error == 0)
		perror("PIPE");
	else if (error == 1)
		perror("FORK");
	else if (error == 2)
		perror("MALLOC");
	exit(1);
}

void	exit_err(t_msh *commands, int cmd_i)
{
	ft_putstr_fd(commands->cmds[cmd_i]->cmd_main, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(127);
}
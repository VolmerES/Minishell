/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdelorme <jdelorme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:50:45 by jdelorme          #+#    #+#             */
/*   Updated: 2024/09/23 16:25:24 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_init_msh_struct(t_msh *commands)
{
	commands->cmds = NULL;
	commands->envp = NULL;
	commands->evar = NULL;
	commands->input = NULL;
	commands->cp_stdin = STDIN_FILENO;
	commands->cp_stdout = STDOUT_FILENO;
	commands->parser.cmd_index = 0;
	commands->last_out = 0;
}

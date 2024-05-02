/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:42:29 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/05/02 15:36:52 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    executor_manage(t_msh *commands)
{
	int i;

	i = 0;
    t_file path;
    t_file *path_;
    path.filename = "infile";
    path.type = INFILE_NORMAL;
    path_ = &path;
    commands->cmds[0]->infile = &path_;
    if (commands->parser.cmd_index == 1)
    {
        if (is_builtins(commands, i))
            bd_one_command(commands);
        else
            one_command(commands);
    }
    else
    {

    }
}
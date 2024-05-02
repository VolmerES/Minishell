/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:42:29 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/05/02 18:06:24 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    executor_manage(t_msh *commands)
{
	int i;

	i = 0;
    // t_file file;
    // t_file *file_ptr;

    // file.filename = "infile";
    // file.type = INFILE_NORMAL;

    // file_ptr = &file;

    // commands->cmds[0]->infile = &file_ptr;


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
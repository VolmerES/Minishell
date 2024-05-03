/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:42:29 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/05/03 13:04:52 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    executor_manage(t_msh *commands)
{
	int i;

	i = 0;
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
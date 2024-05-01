/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:28:40 by david             #+#    #+#             */
/*   Updated: 2024/05/01 13:23:59 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	export_builtin(t_msh *commands, int i)
{
	// if (commands->cmds[i]->args == NULL)
	if (commands->cmds[i]->args[0] == NULL)
		export_empty(commands);
	else
		manage_export(commands, i);
	return (0);
}

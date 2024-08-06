/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:28:40 by david             #+#    #+#             */
/*   Updated: 2024/08/06 19:02:06 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	export_builtin(t_msh *commands, int i)
{
	if (commands->cmds[i]->args == NULL)
		export_empty(commands);
	else
		manage_export(commands, i);
	return (0);
}

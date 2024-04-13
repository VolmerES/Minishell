/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 11:28:40 by david             #+#    #+#             */
/*   Updated: 2024/04/13 12:07:27 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	export_builtin(t_msh *commands, int i)
{
	char **var;

	if (commands->cmds[i]->args == NULL)
		export_empty(commands);
	else
		manage_export(commands, i);
	return (0);
}

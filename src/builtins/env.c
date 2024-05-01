/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:25:02 by david             #+#    #+#             */
/*   Updated: 2024/04/27 17:49:41 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void env_builtin(t_msh *commands)
{
	int j;

	j = 0;
	while (commands->envp[j])
	{
		if (ft_strchr(commands->envp[j], '='))
			printf("%s\n", commands->envp[j]);
		j++;
	}
}
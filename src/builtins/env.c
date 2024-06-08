/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:25:02 by david             #+#    #+#             */
/*   Updated: 2024/06/08 17:58:28 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	env_builtin(t_msh *commands)
{
	int j;

	j = 0;
	while (commands->envp[j])
	{
		if (ft_strchr(commands->envp[j], '='))
			printf("%s\n", commands->envp[j]);
		j++;
	}
	return (0);
}
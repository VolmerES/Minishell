/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:04:12 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/09/27 23:51:03 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	updates_pwds(t_msh *commands, char **old_pwd)
{
	int		i_old_pwd;
	int		i_pwd;

	i_old_pwd = ft_search_env(commands->envp, "OLDPWD");
	i_pwd = ft_search_env(commands->envp, "PWD");
	
	if (*old_pwd)
	{
		update_env(commands, i_old_pwd, ft_strjoin("OLDPWD=", *old_pwd));
		free(*old_pwd);
		*old_pwd = getcwd(NULL, 0);
		update_env(commands, i_pwd, ft_strjoin("PWD=", *old_pwd));
		commands->last_out = 0;
	}
	else{
		free(commands->envp[i_old_pwd]);
		while (commands->envp[i_old_pwd] != NULL)
		{
			commands->envp[i_old_pwd] = commands->envp[i_old_pwd + 1];
			i_old_pwd++;
		}
		commands->last_out = 0;
	}
}

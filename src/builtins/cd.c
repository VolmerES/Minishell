/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:40:32 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/03/22 17:39:36 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cd_builtins(t_msh *commands, int i)
{
	char *old_pwd;
	int index_pwd;
	int index_oldpwd;
	
	old_pwd = getcwd(NULL, 0);
	if (chdir(commands->cmds[i]->args) != -1)
	{
		index_pwd = ft_search_env(commands->envp, "PWD");
		index_oldpwd = ft_search_env(commands->envp, "OLDPWD");
		if (index_pwd != -1)
		{
			free(commands->envp[index_pwd]);
			commands->envp[index_pwd]= ft_strjoin("PWD=", getcwd(NULL, 0));
		}
		else
			commands->envp = ft_addvariable(commands->envp, ft_strjoin("PWD=", commands->cmds[i]->args));
		if (index_oldpwd != -1)
		{
			free(commands->envp[index_oldpwd]);
			commands->envp[index_oldpwd]= ft_strjoin("OLDPWD=", old_pwd);
		}
		else
			commands->envp = ft_addvariable(commands->envp, ft_strjoin("OLDPWD=", old_pwd));
		free(old_pwd);		
	}
	printf("=>PATH: %s\n =>PATHOLD: %s\n",commands->envp[index_pwd], commands->envp[index_oldpwd]);
	return (0);
}

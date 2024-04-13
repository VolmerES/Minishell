/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:40:32 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/04/13 13:45:33 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void update_env(t_msh *commands, int index, char *value)
{
	if (index != -1)
	{
		free(commands->envp[index]);
		commands->envp[index] = value;
	}
	else
		commands->envp = ft_addvariable(commands->envp, value);
}

static void cd_home(t_msh *commands)
{
	int i_home;
	int i_old_pwd;
	int i_pwd;
	char *old_pwd;

	i_home = ft_search_env(commands->envp, "HOME");
	i_old_pwd = ft_search_env(commands->envp, "OLDPWD");
	i_pwd = ft_search_env(commands->envp, "PWD");
	if (i_home == -1)
	{
		printf("cd: HOME not set");
		return;
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(commands->envp[i_home] + 5) != -1)
	{
		update_env(commands, i_pwd, ft_strjoin("PWD=", commands->envp[i_home] + 5));
		update_env(commands, i_old_pwd, ft_strjoin("OLDPWD=", old_pwd));
	}
	free(old_pwd);
}

static void cd_route(t_msh *commands, int i)
{
	int i_old_pwd;
	int i_pwd;
	char *old_pwd;

	i_old_pwd = ft_search_env(commands->envp, "OLDPWD");
	i_pwd = ft_search_env(commands->envp, "PWD");
	old_pwd = getcwd(NULL, 0);
	if (chdir(commands->cmds[i]->args[0]) != -1)
	{
		update_env(commands, i_old_pwd, ft_strjoin("OLDPWD=", old_pwd));
		free(old_pwd);
		old_pwd = getcwd(NULL, 0);
		update_env(commands, i_pwd, ft_strjoin("PWD=", old_pwd));
	}
	free(old_pwd);
}

int cd_builtin(t_msh *commands, int i)
{
	int num_args;

	num_args = check_num_args(commands, i);
	if (!num_args)
		cd_home(commands);
	else if (num_args >= 1)
		cd_route(commands, i);
	return (0);
}

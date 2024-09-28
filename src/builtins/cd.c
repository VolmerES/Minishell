/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:40:32 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/09/28 16:54:32 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	int	update_pwds(t_msh *commands, char *old_p, int i_p, int i_old_p)
{
	if (old_p)
		update_env(commands, i_old_p, ft_strjoin("OLDPWD=", old_p));
	else
	{
		update_env(commands, i_old_p, ft_strjoin("OLDPWD=", \
		commands->envp[i_p] + 4));
	}
	return (0);
}

void	update_env(t_msh *commands, int index, char *value)
{
	if (index != -1)
	{
		free(commands->envp[index]);
		commands->envp[index] = value;
	}
	else
		commands->envp = ft_addvariable(commands->envp, value);
}

static	void	cd_home(t_msh *commands)
{
	int		i_home;
	int		i_old_pwd;
	int		i_pwd;
	char	*old_pwd;

	i_home = ft_search_env(commands->envp, "HOME");
	i_old_pwd = ft_search_env(commands->envp, "OLDPWD");
	i_pwd = ft_search_env(commands->envp, "PWD");
	if (i_home == -1)
	{
		printf("cd: HOME not set");
		commands->last_out = 1;
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(commands->envp[i_home] + 5) != -1)
	{
		commands->last_out = update_pwds(commands, \
		old_pwd, i_pwd, i_old_pwd);
		update_env(commands, i_pwd, \
		ft_strjoin("PWD=", commands->envp[i_home] + 5));
	}
	free(old_pwd);
}

static	void	cd_route(t_msh *commands, int i)
{
	if (updates_pwds(commands, i))
	{
		perror(commands->cmds[i]->args[0]);
		commands->last_out = 1;
	}
}

int	cd_builtin(t_msh *commands, int i)
{
	int	num_args;

	num_args = check_num_args(commands, i);
	if (!num_args)
		cd_home(commands);
	else if (num_args >= 1)
		cd_route(commands, i);
	return (0);
}

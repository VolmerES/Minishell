/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:04:12 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/09/28 20:02:27 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	int	change_dir(t_msh *commands, char *dir)
{
	int		i_old_pwd;
	int		i_pwd;
	char	*new_pwd;

	i_old_pwd = ft_search_env(commands->envp, "OLDPWD");
	i_pwd = ft_search_env(commands->envp, "PWD");
	if (dir && chdir(dir) != -1)
	{
		if (i_pwd != -1)
		{
			update_env(commands, i_old_pwd, ft_strjoin("OLDPWD=", commands->envp[i_pwd] + 4));
			new_pwd = getcwd(NULL, 0);
			if (new_pwd)
			{
				update_env(commands, i_pwd, ft_strjoin("PWD=", new_pwd));
				free(new_pwd);
			}
			else
				update_env(commands, i_pwd, ft_strdup("PWD="));
		}
		else
			move_and_free(commands, i_old_pwd);
		commands->last_out = 0;
	}
	else
		return (dir != NULL);
	return (0);
}

static	char	*get_old_pwd(t_msh *commands)
{
	int		i_old_pwd;

	i_old_pwd = ft_search_env(commands->envp, "OLDPWD");
	if (i_old_pwd != -1)
		return (commands->envp[i_old_pwd] + 7);
	printf("cd: OLDPWD not set\n");
	commands->last_out = 1;
	return (NULL);
}

int	updates_pwds(t_msh *commands, int i_cmd)
{
	char	*dir;

	if (ft_strcmp(commands->cmds[i_cmd]->args[0], "-") == 0)
		dir = get_old_pwd(commands);
	else
		dir = commands->cmds[i_cmd]->args[0];
	return (change_dir(commands, dir));
}

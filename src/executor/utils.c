/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:56:37 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/05/03 17:34:19 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*join_path(char *path, char *command)
{
	char *command_;
	char *new_path;

	command_ = ft_strjoin("/", command);
	new_path = ft_strjoin(path, command_);
	free(command_);
	return (new_path);
}

char	*check_path(char **path, char *command)
{
	char	*path_all;
	int		i;

	i = 0;
	if (ft_strrchr(command, '/') && !access(command, X_OK))
		return (command);
	else if (ft_strrchr(command, '/') && access(command, X_OK))
		return (NULL);
	while (path[i])
	{
		path_all = join_path(path[i], command);
		if (!access(path_all, X_OK))
			return (path_all);
		free(path_all);
		i++;
	}
	return (NULL);
}

char	**find_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			return (ft_split(env[i] + 5, ':'));
	}
	return (NULL);
}

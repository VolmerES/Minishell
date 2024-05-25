/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:55:36 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/05/25 15:01:54 by ldiaz-ra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	write_tmp(int fd, char *name)
{
	char	*buffer;

	buffer = readline("");
	while (buffer && ft_strcmp(buffer, name))
	{
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
		buffer = readline("");
	}
	if (buffer)
		free(buffer);
	return (0);
}

char	*her_doc(char *name)
{
	int		fd;
	char	*tmpfile;

	tmpfile = ft_strjoin(".", name);
	if (!tmpfile)
		return (NULL);
	fd = open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		free(tmpfile);
		return (NULL);
	}
	if (write_tmp(fd, name))
	{
		free(tmpfile);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (tmpfile);
}

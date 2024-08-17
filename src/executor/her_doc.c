/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldiaz-ra <ldiaz-ra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:55:36 by ldiaz-ra          #+#    #+#             */
/*   Updated: 2024/08/17 13:24:59 by ldiaz-ra         ###   ########.fr       */
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

void	check_malloc(char *count_char, char *name_tmp, char *tmp)
{
	if (!count_char || !name_tmp || !tmp)
		_exit(2);
}

char *check_file(char *name)
{
	char	*tmp;
	char	*count_char;
	char	*name_tmp;
	int		count;

	count = 1;
	count_char = ft_itoa(count);
	name_tmp = ft_strjoin(name, count_char);
	tmp = ft_strjoin("/tmp/.", name_tmp);
	check_malloc(count_char, name_tmp, tmp);
	while (access(tmp, F_OK) != -1)
	{
		free(count_char);
		free(name_tmp);
		free(tmp);
		count++;
		count_char = ft_itoa(count);
		name_tmp = ft_strjoin(name, count_char);
		tmp = ft_strjoin("/tmp/.", name_tmp);
		check_malloc(count_char, name_tmp, tmp);
	}
	free(count_char);
	free(name_tmp);
	return tmp;
}

char	*her_doc(char *name)
{
	int		fd;
	char	*tmpfile;
	
	tmpfile = check_file(name);
	fd = open(tmpfile, O_WRONLY | O_CREAT , 0777);
	if (fd < 0)
	{
		free(tmpfile);
		_exit(2);
	}
	write_tmp(fd, name);
	close(fd);
	return (tmpfile);
}

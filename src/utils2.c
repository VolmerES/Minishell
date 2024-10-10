/* ************************************************************************** */
/*                                                                            */
/*   utils2.c                                             :::      ::::::::   */
/*                                     					:+:      :+:    :+:   */
/*   By: juan <juan@student.42.fr>                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:50:45 by jdelorme          #+#    #+#             */
/*   Updated: 2024/03/05 22:50:46 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_null(t_msh *commands, int index)
{
	commands->cmds[index]->infile = NULL;
	commands->cmds[index]->outfile = NULL;
	commands->cmds[index]->cmd_main = NULL;
	commands->cmds[index]->cmd = NULL;
	commands->cmds[index]->args = NULL;
	commands->cmds[index]->full_cmd = NULL;
}

char	*ft_strncpy(char *dst, const char *src, size_t len, size_t n)
{
	size_t	i;

	i = 0;
	while (i < len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	len;

	len = ft_strlen(needle);
	if (len == 0)
		return ((char *)haystack);
	while (*haystack)
	{
		if (!ft_strncmp(haystack, needle, len))
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

void	ft_free_args(t_msh *commands, int *i)
{
	int	j;

	j = 0;
	while (commands->cmds[*i]->args[j] != NULL)
	{
		free(commands->cmds[*i]->args[j]);
		j++;
	}
	free(commands->cmds[*i]->args);
}

void	ft_erase_first_number(t_msh *commands, int i)
{
	int	j;

	j = i + 2;
	ft_strlcpy(&commands->input[i],
	&commands->input[j], ft_strlen(&commands->input[j]) + 1);
}

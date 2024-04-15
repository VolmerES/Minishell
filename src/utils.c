/* ************************************************************************** */
/*                                                                            */
/*   minishell.h                                          :::      ::::::::   */
/*                                     					:+:      :+:    :+:   */
/*   By: juan <juan@student.42.fr>                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:50:45 by jdelorme          #+#    #+#             */
/*   Updated: 2024/03/05 22:50:46 by jdelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* ************************************************************************** */
/*  Funcion para buscar ocurrencias de los bulktins, sin el "n bytes" de la   */
/*  version de la biblioteca de la libft                                      */
/* ************************************************************************** */

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	if (!str1 || !str2)
		return (0);
	i = 0;
	while ((str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

void	ft_free_matrix(char **env)
{
	int	i;

	i = -1;
	if (!env)
		return ;
	while (env[++i])
	{
		free(env[i]);
	}
	*env = NULL;
	free(env);
}

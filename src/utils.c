/* ************************************************************************** */
/*                                                                            */
/*   utils.c                                              :::      ::::::::   */
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

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	free(env);
	env = NULL;
}

void	*ft_realloc(void *ptr, size_t original_size, size_t new_size) 
{
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	} 
	else if (!ptr)
	{
		return (malloc(new_size));
	} else if (new_size <= original_size)
	{
		return (ptr);
	}
	else
	{
		void *new_ptr = malloc(new_size);
		if (new_ptr)
		{
			ft_memcpy(new_ptr, ptr, original_size);
			free(ptr);
		}
		return (new_ptr);
	}
}

void generation_pwd(t_msh *commands)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	update_env(commands, ft_search_env(commands->envp, "PWD"), ft_strjoin("PWD=", pwd));
	free(pwd);
}
